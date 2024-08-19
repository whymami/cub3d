/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:25:06 by muguveli          #+#    #+#             */
/*   Updated: 2024/08/19 15:50:41 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "lib/libft/libft.h"
#include "lib/mlx/mlx.h"
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define _CUB_ERR "Invalid file extension. File must be a .cub file"

#define _SUCC_EXIT 0
#define _FINISH_GAME 1

#define ELEMENTS "10NSEW "
#define DIR "NSEW"

#define WALL '1'
#define GROUND '0'
#define NORTH 'N'
#define SOUTH 'S'
#define EAST 'E'
#define WEST 'W'
#define SPACE ' '

#define WIN_TITLE "CUB3D"
#define WIN_WIDTH 1080
#define WIN_HEIGHT 720

typedef struct s_mapdata
{
	char **data;
	char *no;
	char *so;
	char *we;
	char *ea;
	char *ceiling;
	char *floor;
} t_mapdata;
typedef struct s_map
{
	char **map;
	char **map_copy;
	t_mapdata *data;
	int width;
	int height;
} t_map;

typedef struct s_player
{
	int player_x;
	int player_y;
	char player_dir;
	int dir_count;
} t_player;

typedef struct s_game
{
	void *mlx;
	void *win;
	t_map *map;
	t_player *player;
} t_game;

void ft_exit(int err_no, char *err, t_game *game);
void map_path_control(char *path, t_game *game);
void get_map_size(char *path, t_game *game);
int ft_len_not_nl(char *str);
char **my_realloc_arr(char **ptr, size_t size);
void free_map(char **map, int y);

#endif