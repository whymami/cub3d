/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_initialize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:01:26 by btanir            #+#    #+#             */
/*   Updated: 2024/09/02 15:48:51 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycasting(t_game *game)
{
	int		x;
	double	cameraX;
	int		mapX;
	int		mapY;
	double	deltaDistX;
	double	deltaDistY;
	int		hit;

	for (x = 0; x < WIN_WIDTH; x++)
	{
		cameraX = 2 * x / (double)WIN_WIDTH - 1;
		game->ray->ray_dir_x = game->player->dir_x + game->player->plane_x
			* cameraX;
		game->ray->ray_dir_y = game->player->dir_y + game->player->plane_y
			* cameraX;
		mapX = (int)game->player->player_x;
		mapY = (int)game->player->player_y;
		deltaDistX = fabs(1 / game->ray->ray_dir_x);
		deltaDistY = fabs(1 / game->ray->ray_dir_y);
		double sideDistX, sideDistY;
		int stepX, stepY;
		if (game->ray->ray_dir_x < 0)
		{
			stepX = -1;
			sideDistX = (game->player->player_x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->player->player_x) * deltaDistX;
		}
		if (game->ray->ray_dir_y < 0)
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
			if (game->ray->side_dist_x < game->ray->side_dist_y)
			{
				game->ray->side_dist_x += game->ray->side_dist_x;
				mapX += game->ray->step_x;
				game->ray->side = 0;
			}
			else
			{
				game->ray->side_dist_y += game->ray->side_dist_y;
				mapY += game->ray->step_y;
				game->ray->side = 1;
			}
			if (game->map->map[mapX][mapY] == '1')
				hit = 1;
		}
		if (game->ray->side == 0)
			game->ray->perp_wall_dist = (mapX - game->player->player_x + (1
						- stepX) / 2) / game->ray->ray_dir_x;
		else
			game->ray->perp_wall_dist = (mapY - game->player->player_y + (1
						- stepY) / 2) / game->ray->ray_dir_y;
		game->ray->line_height = (int)(WIN_HEIGHT / game->ray->perp_wall_dist);
		game->ray->draw_start = -game->ray->line_height / 2 + WIN_HEIGHT / 2;
		if (game->ray->draw_start < 0)
			game->ray->draw_start = 0;
		game->ray->draw_end = game->ray->line_height / 2 + WIN_HEIGHT / 2;
		if (game->ray->draw_end >= WIN_HEIGHT)
			game->ray->draw_end = WIN_HEIGHT - 1;
		set_wall_coordinate(game);
		set_texture_coordinate(game);
		set_wall_texture(game);
		draw_scene(game, x);
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
	init_textures(game);
	create_scene(game);
	init_ray(game);
	raycasting(game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	// mlx_hook(game->win,  1,0, key_release, game);
	// mlx_hook(game->win, 17, 1L << 17, ft_exit, game);
	// mlx_loop_hook(game->mlx, key_press, game);
	mlx_loop(game->mlx);
}
