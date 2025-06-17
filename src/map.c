/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:35:52 by odana             #+#    #+#             */
/*   Updated: 2025/06/17 08:42:49 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"
#include "../lib/inc/libft.h"
#include "../lib/inc/get_next_line.h"

static int	*parse_line_values(char *line)
{
	char	**split_line;
	int		*values;
	int		i;
	int		count;

	split_line = ft_split(line, ' ');
	if (!split_line)
		return (NULL);
	count = 0;
	while (split_line[count])
		count++;
	values = (int *)malloc(sizeof(int) * count);
	if (!values)
	{
		free_split(split_line);
		return (NULL);
	}
	i = 0;
	while (i < count)
	{
		values[i] = ft_atoi(split_line[i]);
		i++;
	}
	free_split(split_line);
	return (values);
}

static t_point3d	*create_points(char **lines, int width, int height)
{
	t_point3d	*points;
	int			*line_values;
	int			x;
	int			y;

	points = (t_point3d *)malloc(sizeof(t_point3d) * width * height);
	if (!points)
		return (NULL);
	y = 0;
	while (y < height)
	{
		line_values = parse_line_values(lines[y++]);
		if (!line_values)
			return (free(points), NULL);
		x = 0;
		while (x < width)
		{
			points[(y - 1) * width + x].x = x;
			points[(y - 1) * width + x].y = (y - 1);
			points[(y - 1) * width + x].z = line_values[x];
			x++;
		}
		free(line_values);
	}
	return (points);
}

static t_map	*create_map(char **lines)
{
	t_map	*map;
	int		width;
	int		height;

	if (!lines)
		return (NULL);
	width = count_cols(lines[0]);
	height = get_map_height(lines);
	if (width <= 0 || height <= 0)
		return (NULL);
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->width = width;
	map->height = height;
	map->pts = create_points(lines, width, height);
	if (!map->pts)
	{
		free(map);
		return (NULL);
	}
	return (map);
}

t_map	*parse_fdf_file(char *filename)
{
	char	**lines;
	t_map	*map;

	lines = extract_lines(filename);
	if (!lines)
		return (NULL);
	if (validate_fdf_map(lines))
	{
		map = create_map(lines);
		free_lines(lines);
		return (map);
	}
	free_lines(lines);
	return (NULL);
}
