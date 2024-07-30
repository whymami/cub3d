/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:15:33 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/30 20:12:14 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	parse_map(char *path, t_game *game)
{
	int	y;
	(void)path;
	y = -1;
	while (game->map->map[++y])
		printf("%s", game->map->map[y]);
	
}

static void	add_line(t_map *map, char *line)
{
	map->map = (char **)my_realloc_arr(map->map, sizeof(char *) * (map->height
				+ 1));
	map->map[map->height] = ft_strdup(line);
	map->map_copy = (char **)my_realloc_arr(map->map_copy, sizeof(char *)
			* (map->height + 1));
	map->map_copy[map->height] = ft_strdup(line);
	if (!map->map[map->height] || !map->map || !map->map_copy
		|| !map->map_copy[map->height])
		ft_exit(1, "Memory allocation failed", NULL);
	map->height++;
}

void	get_map_size(char *path)
{
	int		fd;
	char	*line;
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		ft_exit(1, "Memory allocation failed", game);
	game->map = ft_calloc(1, sizeof(t_map));
	if (!game->map)
		ft_exit(1, "Memory allocation failed", game);
	fd = open(path, O_RDONLY);
	game->map->height = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_len_not_nl(line))
			add_line(game->map, line);
		free(line);
	}
	game->map->map[game->map->height] = NULL;
	free(line);
	close(fd);
	parse_map(path, game);
}
