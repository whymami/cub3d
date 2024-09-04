/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:54:58 by muguveli          #+#    #+#             */
/*   Updated: 2024/09/04 16:22:23 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_map_height(char *path)
{
	int		fd;
	char	*line;
	int		y;

	fd = open(path, O_RDONLY);
	y = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		y++;
		free(line);
	}
	return (close(fd), free(line), y);
}

void	map_init(t_game *game, int y)
{
	game->map = ft_calloc(1, sizeof(t_map));
	if (!game->map)
		ft_exit(1, "Memory allocation failed", game);
	game->map->data = ft_calloc(1, sizeof(t_mapdata));
	if (!game->map->data)
		ft_exit(1, "Memory allocation failed", game);
	game->map->data->data = ft_calloc(7, sizeof(char *));
	if (!game->map->data->data)
		ft_exit(1, "Memory allocation failed", game);
	game->map->map_copy = ft_calloc(y + 1, sizeof(char *));
	if (!game->map->map_copy)
		ft_exit(1, "Memory allocation failed", game);
}

static int	is_data(char *line)
{
	if (!line || ft_len_not_nl(line) == 0)
		return (0);
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "S ", 2) == 0 || ft_strncmp(line, "F ", 2) == 0
		|| ft_strncmp(line, "C ", 2) == 0)
		return (1);
	else
		ft_exit(1, "Invalid data", NULL);
	return (0);
}

void	data_copy(t_game *game)
{
	int	y;
	int	data_i;

	y = -1;
	data_i = 0;
	while (++y < game->map->height && data_i < 6)
		if (is_data(game->map->map_copy[y]))
			game->map->data->data[data_i++] = ft_substr(game->map->map_copy[y],
					0, ft_len_not_nl(game->map->map_copy[y]));
	game->map->data->data[data_i] = NULL;
	game->map->data->data_height = y;
}

void	update_data_height(t_game *game)
{
	int	y;

	y = game->map->data->data_height - 1;
	while (++y < game->map->height)
		if (ft_strchr(game->map->map_copy[y], '1'))
			break ;
	game->map->data->data_height = y;
	game->map->height = game->map->height - game->map->data->data_height;
	game->map->map = ft_calloc(game->map->height + 1, sizeof(char *));
	if (!game->map->map)
		ft_exit(1, "Memory allocation failed", game);
}
