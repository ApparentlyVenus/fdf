/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:49:20 by odana             #+#    #+#             */
/*   Updated: 2025/06/17 08:20:50 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static int	handle_movement(int keycode, t_fdf *fdf)
{
	if (keycode == W_KEY || keycode == UP_KEY)
		fdf->offset_y -= 20;
	else if (keycode == S_KEY || keycode == DOWN_KEY)
		fdf->offset_y += 20;
	else if (keycode == A_KEY || keycode == LEFT_KEY)
		fdf->offset_x -= 20;
	else if (keycode == D_KEY || keycode == RIGHT_KEY)
		fdf->offset_x += 20;
	else
		return (0);
	return (1);
}

static int	handle_zoom_and_controls(int keycode, t_fdf *fdf)
{
	if (keycode == PLUS_KEY)
		fdf->zoom += 2;
	else if (keycode == MINUS_KEY && fdf->zoom > 2)
		fdf->zoom -= 2;
	else if (keycode == P_KEY)
		fdf->current_projection = (fdf->current_projection + 1) % 2;
	else if (keycode == R_KEY && fdf->step > 1)
		fdf->step--;
	else if (keycode == T_KEY)
		fdf->step++;
	else
		return (0);
	return (1);
}

static int	handle_angles(int keycode, t_fdf *fdf)
{
	if (keycode == Q_KEY)
	{
		fdf->iso_angle += 0.1f;
		if (fdf->iso_angle > 1.0f)
			fdf->iso_angle = 1.0f;
	}
	else if (keycode == E_KEY)
	{
		fdf->iso_angle -= 0.1f;
		if (fdf->iso_angle < 0.1f)
			fdf->iso_angle = 0.1f;
	}
	else
		return (0);
	return (1);
}

static int	handle_rotations(int keycode, t_fdf *fdf)
{
	if (keycode == I_KEY)
	{
		fdf->z_rotation += 0.1f;
		if (fdf->z_rotation > 2 * PI)
			fdf->z_rotation -= 2 * PI;
	}
	else if (keycode == K_KEY)
	{
		fdf->z_rotation -= 0.1f;
		if (fdf->z_rotation < 0)
			fdf->z_rotation += 2 * PI;
	}
	else
		return (0);
	return (1);
}

int	key_hook(int keycode, t_fdf *fdf)
{
	int	refresh;

	if (keycode == ESC_KEY)
	{
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
		mlx_destroy_display(fdf->mlx_ptr);
		free(fdf->mlx_ptr);
		free_map(fdf->map);
		exit(0);
	}
	refresh = handle_movement(keycode, fdf);
	refresh += handle_zoom_and_controls(keycode, fdf);
	refresh += handle_angles(keycode, fdf);
	refresh += handle_rotations(keycode, fdf);
	if (refresh)
		render_scene(fdf);
	return (0);
}
