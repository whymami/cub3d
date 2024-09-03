/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_initialize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:01:26 by btanir            #+#    #+#             */
/*   Updated: 2024/09/03 21:10:29 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == KEY_ESC)
		ft_exit(_SUCC_EXIT, "EXIT_GAME", game);
	else if (keycode == KEY_W)
		game->move->w = 1;
	else if (keycode == KEY_S)
		game->move->s = 1;
	else if (keycode == KEY_A)
		game->move->a = 1;
	else if (keycode == KEY_D)
		game->move->d = 1;
	else if (keycode == KEY_RIGHT)
		game->move->right = 1;
	else if (keycode == KEY_LEFT)
		game->move->left = 1;
	else if (keycode == SHIFT)
	{
		game->move->shift = 1;
		game->player->boost = 2;
	}
	return (0);
}

int	key_release(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == KEY_W)
		game->move->w = 0;
	else if (keycode == KEY_S)
		game->move->s = 0;
	else if (keycode == KEY_A)
		game->move->a = 0;
	else if (keycode == KEY_D)
		game->move->d = 0;
	else if (keycode == KEY_RIGHT)
		game->move->right = 0;
	else if (keycode == KEY_LEFT)
		game->move->left = 0;
	else if (keycode == SHIFT)
	{
		game->move->shift = 0;
		game->player->boost = 1;
	}
	return (0);
}

int	key_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_clear_window(game->mlx, game->win);
	if (game->move->w)
		move_player(game, game->player->dir_x * MOVE_SPEED
			* game->player->boost, game->player->dir_y * MOVE_SPEED
			* game->player->boost);
	if (game->move->s)
		move_player(game, -(game->player->dir_x * MOVE_SPEED),
			-(game->player->dir_y * MOVE_SPEED));
	if (game->move->a)
		move_player(game, -(game->player->dir_y * MOVE_SPEED),
			(game->player->dir_x * MOVE_SPEED));
	if (game->move->d)
		move_player(game, (game->player->dir_y * MOVE_SPEED), -(game->player->dir_x
				* MOVE_SPEED));
	if (game->move->right)
		rotate_player(game, -ROT_SPEED);
	if (game->move->left)
		rotate_player(game, ROT_SPEED);
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
	game->move = ft_calloc(1, sizeof(t_move));
	if (!game->move)
		ft_exit(1, "malloc move error", game);
	game->player->boost = 1;
	mlx_hook(game->win, 2, 0, key_press, game);
	mlx_hook(game->win, 3, 0, key_release, game);
	mlx_loop_hook(game->mlx, key_hook, game);
	mlx_loop(game->mlx);
}
