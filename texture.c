/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 09:49:41 by btanir            #+#    #+#             */
/*   Updated: 2024/09/04 16:22:35 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_textures(t_game *game)
{
	int			x;
	int			y;
	t_texture	*tex;

	tex = game->textures;
	tex = ft_calloc(1, sizeof(t_texture));
	if (!game->map)
		ft_exit(1, "Memory allocation failed", game);
	tex->so = mlx_xpm_file_to_image(game->mlx, game->map->data->so + 3, &x, &y);
	tex->we = mlx_xpm_file_to_image(game->mlx, game->map->data->we + 3, &x, &y);
	tex->ea = mlx_xpm_file_to_image(game->mlx, game->map->data->ea + 3, &x, &y);
	tex->no = mlx_xpm_file_to_image(game->mlx, game->map->data->no + 3, &x, &y);
	if (!tex->so || !tex->ea || !tex->no || !tex->we)
		ft_exit(1, "Error loading texture", game);
	tex->no_data = (int *)mlx_get_data_addr(tex->no, &tex->bits_per_pixel,
			&tex->size_line, &tex->endian);
	tex->so_data = (int *)mlx_get_data_addr(tex->so, &tex->bits_per_pixel,
			&tex->size_line, &tex->endian);
	tex->we_data = (int *)mlx_get_data_addr(tex->we, &tex->bits_per_pixel,
			&tex->size_line, &tex->endian);
	tex->ea_data = (int *)mlx_get_data_addr(tex->ea, &tex->bits_per_pixel,
			&tex->size_line, &tex->endian);
	if (!tex->no_data || !tex->so_data || !tex->we_data || !tex->ea_data)
		ft_exit(1, "Get texture addr error", game);
	game->textures = tex;
}
