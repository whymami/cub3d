/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ray_coordinate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:11:15 by btanir            #+#    #+#             */
/*   Updated: 2024/09/02 14:11:31 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_wall_texture(t_game *game)
{
	t_ray	*ray;

	ray = game->ray;
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->texture = game->textures->we_data;
	else if (ray->side == 0 && ray->ray_dir_x < 0)
		ray->texture = game->textures->ea_data;
	else if (ray->side == 1 && ray->ray_dir_y > 0)
		ray->texture = game->textures->no_data;
	else
		ray->texture = game->textures->so_data;
	game->ray = ray;
}

void	set_texture_coordinate(t_game *game)
{
	t_ray	*ray;

	ray = game->ray;
	ray->tex_x = (int)(ray->wall_x * (double)(TEX_WIDTH));
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = TEX_WIDTH - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = TEX_WIDTH - ray->tex_x - 1;
	game->ray = ray;
}

void	set_wall_coordinate(t_game *game)
{
	t_ray *ray;

	ray = game->ray;
	if (ray->side == 0)
		ray->wall_x = game->player->player_y + ray->perp_wall_dist
			* ray->ray_dir_y;
	else
		ray->wall_x = game->player->player_x + ray->perp_wall_dist
			* ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	game->ray = ray;
}
