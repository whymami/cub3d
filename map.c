/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:15:33 by muguveli          #+#    #+#             */
/*   Updated: 2024/08/11 20:25:21 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_dir(t_game *game, int x, int y, char dir)
{
	game->player->player_x = x;
	game->player->player_y = y;
	game->player->player_dir = dir;
	game->player->dir_count++;
	if (game->player->dir_count > 1)
		ft_exit(1, "Multiple player directions", game);
}

// int	check_space(char *str, int *i)
// {

// }
void	first_last_line(t_game *game)
{
	int	i;

	i = -1;
	while (game->map->map[0][++i])
		if (game->map->map[0][i] != WALL)
			ft_exit(1, "ilk satır 1 olmalı", game);
	i = -1;
	while (game->map->map[game->map->height - 9][++i])
		if (game->map->map[game->map->height - 9][i] != WALL)
			ft_exit(1, "son satır 1 olmalı", game);
}

// void	horizontal_control(t_game *game)
// {
// 	int	y;
// 	int	x;

// 	y = -1;
// 	while (++y < game->map->height - 8)
// 	{
// 		x = 0;
// 		pass_space(game->map->map[y], &x);
// 		if (((game->map->map[y][x] != WALL)
// 				|| (game->map->map[y][ft_len_not_nl(game->map->map[y])
// 					- 1]) != WALL))
// 			ft_exit(1, "Map is not closed", game);
// 		while (game->map->map[y][x])
// 		{
// 			if (game->map->map[y][x] == SPACE)
// 			{
// 				if (game->map->map[y][x - 1] != WALL)
// 					ft_exit(1, "Map is not closed", game);
// 				pass_space(game->map->map[y], &x);
// 				if (game->map->map[y][x] != WALL)
// 					ft_exit(1, "Map is not closed", game);
// 			}
// 			x++;
// 		}
// 	}
// }

void	frame_control(t_game *game)
{
	int	y;

	y = 0;
	first_last_line(game);
	while (++y < game->map->height - 1)
	{
		if (game->map->map[y][0] != WALL)
			ft_exit(1, "ilk sütun 1 olmalı", game);
		if (game->map->map[y][ft_len_not_nl(game->map->map[y]) - 1] != WALL)
			ft_exit(1, "son sütun 1 olmalı", game);
	}
	// horizontal_control(game);
}

void	map_control(t_game *game)
{
	int	y;
	int	x;

	y = -1;
	game->player = ft_calloc(1, sizeof(t_player));
	if (!game->player)
		ft_exit(1, "Memory allocation failed", game);
	while (++y < game->map->height)
	{
		x = -1;
		if (ft_len_not_nl(game->map->map[y]) == 0)
			ft_exit(1, "The map can not be devided", game);
		while (++x < ft_len_not_nl(game->map->map[y]))
		{
			if (ft_strchr(ELEMENTS, game->map->map[y][x]) == 0)
				ft_exit(1, "Invalid map element", game);
			if (ft_strchr(DIR, game->map->map[y][x]))
				player_dir(game, x, y, game->map->map[y][x]);
		}
	}
	frame_control(game);
}

void	map(char *path)
{
	t_game	*game;
	int		y;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		ft_exit(1, "Memory allocation failed", game);
	y = get_map_height(path);
	map_init(game, y);
	game->map->height = y;
	copy_map(game, path);
	parse_copymap(game);
	game->map->height = y - 9;
	map_control(game);
}
