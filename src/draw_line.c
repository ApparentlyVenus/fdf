/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:03:33 by odana             #+#    #+#             */
/*   Updated: 2025/06/16 09:08:40 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"
#include "../lib/inc/libft.h"
#include "../lib/inc/get_next_line.h"

static void	init_bresenham(t_bresenham *b, t_point2d start, t_point2d end)
{
	b->dx = abs(end.x - start.x);
	b->dy = abs(end.y - start.y);
	if (start.x < end.x)
		b->sx = 1;
	else
		b->sx = -1;
	if (start.y < end.y)
		b->sy = 1;
	else
		b->sy = -1;
	b->err = b->dx - b->dy;
	b->x = start.x;
	b->y = start.y;
}

static void	bresenham_step(t_bresenham *b)
{
	int	e2;

	e2 = 2 * b->err;
	if (e2 > -b->dy)
	{
		b->err -= b->dy;
		b->x += b->sx;
	}
	if (e2 < b->dx)
	{
		b->err += b->dx;
		b->y += b->sy;
	}
}

void	draw_line(t_fdf *fdf, t_point2d start, t_point2d end, int color)
{
	t_bresenham	b;

	init_bresenham(&b, start, end);
	while (1)
	{
		mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, b.x, b.y, color);
		if (b.x == end.x && b.y == end.y)
			break ;
		bresenham_step(&b);
	}
}

void	draw_horizontal_lines(t_fdf *fdf, t_point2d(*f)(t_fdf *, t_point3d))
{
	int			x;
	int			y;
	t_point3d	p1;
	t_point3d	p2;

	x = 0;
	while (x < fdf->width - 1)
	{
		y = 0;
		while (y < fdf->height)
		{
			p1 = (t_point3d){x, y, get_z_value(fdf, x, y)};
			p2 = (t_point3d){x + 1, y, get_z_value(fdf, x + 1, y)};
			draw_line(fdf, f(fdf, p1), f(fdf, p2), get_line_color(fdf, p1.z, p2.z));
			y += fdf->step;
		}
		x += fdf->step;
	}
}

void	draw_vertical_lines(t_fdf *fdf, t_point2d(*f)(t_fdf *, t_point3d))
{
	int			x;
	int			y;
	t_point3d	p1;
	t_point3d	p2;

	y = 0;
	while (y < fdf->height - 1)
	{
		x = 0;
		while (x < fdf->width)
		{
			p1 = (t_point3d){x, y, get_z_value(fdf, x, y)};
			p2 = (t_point3d){x, y + 1, get_z_value(fdf, x, y + 1)};
			draw_line(fdf, f(fdf, p1), f(fdf, p2), get_line_color(fdf, p1.z, p2.z));
			x += fdf->step;
		}
		y += fdf->step;
	}
}
