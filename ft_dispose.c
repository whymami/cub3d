/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dispose.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:28:10 by btanir            #+#    #+#             */
/*   Updated: 2024/09/03 23:21:35 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_dispose_texture(t_game *game)
{
	if (game->textures)
	{
		if (game->textures->scene)
			mlx_destroy_image(game->mlx, game->textures->scene);
		if (game->textures->no)
			mlx_destroy_image(game->mlx, game->textures->no);
		if (game->textures->so)
			mlx_destroy_image(game->mlx, game->textures->so);
		if (game->textures->we)
			mlx_destroy_image(game->mlx, game->textures->we);
		if (game->textures->ea)
			mlx_destroy_image(game->mlx, game->textures->ea);
		free(game->textures);
	}
}

void	ft_dispose_data_map(t_game *game)
{
	int	i;

	i = -1;
	if (game->map->map)
	{
		while (game->map->map[++i])
			free(game->map->map[i]);
		free(game->map->map);
	}
	i = -1;
	if (game->map->data)
	{
		if (game->map->data->data)
		{
			while (++i < 7)
				if (game->map->data->data[i])
					free(game->map->data->data[i]);
			free(game->map->data->data);
		}
		free(game->map->data);
	}
}

void	ft_dispose_map(t_game *game)
{
	int	i;

	if (game->map)
	{
		if (game->map->map_copy)
		{
			i = 0;
			while (game->map->map_copy[i])
				free(game->map->map_copy[i++]);
			free(game->map->map_copy);
		}
		if (game->map->ff_map)
		{
			i = -1;
			while (game->map->ff_map[++i])
				free(game->map->ff_map[i]);
			free(game->map->ff_map);
		}
		free(game->map);
	}
}

void	ft_dispose(t_game *game)
{
	if (!game)
		return ;
	if (game->player)
		free(game->player);
	if (game->ray)
		free(game->ray);
	if (game->move)
		free(game->move);
	ft_dispose_map(game);
	ft_dispose_texture(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
}

void	ft_exit(int err_no, char *err, t_game *game)
{
	if (game)
	{
		ft_dispose(game);
		free(game);
	}
	system("leaks cub3d");
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
