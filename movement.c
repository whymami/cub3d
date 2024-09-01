/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:32:31 by btanir            #+#    #+#             */
/*   Updated: 2024/09/01 18:22:01 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_game *game, double next_x, double next_y)
{
	if (game->map->map[(int)(game->player->player_y)][(int)(game->player->player_x + next_x)] != '1')
		game->player->player_x += next_x;
	if (game->map->map[(int)(game->player->player_y + next_y)][(int)(game->player->player_x)] != '1')
		game->player->player_y += next_y;
}

void	rotate_player(t_game *game, double rot_speed)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = game->player->dir_x;
	game->player->dir_x = game->player->dir_x * cos(rot_speed)
		- game->player->dir_y * sin(rot_speed);
	game->player->dir_y = oldDirX * sin(rot_speed) + game->player->dir_y
		* cos(rot_speed);
	oldPlaneX = game->player->plane_x;
	game->player->plane_x = game->player->plane_x * cos(rot_speed)
		- game->player->plane_y * sin(rot_speed);
	game->player->plane_y = oldPlaneX * sin(rot_speed) + game->player->plane_y
		* cos(rot_speed);
}
