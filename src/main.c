/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:34:30 by odana             #+#    #+#             */
/*   Updated: 2025/06/17 08:23:27 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static int	init_mlx(t_fdf *fdf)
{
	fdf->mlx_ptr = mlx_init();
	if (!fdf->mlx_ptr)
		return (0);
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT,
			"FDF - Wireframe Viewer");
	if (!fdf->win_ptr)
		return (0);
	return (1);
}

static int	mouse_hook(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (button == 1)
		fdf->zoom += 0.7;
	else if (button == 3 && fdf->zoom > 0.7)
		fdf->zoom -= 0.7;
	else if (button == 4)
		fdf->z_scale += 0.1;
	else if (button == 5 && fdf->z_scale > 0.2)
		fdf->z_scale -= 0.1;
	else
		return (0);
	render_scene(fdf);
	return (0);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;
	t_map	*map;

	if (argc != 2)
		return (1);
	map = parse_fdf_file(argv[1]);
	if (!map)
		return (1);
	if (!init_mlx(&fdf))
	{
		free_map(map);
		return (1);
	}
	init_fdf(&fdf, map);
	mlx_key_hook(fdf.win_ptr, key_hook, &fdf);
	mlx_mouse_hook(fdf.win_ptr, mouse_hook, &fdf);
	render_scene(&fdf);
	mlx_loop(fdf.mlx_ptr);
	return (0);
}
