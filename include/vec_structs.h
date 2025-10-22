/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_structs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:58:45 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/10/22 13:44:26 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_STRUCTS_H
# define VEC_STRUCTS_H
# include "vec_utils.h"

typedef struct s_rt
{
	int line;
	t_scene scene;

}	t_rt;

typedef struct s_scene
{
	int			width;
	int			height;
	t_camera	camera;
	t_light		light;
	t_objects	objects;
}	t_scene;

typedef enum e_objtype
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYL,
}	t_objtype;

typedef union u_shape
{
	t_sphere	sp;
	t_plane		pl;
	t_cylinder	cy;
}	t_shape;

typedef struct s_objects
{
	t_objtype type;
	t_material material;
	t_shape shape;
}	t_objects;

typedef struct s_sphere
{
	t_vec		center;
	float		radius;//in .rt we have diametr
	t_material	mat;
}	t_sphere;

typedef struct s_cylinder
{
	t_vec center;
	t_vec axis;
	float radius;
	float height;// float?? or double??
	t_material	mat;
}	t_cylinder;


typedef struct s_plane
{
	t_vec point;
	t_vec normal;
	t_material	mat;
}	t_plane;

// A ray: P(t) = origin + direction * t  (direction must be normalized)
//if there is no origin only direction, then origin is 0,0,0
typedef struct s_ray
{
	t_vec	origin;
	t_vec	direction;

	//we loop through all objects looking for the smaleest positive t, 
	//that will be the first ray intersection.

}	t_ray;
//next i need to create a struct that will store the current hit reccord. with actual value of t

typedef struct s_color
{
	float	r;
	float	g;
	float	b;

}	t_color;

typedef struct s_light
{
	t_vec	position;
	t_color	color;
	float	intensity;//will be calculated through vec_dot;
	//..ambient or not, possition of light??

} t_light;

typedef struct s_camera
{
	t_vec	possition;
	t_vec direction;//normalized direction; comes from .rt
	t_vec right;// cross from direction and...???
	t_vec up;//cross from direction and right
	
}	t_camera;

typedef struct s_material
{
	t_color	albedo;
	//more comming..
	
}	t_material;


#endif