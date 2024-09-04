/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_devided_h.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:17:28 by muguveli          #+#    #+#             */
/*   Updated: 2024/09/04 16:22:21 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	flood_fill(t_game *game, int y, int x)
{
	if (x < 0 || x > game->map->max_width || y < 0 || y > game->map->height - 1)
		return ;
	if (game->map->ff_map[y][x] != STAR && game->map->ff_map[y][x] != 'F')
	{
		game->map->ff_map[y][x] = 'F';
		flood_fill(game, y - 1, x);
		flood_fill(game, y + 1, x);
		flood_fill(game, y, x - 1);
		flood_fill(game, y, x + 1);
	}
}

static void	h_control(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (game->map->ff_map[++y])
	{
		x = -1;
		while (game->map->ff_map[y][++x])
			if (game->map->ff_map[y][x] == WALL
				|| game->map->ff_map[y][x] == GROUND)
				ft_exit(2, "map can not be devided horizontal", game);
	}
}

void	map_devided_h(t_game *game)
{
	flood_fill(game, game->player->player_x, game->player->player_y);
	h_control(game);
}
