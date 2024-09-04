/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:10:38 by btanir            #+#    #+#             */
/*   Updated: 2024/09/04 16:22:10 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_game *game)
{
	t_ray	*ray;

	ray = ft_calloc(1, sizeof(t_ray));
	if (!ray)
		ft_exit(1, "Memory allocation failed", game);
	game->ray = ray;
}

static void	player_start_dir2(t_player *player)
{
	if (player->player_dir == WEST)
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else if (player->player_dir == EAST)
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
}

void	player_start_dir(t_game *game)
{
	t_player	*player;

	player = game->player;
	if (player->player_dir == NORTH)
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
	else if (player->player_dir == SOUTH)
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
	else
		player_start_dir2(player);
	game->player = player;
}
