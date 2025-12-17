/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:00:44 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/11/28 14:21:49 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

//dot possition
t_vec	vec_pos(double x, double y, double z)
{
	t_vec	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

//usage brightness = max(0, dot(normal, light_dir));
//return the value of the cos between two vectors
//if they are penoerdicular return 0;
double	vec_dot(t_vec a, t_vec b)
{
	double	c;

	c = a.x * b.x + a.y * b.y + a.z * b.z;
	return (c);
}

//builds a vector perpendicular to two other given vectors
// which identify the plane in the space
//so basically we build perpendicular to the plane
t_vec	vec_cross(t_vec a, t_vec b)
{
	t_vec	cross;

	cross.x = a.y * b.z - a.z * b.y;
	cross.y = a.z * b.x - a.x * b.z;
	cross.z = a.x * b.y - a.y * b.x;
	return (cross);
}

//helper func for normalization and to compare distances
double	vec_length(t_vec v)
{
	double	len;

	len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return (len);
}

//ray directions and normals should be unit length for correct math
t_vec	vec_normalize(t_vec v)
{
	t_vec	normalized;
	double	len;

	len = vec_length(v);
	if (len < EPS)
		return (v);
	normalized.x = v.x / len;
	normalized.y = v.y / len;
	normalized.z = v.z / len;
	return (normalized);
}
