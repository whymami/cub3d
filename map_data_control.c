/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_data_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:56:44 by muguveli          #+#    #+#             */
/*   Updated: 2024/09/04 16:22:19 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	data_control(t_game *game)
{
	char	*line;
	int		fd;
	int		i;

	i = -1;
	while (++i < 4)
	{
		fd = open(game->map->data->data[i] + 3, O_RDONLY);
		if (fd < 0)
			ft_exit(1, "Invalid data path", game);
		line = get_next_line(fd);
		close(fd);
		if (line == NULL)
		{
			free(line);
			ft_exit(1, "NO Path not found\n", game);
		}
		free(line);
	}
	rgb_control(game);
}

static void	data_arg_type(char *check_str, t_game *game, int i)
{
	if (game->map->data->no == NULL && ft_strncmp(check_str, "NO", 2) == 0)
		game->map->data->no = game->map->data->data[i];
	else if (game->map->data->so == NULL && ft_strncmp(check_str, "SO", 2) == 0)
		game->map->data->so = game->map->data->data[i];
	else if (game->map->data->we == NULL && ft_strncmp(check_str, "WE", 2) == 0)
		game->map->data->we = game->map->data->data[i];
	else if (game->map->data->ea == NULL && ft_strncmp(check_str, "EA", 2) == 0)
		game->map->data->ea = game->map->data->data[i];
	else if (game->map->data->floor == NULL && ft_strncmp(check_str, "F",
			1) == 0)
		game->map->data->floor = game->map->data->data[i];
	else if (game->map->data->ceiling == NULL && ft_strncmp(check_str, "C",
			1) == 0)
		game->map->data->ceiling = game->map->data->data[i];
	else
		ft_exit(1, "Invalid map data", game);
}

void	data_args_control(t_game *game)
{
	int	i;

	i = -1;
	while (game->map->data->data[++i])
		if (ft_len_not_nl(game->map->data->data[i]))
			data_arg_type(game->map->data->data[i], game, i);
	data_control(game);
}
