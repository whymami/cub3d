/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:25:06 by muguveli          #+#    #+#             */
/*   Updated: 2024/08/04 19:37:00 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "lib/libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define _CUB_ERR "Invalid file extension. File must be a .cub file"

# define _SUCC_EXIT 0
# define _FINISH_GAME 1

typedef struct s_mapdata
{
	char		**data;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*ceiling;
	char		*floor;
}				t_mapdata;
typedef struct s_map
{
	char		**map;
	char		**map_copy;
	t_mapdata	*data;
	int			width;
	int			height;
}				t_map;

typedef struct s_player
{
	int			player_x;
	int			player_y;
}				t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		*map;
	t_player	*player;
}				t_game;

void			ft_exit(int err_no, char *err, t_game *game);
void			map_path_control(char *path);
void			get_map_size(char *path);
int				ft_len_not_nl(char *str);
char			**my_realloc_arr(char **ptr, size_t size);
void	free_map(char **map, int y);

#endif