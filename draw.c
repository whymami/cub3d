/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:49:38 by btanir            #+#    #+#             */
/*   Updated: 2024/09/04 16:22:05 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_scene(t_game *game)
{
	t_texture	*tex;

	tex = game->textures;
	tex->scene = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!tex->scene)
		ft_exit(2, "tex->scene", game);
	tex->scene_data = (int *)mlx_get_data_addr(tex->scene, &tex->bits_per_pixel,
			&tex->size_line, &tex->endian);
	if (!tex->scene_data)
		ft_exit(2, "tex->scene_data", game);
	game->textures = tex;
}

void	draw_scene(t_game *game, int x)
{
	t_ray	*ray;
	int		y;

	ray = game->ray;
	ray->step = 1.0 * TEX_HEIGHT / ray->line_height;
	ray->tex_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2)
		* ray->step;
	y = -1;
	while (++y <= ray->draw_start)
		game->textures->scene_data[y * WIN_WIDTH
			+ x] = game->map->data->ceiling_rgb;
	while (y < ray->draw_end)
	{
		ray->tex_y = (int)ray->tex_pos & (TEX_HEIGHT - 1);
		ray->tex_pos += ray->step;
		ray->color = ray->texture[TEX_HEIGHT * ray->tex_y + ray->tex_x];
		game->textures->scene_data[y * WIN_WIDTH + x] = ray->color;
		y++;
	}
	while (y < WIN_HEIGHT)
	{
		game->textures->scene_data[y * WIN_WIDTH
			+ x] = game->map->data->floor_rgb;
		y++;
	}
}
