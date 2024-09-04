/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:57:06 by btanir            #+#    #+#             */
/*   Updated: 2024/09/04 16:22:18 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	copy_map(t_game *game, char *path)
{
	int		fd;
	char	*line;
	int		y;

	fd = open(path, O_RDONLY);
	y = -1;
	game->map->max_width = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if ((int)ft_strlen(line) > game->map->max_width)
			game->map->max_width = ft_strlen(line);
		game->map->map_copy[++y] = ft_strdup(line);
		free(line);
	}
	game->map->map_copy[++y] = NULL;
	free(line);
	close(fd);
}

void	game_map_copy(t_game *game)
{
	int	y;
	int	x;

	y = game->map->data->data_height;
	x = -1;
	while (++x < game->map->height)
	{
		game->map->map[x] = ft_substr(game->map->map_copy[y], 0,
				ft_len_not_nl(game->map->map_copy[y]));
		y++;
	}
	game->map->map[x] = NULL;
}

void	parse_copymap(t_game *game)
{
	data_copy(game);
	data_args_control(game);
	update_data_height(game);
	game_map_copy(game);
}
