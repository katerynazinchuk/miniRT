/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:00:44 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/10/16 17:27:49 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vec_utils.h"
#include <math.h>


//dot possition
t_vec vec_pos(float x, float y, float z)
{
	t_vec  v;
	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
	//return (t_vec) {x, y, z};
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

//usage brightness = max(0, dot(normal, light_dir));
//return the value of the cos between two vectors
//if they are penoerdicular return 0;
float vec_dot(t_vec a, t_vec b)
{ 
	float c; 
	c = a.x * b.x + a.y * b.y + a.z * b.z; 
	return (c); 
}

//builds a vector perpendicular to two other given vectors which identify the plane in the space
//so basically we build perpendicular to the plane
t_vec vec_cross(t_vec a, t_vec b)
{
	t_vec cross;

	cross.x = a.y * b.z - a.z * b.y;
	cross.y = a.z * b.x - a.x * b.z;
	cross.z = a.x * b.y - a.y * b.x;

	return(cross);

}

//helper func for normalization and to compare distances
float vec_length(t_vec v)
{
	float len;

	len = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	//sqrtf return float. sqrt return double
	return (len);
}

//ray directions and normals should be unit length for correct math
t_vec vec_normalize(t_vec v)
{
	t_vec normalized;
	float len;

	len = vec_length(v);
	if(len == 0)
		retutn (v);
	normalized.x = v.x / len;
	normalized.y = v.y / len;
	normalized.z = v.z / len;
	return (normalized);
}

//made the vector oposite direction oriented if normal looks to the wrong direction
//if ray is inside the oject
//
t_vec  vec_neg(t_vec v)
{
	t_vec negative;

	negative.x = -v.x;
	negative.y = -v.y;
	negative.z = -v.z;
	return (negative);
}