/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:49:38 by btanir            #+#    #+#             */
/*   Updated: 2024/09/01 18:27:57 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_scene(t_game *game)
{
	t_texture	*texture;

	texture = game->textures;
	texture->scene = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	texture->scene_data = (int *)mlx_get_data_addr(texture->scene,
			&texture->bits_per_pixel, &texture->size_line, &texture->endian);
}

void	draw_scene(t_game *game, int x, int draw_start, int draw_end, int color)
{
	t_texture	*texture;
	int			y;

	texture = game->textures;
	y = 0;
	while (y <= draw_start)
	{
		texture->scene_data[y * WIN_WIDTH + x] = 0x0FFFF00;
		y++;
	}
	y = draw_start;
	while (y++ < draw_end)
	{
		texture->scene_data[y * WIN_WIDTH + x] = color;
	}
	while (y < WIN_HEIGHT)
	{
		texture->scene_data[y * WIN_WIDTH + x] = 0x00000FF;
		y++;
	}
}
