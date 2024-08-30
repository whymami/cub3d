/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:15:33 by muguveli          #+#    #+#             */
/*   Updated: 2024/08/30 19:44:23 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_dir(t_game *game, int x, int y, char dir)
{
	game->player->player_x = x;
	game->player->player_y = y;
	game->player->player_dir = dir;
	game->player->dir_count++;
	if (game->player->dir_count > 1)
		ft_exit(1, "Multiple player directions", game);
}

void	first_last_line(t_game *game)
{
	int	i;

	i = -1;
	while (game->map->map[0][++i])
		if (game->map->map[0][i] != WALL)
			ft_exit(1, "ilk satır 1 olmalı", game);
	i = -1;
	while (game->map->map[game->map->height - 9][++i])
		if (game->map->map[game->map->height - 9][i] != WALL)
			ft_exit(1, "son satır 1 olmalı", game);
}

void	star_helper(t_game *game, int y, int x)
{
	if (x > 0 && !(game->map->ff_map[y][x - 1] == WALL || game->map->ff_map[y][x - 1] == STAR))
		ft_exit(1, "Map is not closed left", game);
	if (x < (int)ft_strlen(game->map->ff_map[y]) - 1 && !(game->map->ff_map[y][x + 1] == WALL || game->map->ff_map[y][x + 1] == STAR))
		ft_exit(1, "Map is not closed right", game);
	if (y > 0 && !(game->map->ff_map[y - 1][x] == WALL || game->map->ff_map[y - 1][x] == STAR))
		ft_exit(1, "Map is not closed up", game);
	if (y > 0 && !(game->map->ff_map[y + 1][x] == WALL || game->map->ff_map[y + 1][x] == STAR))
		ft_exit(1, "Map is not closed down", game);
}

void	star_control(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (++y < game->map->height - 1)
	{
		x = 0;
		while (++x < (int)ft_strlen(game->map->ff_map[y]))
			if (game->map->ff_map[y][x] == '*')
				star_helper(game, y, x);
	}
}

void border_control(t_game *game)
{
	int	y;
	int	x;

	y = -1;
	while (++y < game->map->height)
	{
		x = -1;
		while (++x < (int)ft_strlen(game->map->ff_map[y]))
			if (y == 0 || y == game->map->height - 1 || x == 0 || x == (int)ft_strlen(game->map->ff_map[y]) - 1)
				if (game->map->ff_map[y][x] != WALL && game->map->ff_map[y][x] != STAR)
					ft_exit(1, "Map is not closed from border", game);
	}
}

void	frame_control(t_game *game)
{
	int	y;
	int	x;

	game->map->ff_map = ft_calloc(game->map->height + 1, sizeof(char *));
	if (!game->map->ff_map)
		ft_exit(1, "malloc error", game);
	y = -1;
	while (++y < game->map->height)
	{
		game->map->ff_map[y] = malloc(game->map->max_width * sizeof(char));
		x = -1;
		while (game->map->map[y][++x])
		{
			if (game->map->map[y][x] == SPACE)
				game->map->ff_map[y][x] = '*';
			else
				game->map->ff_map[y][x] = game->map->map[y][x];
		}
		while (x < game->map->max_width - 1)
			game->map->ff_map[y][x++] = '*';
		game->map->ff_map[y][x] = '\0';
	}
	star_control(game);
	border_control(game);
}

void	map_control(t_game *game)
{
	int	y;
	int	x;

	y = -1;
	game->player = ft_calloc(1, sizeof(t_player));
	if (!game->player)
		ft_exit(1, "Memory allocation failed", game);
	while (++y < game->map->height - 1) // nullı almasın diye
	{
		x = -1;
		if (ft_len_not_nl(game->map->map[y]) == 0)
			ft_exit(1, "The map can not be devided", game);
		while (++x < (int)ft_strlen(game->map->map[y]))
		{
			if (ft_strchr(ELEMENTS, game->map->map[y][x]) == 0 && printf("%c\n",
					game->map->map[y][x]))
				ft_exit(1, "Invalid map element", game);
			if (ft_strchr(DIR, game->map->map[y][x]))
				player_dir(game, x, y, game->map->map[y][x]);
		}
	}
	frame_control(game);
}

void	map(char *path)
{
	t_game	*game;
	int		y;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		ft_exit(1, "Memory allocation failed", game);
	y = get_map_height(path);
	map_init(game, y);
	game->map->height = y;
	copy_map(game, path);
	parse_copymap(game);
	map_control(game);
}
