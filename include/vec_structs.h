/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_structs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:58:45 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/12/08 16:33:40 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_STRUCTS_H
# define VEC_STRUCTS_H
# include "vec_utils.h"

// A ray: P(t) = origin + direction * t  (direction must be normalized)
//if there is no origin only direction, then origin is 0,0,0
typedef struct	s_ray
{
	t_vec	origin;
	t_vec	direction;

	//we loop through all objects looking for the smaleest positive t, 
	//that will be the first ray intersection.

}	t_ray;
//next i need to create a struct that will store the current hit reccord. with actual value of t

typedef struct	s_ambient
{
	t_color color;
	double ratio;
	bool	flag;
}	t_ambient;

typedef struct	s_camera
{
	t_vec	position;
	t_vec	direction;//normalized direction; comes from .rt
	t_vec	right;// cross from direction and...???
	t_vec	up;//cross from direction and right
	double	angle;//in radiant so angle = 70 * M_PI / 180.0 and result will be in radiant
	double	scale;// scale = tan((camera->angle * 0,5));
	double	aspect;// aspect = (double)WIDTH / (double)HEIGHT;
	bool	flag;
}	t_camera;

typedef struct	s_light
{
	t_vec	position;
	t_color	color;
	double	intensity;//will be calculated through vec_dot;
	//..ambient or not, possition of light??
} t_light;

typedef enum	e_objtype
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYL,
}	t_objtype;

typedef struct	s_sphere
{
	t_vec				center;
	double				radius;//in .rt we have diametr
	t_color				color;
	t_objtype			type;
}	t_sphere;

typedef struct	s_cylinder
{
	t_vec center;
	t_vec axis;
	double radius;
	double height;// float?? or double??
	t_color				color;
	t_objtype			type;
}	t_cylinder;

typedef struct	s_plane
{
	t_vec point;
	t_vec normal;
	t_objtype			type;
	t_color				color;
}	t_plane;

typedef struct	s_objects
{
	t_sphere	*sps;
	t_cylinder	*cys;
	t_plane		*pls;
	size_t		sp_count;
	size_t		cy_count;
	size_t		pl_count;
	size_t		sp_arr_cap;
	size_t		cy_arr_cap;
	size_t		pl_arr_cap;
}	t_objects;

typedef struct	s_data_img
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	color;
	mlx_image_t	*img;
}	t_data_img;

typedef struct	s_l_spots
{
	t_light				*l_arr;//before multi_spot
	size_t				l_count;
	size_t				l_cap;
}	t_l_spots;


typedef struct	s_scene
{
	t_camera			camera;
	t_l_spots			l_sp;
	t_objects			objects;
	t_ambient			ambient;
	t_data_img			data_i;
	struct s_hit_rec	*hit_rec;
	int					render;
	// t_light				*ls;
	// size_t				l_count;
	// size_t				l_cap;
}	t_scene;

typedef struct	s_rt
{
	int		line_counter;
	t_scene	scene;
}	t_rt;

typedef struct s_hit_rec
{
	double		t;
	t_vec		intersection;
	t_vec		normal;
	t_objtype	type;
	int			index;
	t_color		color;
	
}	t_hit_rec;

typedef struct s_light_basis
{
	t_vec	l_ray;//direction from intersection point to light
	double	bright;// 0-1 diffuse
	t_color	l_color;//before it was base
	
	t_vec		light_dir;
	t_hit_rec	temp_rec;
	double		light_distance;
	t_ray 		shadow_ray;
}	t_light_basis;

#endif