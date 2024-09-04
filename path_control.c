/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:14:09 by muguveli          #+#    #+#             */
/*   Updated: 2024/09/04 16:22:28 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	cub_control(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (path[len - 4] == '.' && path[len - 3] == 'c' && path[len - 2] == 'u'
		&& path[len - 1] == 'b')
		return (1);
	return (0);
}

void	map_path_control(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	close(fd);
	if (cub_control(path))
	{
		if (fd >= 3)
			map(path);
		else
			ft_exit(1, "Map not found", NULL);
	}
	else
		ft_exit(1, _CUB_ERR, NULL);
}
