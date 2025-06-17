/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:54:15 by odana             #+#    #+#             */
/*   Updated: 2025/06/17 10:30:26 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <mlx.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>

# define ESC_KEY 65307
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define UP_KEY 65362
# define DOWN_KEY 65364
# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define PLUS_KEY 61
# define MINUS_KEY 45
# define P_KEY 112
# define I_KEY 105
# define K_KEY 107
# define Q_KEY 113
# define E_KEY 101
# define R_KEY 116
# define T_KEY 114

# define WINDOW_WIDTH 2000
# define WINDOW_HEIGHT 1200
# define PI 3.14159265358979323846f

typedef struct s_point2d
{
	int	x;
	int	y;
}	t_point2d;

typedef struct s_point3d
{
	int	x;
	int	y;
	int	z;
}	t_point3d;

typedef struct s_map
{
	int			width;
	int			height;
	t_point3d	*pts;
}	t_map;

typedef struct s_bresenham
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	x;
	int	y;
}	t_bresenham;

typedef struct s_fdf
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_map		*map;
	int			width;
	int			height;
	float		zoom;
	int			color_scheme;
	int			z_min;
	int			z_max;
	float		z_scale;
	float		z_rotation;
	int			offset_x;
	int			offset_y;
	int			current_projection;
	float		iso_angle;
	int			step;
}	t_fdf;

// parsing logic + utils
char		**extract_lines(char *file);
void		free_lines(char **lines);
void		free_exit(int fd, char **lines, char *msg);
int			count_rows(char *file);
int			count_cols(char *line);

// map + utils
t_map		*parse_fdf_file(char *filename);
int			get_map_height(char **lines);
void		free_split(char **split);
void		free_map(t_map *map);
int			extract_z_value(char *token);

// validation
int			validate_fdf_map(char **lines);
void		free_split(char **split);

// draw line (bresenhamd algorithm)
void		draw_line(t_fdf *fdf, t_point2d start, t_point2d end, int color);
void		draw_vertical_lines(t_fdf *fdf, t_point2d(*f)(t_fdf *, t_point3d));
void		draw_horizontal_lines(t_fdf *fd, t_point2d(*f)(t_fdf *, t_point3d));

// draw wireframe
void		init_fdf(t_fdf *fdf, t_map *map);
void		init_step_and_zoom(t_fdf *fdf);
void		init_z_range(t_fdf *fdf);
int			get_z_value(t_fdf *fdf, int x, int y);
void		render_scene(t_fdf *fdf);

// projections
t_point2d	project_isometric(t_fdf *fdf, t_point3d point3d);
t_point2d	project_conic(t_fdf *fdf, t_point3d point3d);

// event handling
int			key_hook(int keycode, t_fdf *fdf);

// color management
int			get_color_component(int color, char component);
int			create_color(int r, int g, int b);
int			interpolate_color(int color1, int color2, float ratio);
int			get_height_color(t_fdf *fdf, int z);
int			get_line_color(t_fdf *fdf, int z1, int z2);

#endif