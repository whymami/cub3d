/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:15:33 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/30 16:27:39 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_window_size(t_game *game)
{
	if (game->map->map_height == 0 || game->map->map_width == 0)
		ft_exit(1, "Map file cannot be left empty", game);
	if (game->map->map_height > 20 || game->map->map_width > 10)
		ft_exit(1, "Window size is too big", game);
}

static void	map_check(t_game *game)
{
	int	first_line;
	int	control_line;
	int	y;

	y = 0;
	first_line = ft_len_not_nl(game->map->game_map[0]);
	while (++y < game->map->map_height)
	{
		control_line = ft_len_not_nl(game->map->game_map[y]);
		if (control_line != first_line)
			ft_exit(1, "Map is not rectangular", game);
	}
}

static void	read_map(char *path, t_game *game)
{
	int	fd;
	int	y;

	y = -1;
	game->map->game_map = ft_calloc(game->map->map_height, sizeof(char *));
	if (!game->map->game_map)
		ft_exit(1, "Memory allocation failed", game);
	fd = open(path, O_RDONLY);
	while (++y < game->map->map_height)
		game->map->game_map[y] = get_next_line(fd);
	map_check(game);
}

void	get_map_size(char *path)
{
	int		fd;
	char	*line;
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		ft_exit(1, "Memory allocation failed", game);
	game->map = ft_calloc(1, sizeof(t_map));
	if (!game->map)
		ft_exit(1, "Memory allocation failed", game);
	fd = open(path, O_RDONLY);
	game->map->map_height = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		game->map->map_width = ft_strlen(line);
		game->map->map_height++;
		free(line);
	}
	free(line);
	close(fd);
	ft_window_size(game);
	read_map(path, game);
}
