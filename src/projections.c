/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:27:16 by odana             #+#    #+#             */
/*   Updated: 2025/06/17 10:12:29 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

t_point2d	project_isometric(t_fdf *fdf, t_point3d point3d)
{
	t_point2d	point2d;
	float		cos_rot;
	float		sin_rot;
	float		x_rot;
	float		y_rot;

	cos_rot = cos(fdf->z_rotation);
	sin_rot = sin(fdf->z_rotation);
	x_rot = point3d.x * cos_rot - point3d.y * sin_rot;
	y_rot = point3d.x * sin_rot + point3d.y * cos_rot;
	point2d.x = (x_rot - y_rot) * cos(fdf->iso_angle)
		* fdf->zoom + fdf->offset_x;
	point2d.y = (x_rot + y_rot) * sin(fdf->iso_angle)
		* fdf->zoom - point3d.z * fdf->z_scale * fdf->zoom + fdf->offset_y;
	return (point2d);
}

t_point2d	project_conic(t_fdf *fdf, t_point3d point3d)
{
	t_point2d	point2d;
	float		d;
	float		eye_z;
	float		z_transformed;
	float		scale_factor;

	d = 800.0f;
	eye_z = 500.0f;
	z_transformed = point3d.z * fdf->z_scale + eye_z;
	if (z_transformed <= 0)
		z_transformed = 1.0f;
	scale_factor = d / z_transformed;
	point2d.x = point3d.x * scale_factor * fdf->zoom + fdf->offset_x;
	point2d.y = point3d.y * scale_factor * fdf->zoom + fdf->offset_y;
	return (point2d);
}
