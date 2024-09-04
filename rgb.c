/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:37:03 by btanir            #+#    #+#             */
/*   Updated: 2024/09/04 16:22:31 by muguveli         ###   ########.fr       */
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

static void	rgb_control_check(t_game *game, char ***f, char ***c)
{
	t_mapdata	*dt;
	char		*line;

	dt = game->map->data;
	if (!dt->floor || !dt->ceiling)
		ft_exit(1, "Invalid floor or ceiling color", game);
	comma_count(dt->ceiling, game);
	comma_count(dt->floor, game);
	line = ft_strtrim(dt->floor, " ");
	if (!line)
		ft_exit(1, "Invalid floor color", game);
	*f = ft_split(line + 2, ',');
	free(line);
	line = ft_strtrim(dt->ceiling, " ");
	if (!line)
		ft_exit(1, "Invalid floor color", game);
	*c = ft_split(line + 2, ',');
	free(line);
	if (arr_len(*f) != 3 || arr_len(*c) != 3)
		ft_exit(1, "Invalid rgb values", game);
}

void	rgb_control(t_game *game)
{
	char		**f;
	char		**c;
	t_mapdata	*dt;
	int			i;

	i = -1;
	rgb_control_check (game, &f, &c);
	dt = game->map->data;
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
