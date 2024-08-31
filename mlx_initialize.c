/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_initialize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:01:26 by btanir            #+#    #+#             */
/*   Updated: 2024/08/31 13:14:16 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor_sky(t_game *game, int x, int y)
{
	int	*data;
	int	bits_per_pixel;
	int	size_line;
	int	endian;

	game->texture->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	data = (int *)mlx_get_data_addr(game->texture->img, &bits_per_pixel,
			&size_line, &endian);
	x = -1;
	while (++x < WIN_WIDTH)
	{
		y = -1;
		while (++y < WIN_HEIGHT)
		{
			if (y < WIN_HEIGHT / 2)
				data[y * WIN_WIDTH + x] = 0x0FFFF00;
			else
				data[y * WIN_WIDTH + x] = 0x00000FF;
		}
	}
}

void	mlx_initialize(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	game->mlx = mlx_init();
	if (!game->mlx)
		ft_exit(1, "mlx_init() error", game);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (!game->win)
		ft_exit(1, "mlx_new_window() error", game);
	game->texture = ft_calloc(1, sizeof(t_texture));
	draw_floor_sky(game, x, y);
	mlx_put_image_to_window(game->mlx, game->win, game->texture->img, 0, 0);
	mlx_loop(game->mlx);
}
