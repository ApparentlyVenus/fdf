/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:40:42 by odana             #+#    #+#             */
/*   Updated: 2025/06/17 08:25:24 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"
#include "../lib/inc/libft.h"
#include "../lib/inc/get_next_line.h"

void	free_map(t_map *map)
{
	if (!map)
		return ;
	if (map->pts)
		free(map->pts);
	free(map);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	get_map_height(char **lines)
{
	int	height;

	if (!lines)
		return (0);
	height = 0;
	while (lines[height])
		height++;
	return (height);
}
