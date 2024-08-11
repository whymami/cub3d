/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:54:58 by muguveli          #+#    #+#             */
/*   Updated: 2024/08/11 20:44:18 by muguveli         ###   ########.fr       */
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
	game->map->map = ft_calloc(y - 8, sizeof(char *));
	if (!game->map->map)
		ft_exit(1, "Memory allocation failed", game);
	game->map->data = ft_calloc(1, sizeof(t_mapdata));
	if (!game->map->data)
		ft_exit(1, "Memory allocation failed", game);;
	game->map->data->data = ft_calloc(9, sizeof(char *));
	if (!game->map->data->data)
		ft_exit(1, "Memory allocation failed", game);
	game->map->map_copy = ft_calloc(y, sizeof(char *));
	if (!game->map->map_copy)
		ft_exit(1, "Memory allocation failed", game);
}

void	copy_map(t_game *game, char *path)
{
	int		fd;
	char	*line;
	int		y;

	fd = open(path, O_RDONLY);
	y = -1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (y < 7 && ft_len_not_nl(line))
			game->map->map_copy[++y] = ft_strdup(line);
		else if (y > 7)
			game->map->map_copy[++y] = ft_strdup(line);
		free(line);
	}
	free(line);
	close(fd);
}



void	parse_copymap(t_game *game)
{
	int	y;

	y = -1;
	while (++y < game->map->height)
	{
		printf("a: %s", game->map->map_copy[y]);
		if (y < 8)
			game->map->data->data[y] = ft_substr(game->map->map_copy[y], 0,
					ft_len_not_nl(game->map->map_copy[y]));
		else
			game->map->map[y - 6] = ft_substr(game->map->map_copy[y], 0,
					ft_len_not_nl(game->map->map_copy[y]));
	}
	data_args_control(game);
}
