/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_initialize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:01:26 by btanir            #+#    #+#             */
/*   Updated: 2024/09/01 15:24:48 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycasting(t_game *game)
{
	double cameraX, rayDirX, rayDirY;
	int mapX, mapY, stepX, stepY;
	double sideDistX, sideDistY;
	double deltaDistX, deltaDistY, perpWallDist;
	int hit, side;
	int lineHeight, drawStart, drawEnd, color;
	for (int x = 0; x < WIN_WIDTH; x++)
	{
		cameraX = 2 * x / (double)WIN_WIDTH - 1;
		rayDirX = game->player->dir_x + game->player->plane_x * cameraX;
		rayDirY = game->player->dir_y + game->player->plane_y * cameraX;
		mapX = (int)game->player->player_x;
		mapY = (int)game->player->player_y;
		deltaDistX = fabs(1 / rayDirX);
		deltaDistY = fabs(1 / rayDirY);
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (game->player->player_x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->player->player_x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (game->player->player_y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->player->player_y) * deltaDistY;
		}
		hit = 0;
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (game->map->map[mapX][mapY] > 0)
				hit = 1;
		}
		perpWallDist = (side == 0) ? (mapX - game->player->player_x + (1
					- stepX) / 2) / rayDirX : (mapY - game->player->player_y
				+ (1 - stepY) / 2) / rayDirY;
		lineHeight = (int)(WIN_HEIGHT / perpWallDist);
		drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
		drawStart = (drawStart < 0) ? 0 : drawStart;
		drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
		drawEnd = (drawEnd >= WIN_HEIGHT) ? WIN_HEIGHT - 1 : drawEnd;
		color = (side == 0) ? 0xFF0000 : 0x00FF00;
		draw_scene(game, x, drawStart, drawEnd, color);
	}
	printf("player_x: %f, player_y: %f\n", game->player->player_x, game->player->player_y);
	mlx_put_image_to_window(game->mlx, game->win, game->textures->scene, 0, 0);
}

int	key_press(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == KEY_ESC)
		ft_exit(_SUCC_EXIT, "EXIT_GAME", game);
	if (keycode == KEY_W || keycode == KEY_D)
		move_player(game, 0);
	if (keycode == KEY_S || keycode == KEY_A)
		move_player(game, 1);
	if (keycode == KEY_RIGHT)
		rotate_player(game, -ROT_SPEED);
	if (keycode == KEY_LEFT)
		rotate_player(game, ROT_SPEED);
	mlx_clear_window(game->mlx, game->win);
	raycasting(game);
	return (0);
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
	game->player->dir_x = 1;
	game->player->dir_y = 0;
	game->player->plane_x = 0;
	game->player->plane_y = -0.66;
	game->textures = ft_calloc(1, sizeof(t_texture));
	if (!game->textures)
		ft_exit(1, "Memory allocation failed", game);
	create_scene(game);
	raycasting(game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_loop(game->mlx);
}
