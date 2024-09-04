/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:32:31 by btanir            #+#    #+#             */
/*   Updated: 2024/09/04 16:22:27 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_game *game, double next_x, double next_y)
{
	t_map		*map;
	t_player	*player;

	player = game->player;
	map = game->map;
	if (map->map[(int)(player->player_x
			+ next_x)][(int)(player->player_y)] != WALL)
		player->player_x += next_x;
	if (map->map[(int)(player->player_x)][(int)(player->player_y
			+ next_y)] != WALL)
		player->player_y += next_y;
}

void	rotate_player(t_game *game, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player->dir_x;
	game->player->dir_x = game->player->dir_x * cos(rot_speed)
		- game->player->dir_y * sin(rot_speed);
	game->player->dir_y = old_dir_x * sin(rot_speed) + game->player->dir_y
		* cos(rot_speed);
	old_plane_x = game->player->plane_x;
	game->player->plane_x = game->player->plane_x * cos(rot_speed)
		- game->player->plane_y * sin(rot_speed);
	game->player->plane_y = old_plane_x * sin(rot_speed) + game->player->plane_y
		* cos(rot_speed);
}
