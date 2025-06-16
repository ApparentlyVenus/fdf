/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 09:09:06 by odana             #+#    #+#             */
/*   Updated: 2025/06/16 10:34:32 by odana            ###   ########.fr       */
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
	int	r1;
	int	g1;
	int	b1;
	int	r2;
	int	g2;
	int	b2;

	r1 = get_color_component(color1, 'r');
	g1 = get_color_component(color1, 'g');
	b1 = get_color_component(color1, 'b');
	r2 = get_color_component(color2, 'r');
	g2 = get_color_component(color2, 'g');
	b2 = get_color_component(color2, 'b');
	return (create_color(
		r1 + (int)((r2 - r1) * ratio),
		g1 + (int)((g2 - g1) * ratio),
		b1 + (int)((b2 - b1) * ratio)
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

