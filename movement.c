/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:32:31 by btanir            #+#    #+#             */
/*   Updated: 2024/09/01 15:27:33 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_game *game, int sign)
{
	if (sign == 0)
	{
		if (game->map->map[(int)(game->player->player_x + game->player->dir_x
				* MOVE_SPEED)][(int)game->player->player_y] != WALL)
			game->player->player_x += game->player->dir_x * MOVE_SPEED;
		if (game->map->map[(int)game->player->player_x][(int)(game->player->player_y
				+ game->player->dir_y * MOVE_SPEED)] != WALL)
			game->player->player_y += game->player->dir_y * MOVE_SPEED;
	}
	else if (sign == 1)
	{
		if (game->map->map[(int)(game->player->player_x - game->player->dir_x
				* MOVE_SPEED)][(int)game->player->player_y] != WALL)
			game->player->player_x -= game->player->dir_x * MOVE_SPEED;
		if (game->map->map[(int)game->player->player_x][(int)(game->player->player_y
				- game->player->dir_y * MOVE_SPEED)] != WALL)
			game->player->player_y -= game->player->dir_y * MOVE_SPEED;
	}
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
