/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_structs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:58:45 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/12/18 10:14:15 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_STRUCTS_H
# define VEC_STRUCTS_H
# include "vec_utils.h"

// A ray: P(t) = origin + direction * t  (direction must be normalized)
//if there is no origin only direction, then origin is 0,0,0
typedef struct s_ray
{
	t_vec	origin;
	t_vec	dir;
}	t_ray;

typedef struct s_ambient
{
	t_color	color;
	double	ratio;
	bool	flag;
}	t_ambient;

typedef struct s_camera
{
	t_vec	position;
	t_vec	direction;
	t_vec	right;
	t_vec	up;
	double	angle;
	double	scale;
	double	aspect;
	bool	flag;
}	t_camera;

typedef struct s_light
{
	t_vec	position;
	t_color	color;
	double	intensity;
}	t_light;

typedef enum e_objtype
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYL,
}	t_objtype;

typedef struct s_sphere
{
	t_vec		center;
	double		radius;
	t_color		color;
	t_objtype	type;
}	t_sphere;

typedef struct s_cyl
{
	t_vec		center;
	t_vec		axis;
	double		radius;
	double		height;
	t_color		color;
	t_objtype	type;
}	t_cyl;

typedef struct s_plane
{
	t_vec		point;
	t_vec		normal;
	t_objtype	type;
	t_color		color;
}	t_plane;

typedef struct s_objects
{
	t_sphere	*sps;
	t_cyl		*cys;
	t_plane		*pls;
	size_t		sp_count;
	size_t		cy_count;
	size_t		pl_count;
	size_t		sp_arr_cap;
	size_t		cy_arr_cap;
	size_t		pl_arr_cap;
}	t_objects;

typedef struct s_data_img
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	color;
	mlx_image_t	*img;
}	t_data_img;

typedef struct s_l_spots
{
	t_light		*l_arr;
	size_t		l_count;
	size_t		l_cap;
}	t_l_spots;

typedef struct s_scene
{
	t_camera			camera;
	t_l_spots			l_sp;
	t_objects			objects;
	t_ambient			ambient;
	t_data_img			data_i;
	struct s_hit_rec	*hit_rec;
	t_color				black;
	int					render;
	uint32_t			background;

}	t_scene;

typedef struct s_rt
{
	int		line_counter;
	t_scene	scene;
}	t_rt;

typedef struct s_hit
{
	double		t;
	t_vec		intersection;
	t_vec		normal;
	t_vec		camera_pos;
	t_objtype	type;
	int			index;
	t_color		color;
}	t_hit;

typedef struct s_light_basis
{
	t_vec	l_ray;
	double	dif;
	t_color	l_color;
	double	l_len;
}	t_light_basis;

typedef struct s_cyl_hits
{
	t_hit	body;
	t_hit	top;
	t_hit	bot;
	bool	h_top;
	bool	h_bot;
	bool	h_body;
}	t_cyl_hits;

typedef struct s_cyl_quad
{
	double	a;
	double	half_b;
	double	c_perp;
	double	disc;
	double	sqrt_disc;
	double	t_root[2];
}	t_cyl_quad;

typedef struct s_body_ctx
{
	const t_ray	*c_ray;
	t_cyl		*cyl;
	t_hit		*hit;
	double		half_height;
	double		best_t;
}	t_body_ctx;

typedef struct s_h_cyl_vecs
{
	t_vec		top_center;
	t_vec		bot_center;
	t_vec		bot_normal;
	const t_ray	*camera_ray;
	bool		is_top_center;
}	t_h_cyl_vecs;

#endif