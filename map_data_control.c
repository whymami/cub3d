/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_data_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:56:44 by muguveli          #+#    #+#             */
/*   Updated: 2024/09/03 16:13:28 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	floor_ceil_control(char *str, t_game *game)
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

void	free_arr(char **arr)
{
	int	i;

	i = -1;
	if (arr)
	{
		if (*arr)
		{
			while (arr[++i])
				free(arr[i]);
		}
		free(arr);
	}
}

static void	rgb_control(t_game *game)
{
	char		**f;
	char		**c;
	int			i;
	t_mapdata	*dt;

	dt = game->map->data;
	f = ft_split(dt->floor + 2, ','); // trim
	c = ft_split(dt->ceiling + 2, ',');
	if (arr_len(f) != 3 || arr_len(c) != 3)
		ft_exit(1, "Invalid rgb values", game);
	i = -1;
	while (++i < 3)
	{
		floor_ceil_control(f[i], game);
		floor_ceil_control(c[i], game);
	}
	dt->floor_rgb = ft_atoi(f[0]) << 16 | ft_atoi(f[1]) << 8 | ft_atoi(f[2]);
	dt->ceiling_rgb = ft_atoi(c[0]) << 16 | ft_atoi(c[1]) << 8 | ft_atoi(c[2]);
	free_arr(f);
	free_arr(c);
}

static void	data_control(t_game *game)
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
		{
			free(line);
			ft_exit(1, "NO Path not found\n", game);
		}
		free(line);
	}
	rgb_control(game);
}

static void	data_arg_type(char *check_str, t_game *game, int i)
{
	if (ft_strncmp(check_str, "NO", 2) == 0)
		game->map->data->no = game->map->data->data[i];
	else if (ft_strncmp(check_str, "SO", 2) == 0)
		game->map->data->so = game->map->data->data[i];
	else if (ft_strncmp(check_str, "WE", 2) == 0)
		game->map->data->we = game->map->data->data[i];
	else if (ft_strncmp(check_str, "EA", 2) == 0)
		game->map->data->ea = game->map->data->data[i];
	else if (ft_strncmp(check_str, "F", 1) == 0)
		game->map->data->floor = game->map->data->data[i];
	else if (ft_strncmp(check_str, "C", 1) == 0)
		game->map->data->ceiling = game->map->data->data[i];
	else
		ft_exit(1, "Invalid map data", game);
}

void	data_args_control(t_game *game)
{
	int	i;

	i = -1;
	while (game->map->data->data[++i])
		if (ft_len_not_nl(game->map->data->data[i]))
			data_arg_type(game->map->data->data[i], game, i);	
	data_control(game);
}
