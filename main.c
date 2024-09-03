/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:27:07 by muguveli          #+#    #+#             */
/*   Updated: 2024/09/03 13:28:01 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	if (argc == 2 && argv[1][0])
		map_path_control(argv[1]);
	else
		ft_exit(1, "Invalid number of arguments", NULL);
}
