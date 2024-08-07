/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:15:33 by muguveli          #+#    #+#             */
/*   Updated: 2024/08/07 14:42:24 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_control(t_game *game)
{
	int y;

	y = -1;
	while (game->map->data->data[++y])
		printf("%s", game->map->data->data[y]);
	y = -1;
	while (game->map->map[++y])
		printf("%s", game->map->map[y]);
}

void	data_control(t_game *game)
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
}

static void	parse_copymap(t_game *game)
{
	int	y;

	y = -1;
	while (++y < game->map->height)
	{
		if (y < 6)
			game->map->data->data[y] = ft_strdup(game->map->map_copy[y]);
		else
			game->map->map[y - 6] = ft_strdup(game->map->map_copy[y]);
	}
	data_control(game);
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

void	get_map_size(char *path)
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
