/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:27:07 by muguveli          #+#    #+#             */
/*   Updated: 2024/08/19 15:53:20 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_exit(int err_no, char *err, t_game *game)
{
	(void)game;
	if (err_no == _SUCC_EXIT || err_no == _FINISH_GAME)
	{
		ft_putstr_fd(err, 2);
		exit(0);
	}
	ft_putstr_fd("ERROR: Excited With (", 2);
	ft_putnbr_fd(err_no, 2);
	ft_putstr_fd("): ", 2);
	ft_putendl_fd(err, 2);
	exit(err_no);
}

int mlx_initialize(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (1);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (!game->win)
		return (1);
	
	return (0);
}

int main(int argc, char **argv)
{
	t_game game = {0};

	if (argc == 2 && argv[1][0])
		map_path_control(argv[1], &game);
	else
		ft_exit(1, "Invalid number of arguments", NULL);
	if (mlx_initialize(&game))
		return (1);

	mlx_loop(game.mlx);
}
