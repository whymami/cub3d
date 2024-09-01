/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_initialize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:01:26 by btanir            #+#    #+#             */
/*   Updated: 2024/09/01 19:54:54 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycasting(t_game *game)
{
	int		x;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	deltaDistX;
	double	deltaDistY;
	int		hit;
	int		side;
	double	perpWallDist;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	double	wallX;
	int		texX;
	double	step;
	double	texPos;
	int		texY;
	int		color;
	void	*texture;
	int		y;

	for (x = 0; x < WIN_WIDTH; x++)
	{
		cameraX = 2 * x / (double)WIN_WIDTH - 1;
		rayDirX = game->player->dir_x + game->player->plane_x * cameraX;
		rayDirY = game->player->dir_y + game->player->plane_y * cameraX;
		mapX = (int)game->player->player_x;
		mapY = (int)game->player->player_y;
		deltaDistX = fabs(1 / rayDirX);
		deltaDistY = fabs(1 / rayDirY);
		double sideDistX, sideDistY;
		int stepX, stepY;
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
			if (game->map->map[mapX][mapY] == '1')
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - game->player->player_x + (1 - stepX) / 2)
				/ rayDirX;
		else
			perpWallDist = (mapY - game->player->player_y + (1 - stepY) / 2)
				/ rayDirY;
		lineHeight = (int)(WIN_HEIGHT / perpWallDist);
		drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
		if (drawEnd >= WIN_HEIGHT)
			drawEnd = WIN_HEIGHT - 1;
		// Duvarın X koordinatını hesapla
		if (side == 0)
			wallX = game->player->player_y + perpWallDist * rayDirY;
		else
			wallX = game->player->player_x + perpWallDist * rayDirX;
		wallX -= floor(wallX);
		// Texture X koordinatını hesapla
		texX = (int)(wallX * (double)(TEX_WIDTH));
		if (side == 0 && rayDirX > 0)
			texX = TEX_WIDTH - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = TEX_WIDTH - texX - 1;
		// Texturu seç
		if (side == 0 && rayDirX > 0)
			texture = game->textures->we_data;
		else if (side == 0 && rayDirX < 0)
			texture = game->textures->ea_data;
		else if (side == 1 && rayDirY > 0)
			texture = game->textures->no_data;
		else
			texture = game->textures->so_data;
		// Texture boyuna göre adım belirle
		step = 1.0 * TEX_HEIGHT / lineHeight;
		texPos = (drawStart - WIN_HEIGHT / 2 + lineHeight / 2) * step;
		y = 0;
		while (y <= drawStart)
		{
			game->textures->scene_data[y * WIN_WIDTH + x] = game->map->data->ceiling_rgb;
			y++;
		}
		y = drawStart;
		while (y < drawEnd)
		{
			texY = (int)texPos & (TEX_HEIGHT - 1);
			texPos += step;
			color = ((int *)texture)[TEX_HEIGHT * texY + texX];
			game->textures->scene_data[y * WIN_WIDTH + x] = color;
			y++;
		}
		while (y < WIN_HEIGHT)
		{
			game->textures->scene_data[y * WIN_WIDTH + x] = game->map->data->floor_rgb;
			y++;
		}
	}
	mlx_put_image_to_window(game->mlx, game->win, game->textures->scene, 0, 0);
}

int	key_press(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == KEY_ESC)
		ft_exit(_SUCC_EXIT, "EXIT_GAME", game);
	if (keycode == KEY_W)
		move_player(game, game->player->dir_x * MOVE_SPEED, game->player->dir_y
			* MOVE_SPEED);
	if (keycode == KEY_S)
		move_player(game, -(game->player->dir_x * MOVE_SPEED),
			-(game->player->dir_y * MOVE_SPEED));
	if (keycode == KEY_A)
		move_player(game, -(game->player->dir_y * MOVE_SPEED),
			(game->player->dir_x * MOVE_SPEED));
	if (keycode == KEY_D)
		move_player(game, game->player->dir_y * MOVE_SPEED,
			-(game->player->dir_x * MOVE_SPEED));
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
	game->textures->so = mlx_xpm_file_to_image(game->mlx, game->map->data->so
			+ 3, &x, &y);
	if (!game->textures->so)
		ft_exit(1, "Error loading east texture", game);
	game->textures->we = mlx_xpm_file_to_image(game->mlx, game->map->data->we
			+ 3, &x, &y);
	game->textures->ea = mlx_xpm_file_to_image(game->mlx, game->map->data->ea
			+ 3, &x, &y);
	game->textures->no = mlx_xpm_file_to_image(game->mlx, game->map->data->no
			+ 3, &x, &y);
	game->textures->no_data = (int *)mlx_get_data_addr(game->textures->no,
			&game->textures->bits_per_pixel, &game->textures->size_line,
			&game->textures->endian);
	game->textures->so_data = (int *)mlx_get_data_addr(game->textures->so,
			&game->textures->bits_per_pixel, &game->textures->size_line,
			&game->textures->endian);
	game->textures->we_data = (int *)mlx_get_data_addr(game->textures->we,
			&game->textures->bits_per_pixel, &game->textures->size_line,
			&game->textures->endian);
	game->textures->ea_data = (int *)mlx_get_data_addr(game->textures->ea,
			&game->textures->bits_per_pixel, &game->textures->size_line,
			&game->textures->endian);
	if (!game->textures)
		ft_exit(1, "Memory allocation failed", game);
	create_scene(game);
	raycasting(game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_loop(game->mlx);
}
