/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 09:09:06 by odana             #+#    #+#             */
/*   Updated: 2025/06/17 07:27:25 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	get_color_component(int color, char component)
{
	if (component == 'r')
		return ((color / 65536) % 256);
	else if (component == 'g')
		return ((color / 256) % 256);
	else if (component == 'b')
		return (color % 256);
	return (0);
}

int	create_color(int r, int g, int b)
{
	return (r * 65536 + g * 256 + b);
}

int	interpolate_color(int color1, int color2, float ratio)
{
	int	rgb1[3];
	int	rgb2[3];

	rgb1[0] = get_color_component(color1, 'r');
	rgb1[1] = get_color_component(color1, 'g');
	rgb1[2] = get_color_component(color1, 'b');
	rgb2[0] = get_color_component(color2, 'r');
	rgb2[1] = get_color_component(color2, 'g');
	rgb2[2] = get_color_component(color2, 'b');
	return (create_color(
			rgb1[0] + (int)((rgb2[0] - rgb1[0]) * ratio),
		rgb1[1] + (int)((rgb2[1] - rgb1[1]) * ratio),
			rgb1[2] + (int)((rgb2[2] - rgb1[2]) * ratio)
	));
}

int	get_height_color(t_fdf *fdf, int z)
{
	float	ratio;
	int		color_low;
	int		color_high;

	if (fdf->color_scheme == 0)
		return (0xFFFFFF);
	if (fdf->color_scheme == 1)
		color_low = 0x0000FF;
	else
		color_low = 0x00FF00;
	if (fdf->color_scheme == 1)
		color_high = 0xFF0000;
	else
		color_high = 0xFF00FF;
	if (fdf->z_min == fdf->z_max)
		return (color_low);
	ratio = (float)(z - fdf->z_min) / (float)(fdf->z_max - fdf->z_min);
	if (ratio < 0)
		ratio = 0;
	if (ratio > 1)
		ratio = 1;
	return (interpolate_color(color_low, color_high, ratio));
}

int	get_line_color(t_fdf *fdf, int z1, int z2)
{
	int	avg_z;

	if (fdf->color_scheme == 0)
		return (0xFFFFFF);
	avg_z = (z1 + z2) / 2;
	return (get_height_color(fdf, avg_z));
}
