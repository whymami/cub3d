/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:27:44 by btanir            #+#    #+#             */
/*   Updated: 2024/09/04 16:22:30 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_camera(t_game *game, int x)
{
	game->ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	game->ray->ray_dir_x = game->player->dir_x + game->player->plane_x
		* game->ray->camera_x;
	game->ray->ray_dir_y = game->player->dir_y + game->player->plane_y
		* game->ray->camera_x;
	game->ray->delta_dist_x = fabs(1 / game->ray->ray_dir_x);
	game->ray->delta_dist_y = fabs(1 / game->ray->ray_dir_y);
}

static void	calculate_ray_steps(t_game *game, int map_x, int map_y)
{
	if (game->ray->ray_dir_x < 0)
	{
		game->ray->step_x = -1;
		game->ray->side_dist_x = (game->player->player_x - map_x)
			* game->ray->delta_dist_x;
	}
	else
	{
		game->ray->step_x = 1;
		game->ray->side_dist_x = (map_x + 1.0 - game->player->player_x)
			* game->ray->delta_dist_x;
	}
	if (game->ray->ray_dir_y < 0)
	{
		game->ray->step_y = -1;
		game->ray->side_dist_y = (game->player->player_y - map_y)
			* game->ray->delta_dist_y;
	}
	else
	{
		game->ray->step_y = 1;
		game->ray->side_dist_y = (map_y + 1.0 - game->player->player_y)
			* game->ray->delta_dist_y;
	}
}

static void	perform_dda(t_game *game, int *map_x, int *map_y)
{
	game->ray->hit = 0;
	while (game->ray->hit == 0)
	{
		if (game->ray->side_dist_x < game->ray->side_dist_y)
		{
			game->ray->side_dist_x += game->ray->delta_dist_x;
			*map_x += game->ray->step_x;
			game->ray->side = 0;
		}
		else
		{
			game->ray->side_dist_y += game->ray->delta_dist_y;
			*map_y += game->ray->step_y;
			game->ray->side = 1;
		}
		if (game->map->map[*map_x][*map_y] == '1')
			game->ray->hit = 1;
	}
}

static void	calculate_wall_height(t_game *game, int map_x, int map_y)
{
	if (game->ray->side == 0)
		game->ray->perp_wall_dist = (map_x - game->player->player_x + (1
					- game->ray->step_x) / 2) / game->ray->ray_dir_x;
	else
		game->ray->perp_wall_dist = (map_y - game->player->player_y + (1
					- game->ray->step_y) / 2) / game->ray->ray_dir_y;
	game->ray->line_height = (int)(WIN_HEIGHT / game->ray->perp_wall_dist);
	game->ray->draw_start = -game->ray->line_height / 2 + WIN_HEIGHT / 2;
	if (game->ray->draw_start < 0)
		game->ray->draw_start = 0;
	game->ray->draw_end = game->ray->line_height / 2 + WIN_HEIGHT / 2;
	if (game->ray->draw_end >= WIN_HEIGHT)
		game->ray->draw_end = WIN_HEIGHT - 1;
}

void	raycasting(t_game *game)
{
	int	x;
	int	map_x;
	int	map_y;

	x = -1;
	while (++x < WIN_WIDTH)
	{
		set_camera(game, x);
		map_x = (int)game->player->player_x;
		map_y = (int)game->player->player_y;
		calculate_ray_steps(game, map_x, map_y);
		perform_dda(game, &map_x, &map_y);
		calculate_wall_height(game, map_x, map_y);
		set_wall_coordinate(game);
		set_texture_coordinate(game);
		set_wall_texture(game);
		draw_scene(game, x);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->textures->scene, 0, 0);
}
