/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:00:44 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/10/13 18:39:19 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vec_utils.h"


//dot possition
t_vec vec_pos(float x, float y, float z)
{
	// t_vec  v;
	// v.x = x;
	// v.y = y;
	// v.z = z;
	// return (v);
	return (t_vec) {x, y, z};
}

//move a poit by a vector
//usage: pos + offset, normal + something, color1 + color2
t_vec vec_add(t_vec a, t_vec b)
{
	t_vec add_p;
	
	add_p.x = a.x + b.x;
	add_p.y = a.y + b.y;
	add_p.z = a.z + b.z;
	return (add_p);
}

//substitution. build directions vectors (to light or to sphere center)
//usage to_light = light.pos - hit.pint ==> vec_sub(light.pos, hit_point)
t_vec vec_sub(t_vec a, t_vec b)//(light_possition, hit_point)
{
	t_vec sub_p;
	
	sub_p.x = a.x - b.x;
	sub_p.y = a.y - b.y;
	sub_p.z = a.z - b.z;
	return (sub_p);

}

//scale a direction by distance t, scale colors by intensities or material coefficients
//usage P(t) = O + D * t, where D * t is vec_scale; diffuse = color * intencity
t_vec vec_scale(t_vec v, float s)
{
	t_vec scale_p;

	scale_p.x = v.x * s;
	scale_p.y = v.y * s;
	scale_p.z = v.z * s;
	return (scale_p);
}

//normale???
float vec_dot(t_vec a, t_vec b)
{

}

//builds a vector perpendicular to two others// why and wich two others???
t_vec vec_cross(t_vec a, t_vec b)
{

}

//helper func for normalization and to compare distances
float vec_length(t_vec v)
{

}

//ray directions and normals should be unit length for correct math
t_vec vec_normalize(t_vec v)
{

}

//neglect. helper
t_vec  vec_neg(t_vec v)
{

}