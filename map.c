/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:15:33 by muguveli          #+#    #+#             */
/*   Updated: 2024/09/04 16:22:24 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_dir(t_game *game, int y, int x, char dir)
{
	game->player->player_x = x + 0.5;
	game->player->player_y = y + 0.5;
	game->player->player_dir = dir;
	game->player->dir_count++;
	if (game->player->dir_count > 1)
		ft_exit(1, "Multiple player directions", game);
}

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
	map_control(game);
	mlx_initialize(game);
}
