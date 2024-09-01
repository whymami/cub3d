/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:25:06 by muguveli          #+#    #+#             */
/*   Updated: 2024/09/01 19:54:28 by btanir           ###   ########.fr       */
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
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define MOVE_SPEED 0.09
# define ROT_SPEED 0.09
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

# define KEY_ESC 53
# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124

typedef struct s_texture
{
	void		*scene;
	int			*scene_data;
	void		*no;
	int 		*no_data;
	void		*so;
	int			*so_data;
	void		*we;
	int			*we_data;
	void		*ea;
	int			*ea_data;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
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
	int			ceiling_rgb;
	int			floor_rgb;
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
	double		player_x;
	double		player_y;
	char		player_dir;
	int			dir_count;
	double		dir_x;
	double		dir_y;
	double		plane_y;
	double		plane_x;
}				t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		*map;
	t_player	*player;
	t_texture	*textures;
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
void			move_player(t_game *game, double next_x, double next_y);
void			rotate_player(t_game *game, double rot_speed);
void			create_scene(t_game *game);
void			draw_scene(t_game *game, int x, int draw_start, int draw_end,
					int color);

#endif