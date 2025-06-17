/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wireframe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:55:40 by odana             #+#    #+#             */
/*   Updated: 2025/06/17 07:29:02 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_z_value(t_fdf *fdf, int x, int y)
{
	return (fdf->map->pts[y * fdf->width + x].z);
}

void	init_fdf(t_fdf *fdf, t_map *map)
{
	fdf->map = map;
	fdf->width = map->width;
	fdf->height = map->height;
	fdf->color_scheme = 1;
	fdf->z_scale = 0.1f;
	init_step_and_zoom(fdf);
	init_z_range(fdf);
	fdf->z_rotation = 1.0f;
	fdf->offset_x = WINDOW_WIDTH / 2;
	fdf->offset_y = WINDOW_HEIGHT / 2;
	fdf->current_projection = 0;
	fdf->iso_angle = 0.4f;
}

void	init_step_and_zoom(t_fdf *fdf)
{
	if (fdf->width > 200 || fdf->height > 200)
		fdf->zoom = 2;
	else if (fdf->width > 100 || fdf->height > 100)
		fdf->zoom = 4;
	else if (fdf->width > 50 || fdf->height > 50)
		fdf->zoom = 8;
	else if (fdf->width > 20 || fdf->height > 20)
		fdf->zoom = 15;
	else
		fdf->zoom = 25;
	if (fdf->width > 200 || fdf->height > 200)
		fdf->step = 4;
	else
		fdf->step = 1;
}

void	init_z_range(t_fdf *fdf)
{
	int	i;
	int	total_points;

	total_points = fdf->width * fdf->height;
	fdf->z_min = INT_MAX;
	fdf->z_max = INT_MIN;
	i = 0;
	while (i < total_points)
	{
		if (fdf->map->pts[i].z < fdf->z_min)
			fdf->z_min = fdf->map->pts[i].z;
		if (fdf->map->pts[i].z > fdf->z_max)
			fdf->z_max = fdf->map->pts[i].z;
		i++;
	}
}

void	render_scene(t_fdf *fdf)
{
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	if (fdf->current_projection == 0)
	{
		draw_horizontal_lines(fdf, project_isometric);
		draw_vertical_lines(fdf, project_isometric);
	}
	else
	{
		draw_horizontal_lines(fdf, project_conic);
		draw_vertical_lines(fdf, project_conic);
	}
}
