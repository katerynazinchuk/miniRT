/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:13:59 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/10/16 19:06:18 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_utils.h"

typedef struct s_elemnts
{
	camera;
	*objects;
	*lights;
}	t_elements;

typedef struct s_objects
{
	type plane;
	type cylinder;
	type sphere;
}	t_objects;

typedef struct s_ray
{
	t_vec	origin;
	t_vec	direction;

	//we loop through all objects looking for the smaleest positive t, 
	//that will be the first ray intersection.
	//P(t) = origin + direction * t;

}	t_ray;
//next i need to create a struct that will store the current hit reccord. with actual value of t

typedef struct s_color
{
	float	r;
	float	g;
	float	b;

}	t_color;

typedef struct s_sphere
{
	t_vec		center;
	float		radius;
	t_material	mat;
}	t_sphere;

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
	t_vec;
	//direction; comes from .rt
	//perpendicular;
	//negative;
	//cross from perpendicular and direction


}	t_camera;

typedef struct s_scene
{
	//everithing inside

}	t_scene;

typedef struct s_material
{
	t_color	albedo;
	//more comming..
	
}	t_material;