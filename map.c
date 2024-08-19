/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:15:33 by muguveli          #+#    #+#             */
/*   Updated: 2024/08/19 15:45:59 by btanir           ###   ########.fr       */
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

void	map_control(t_game *game)
{
	int	y;
	int	x;

	y = -1;
	game->player = ft_calloc(1, sizeof(t_player));
	if (!game->player)
		ft_exit(1, "Memory allocation failed", game);
	printf("%s", game->map->map[0]);

	while (++y < game->map->height - 7)
	{
		x = -1;
		while (++x < ft_len_not_nl(game->map->map[y]))
		{
			if (ft_strchr(ELEMENTS, game->map->map[y][x]) == 0)
				ft_exit(1, "Invalid map element", game);
			if (ft_strchr(DIR, game->map->map[y][x]))
				player_dir(game, x, y, game->map->map[y][x]);
		}
	}
}

int	arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
int	ft_str_digit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

void	floor_ceil_control(char *str, t_game *game)
{
	if (ft_str_digit(str))
	{
		if (ft_atoi(str) < 0 || ft_atoi(str) > 255)
			ft_exit(1, "rgb value cannot be less than 0 or greater than 255",
				game);
	}
	else
		ft_exit(1, "Invalid rgb value", game);
}

void	rgb_control(t_game *game)
{
	char	**f;
	char	**c;
	int		i;

	f = ft_split(game->map->data->floor + 2, ',');
	c = ft_split(game->map->data->ceiling + 2, ',');
	if (arr_len(f) != 3 || arr_len(c) != 3) // free f and c
		ft_exit(1, "Invalid rgb values", game);
	i = -1;
	while (++i < 3)
	{
		floor_ceil_control(f[i], game);
		floor_ceil_control(c[i], game);
	}
}

void	data_control(t_game *game)
{
	char	*line;
	int		fd;
	int		i;

	i = -1;
	while (++i < 4)
	{
		fd = open(game->map->data->data[i] + 3, O_RDONLY);
		if (fd < 0)
			ft_exit(1, "Invalid data path", game);
		line = get_next_line(fd);
		close(fd);
		if (line == NULL)
			ft_exit(1, "NO Path not found\n", game);
	}
	rgb_control(game);
}

void	data_args_control(t_game *game)
{
	if (ft_strncmp(game->map->map_copy[0], "NO", 2) == 0)
		game->map->data->no = game->map->data->data[0];
	else
		ft_exit(1, "Invalid map data", game);
	if (ft_strncmp(game->map->map_copy[1], "SO", 2) == 0)
		game->map->data->so = game->map->data->data[1];
	else
		ft_exit(1, "Invalid map data", game);
	if (ft_strncmp(game->map->map_copy[2], "WE", 2) == 0)
		game->map->data->we = game->map->data->data[2];
	else
		ft_exit(1, "Invalid map data", game);
	if (ft_strncmp(game->map->map_copy[3], "EA", 2) == 0)
		game->map->data->ea = game->map->data->data[3];
	else
		ft_exit(1, "Invalid map data", game);
	if (ft_strncmp(game->map->map_copy[4], "F", 1) == 0)
		game->map->data->floor = game->map->data->data[4];
	else
		ft_exit(1, "Invalid map data", game);
	if (ft_strncmp(game->map->map_copy[5], "C", 1) == 0)
		game->map->data->ceiling = game->map->data->data[5];
	else
		ft_exit(1, "Invalid map data", game);
	data_control(game);
}

static void	parse_copymap(t_game *game)
{
	int	y;

	y = -1;
	while (++y < game->map->height)
	{
		if (y < 6)
			game->map->data->data[y] = ft_substr(game->map->map_copy[y], 0,
					ft_len_not_nl(game->map->map_copy[y]));
		else
			game->map->map[y - 6] = ft_substr(game->map->map_copy[y], 0,
					ft_len_not_nl(game->map->map_copy[y]));

	}
	data_args_control(game);
}
void	map_init(t_game *game, int y)
{
	game->map = ft_calloc(1, sizeof(t_map));
	if (!game->map)
		ft_exit(1, "Memory allocation failed", game);
	game->map->map = ft_calloc(y - 5, sizeof(char *));
	game->map->data = ft_calloc(1, sizeof(t_mapdata));
	if (!game->map->data)
		ft_exit(1, "Memory allocation failed", game);
	game->map->map_copy = ft_calloc(y, sizeof(char *));
	if (!game->map->map_copy)
		ft_exit(1, "Memory allocation failed", game);
	game->map->data->data = ft_calloc(7, sizeof(char *));
	if (!game->map->data->data)
		ft_exit(1, "Memory allocation failed", game);
}
int	get_map_height(char *path)
{
	int		fd;
	char	*line;
	int		y;

	fd = open(path, O_RDONLY);
	y = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_len_not_nl(line))
			y++;
		free(line);
	}
	free(line);
	close(fd);
	return (y);
}

void	copy_map(t_game *game, char *path)
{
	int		fd;
	char	*line;
	int		y;

	fd = open(path, O_RDONLY);
	y = -1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_len_not_nl(line))
			game->map->map_copy[++y] = ft_strdup(line);
		free(line);
	}
	free(line);
	close(fd);
}

void	get_map_size(char *path, t_game *game)
{
	int		y;

	y = get_map_height(path);
	map_init(game, y);
	game->map->height = y;
	copy_map(game, path);
	parse_copymap(game);
	map_control(game);
}
