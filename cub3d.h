/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:25:06 by muguveli          #+#    #+#             */
/*   Updated: 2024/08/31 13:08:28 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "lib/libft/libft.h"
# include "lib/mlx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define _CUB_ERR "Invalid file extension. File must be a .cub file"

# define _SUCC_EXIT 0
# define _FINISH_GAME 1

# define WIN_HEIGHT 720
# define WIN_WIDTH 1280
# define WIN_TITLE "CUB3D"

# define ELEMENTS "10NSEW "
# define DIR "NSEW"

# define WALL '1'
# define GROUND '0'
# define NORTH 'N'
# define SOUTH 'S'
# define EAST 'E'
# define WEST 'W'
# define SPACE ' '
# define STAR '*'

typedef struct	s_texture
{
	void	*img;
	void	*wall;
}				t_texture;

typedef struct s_mapdata
{
	char		**data;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*ceiling;
	char		*floor;
	int			data_height;
}				t_mapdata;

typedef struct s_map
{
	char		**map;
	char		**map_copy;
	int			max_width;
	char		**ff_map;
	t_mapdata	*data;
	int			width;
	int			height;
}				t_map;

typedef struct s_player
{
	int			player_x;
	int			player_y;
	char		player_dir;
	int			dir_count;
}				t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		*map;
	t_player	*player;
	t_texture	*texture;
}				t_game;

void			ft_exit(int err_no, char *err, t_game *game);
void			map_path_control(char *path);
void			map(char *path);
int				ft_len_not_nl(char *str);
char			**my_realloc_arr(char **ptr, size_t size);
void			free_map(char **map, int y);

void			map_init(t_game *game, int y);
void			copy_map(t_game *game, char *path);
void			parse_copymap(t_game *game);
void			data_args_control(t_game *game);
int				get_map_height(char *path);
int				ft_str_digit(char *str);
int				arr_len(char **arr);
void			mlx_initialize(t_game *game);

#endif