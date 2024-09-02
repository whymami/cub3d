/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_initialize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:01:26 by btanir            #+#    #+#             */
/*   Updated: 2024/09/02 18:16:58 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		rotate_player(game, ROT_SPEED);
	if (keycode == KEY_LEFT)
		rotate_player(game, -ROT_SPEED);
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
	player_start_dir(game);
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
