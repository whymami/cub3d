/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:59:09 by muguveli          #+#    #+#             */
/*   Updated: 2024/09/04 16:22:37 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_len_not_nl(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	return (i);
}

int	ft_str_digit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

int	arr_len(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

void	free_arr(char **arr)
{
	int	i;

	i = -1;
	if (arr)
	{
		if (*arr)
			while (arr[++i])
				free(arr[i]);
		free(arr);
	}
}

void	comma_count(char *line, t_game *game)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (line[++i])
		if (line[i] == ',')
			++count;
	if (count > 2)
		ft_exit(2, "comma count error", game);
}
