/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere_plane.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:42:59 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/12/03 15:43:02 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool	hit_sphere(const t_ray *c_ray, const t_sphere *sphere, t_hit_rec *hit_rec)
{
	t_vec oc = vec_sub(c_ray->origin, sphere->center);
	double a = vec_dot(c_ray->direction, c_ray->direction); //(D·D); c_ray->direction * c_ray->direction
	double half_b = vec_dot(oc, c_ray->direction);//oc * c_ray->direction;
	double c = vec_dot(oc, oc) - (sphere->radius * sphere->radius);//oc * oc - sphere->radius * sphere->radius;
	double disc = (half_b * half_b) - (a * c);
	if(disc < 0)
		return false;
	//var for getting root. result of moving elements to the right to find clean t from squere equesion
	hit_rec->t = (-half_b - sqrt(disc)) / a;//first cross cos it always smaller
	if(hit_rec->t < T_MIN || hit_rec->t > T_MAX)
	{
		hit_rec->t = (-half_b + sqrt(disc)) / a;//second cross cos it bigger
		if(hit_rec->t < T_MIN || hit_rec->t > T_MAX)
			return false;
	}
	hit_rec->intersection = vec_add(c_ray->origin, vec_scale(c_ray->direction, hit_rec->t));
	hit_rec->normal = vec_sub(hit_rec->intersection, sphere->center);
	hit_rec->normal = vec_normalize(hit_rec->normal);
	hit_rec->color = sphere->color;
	return true;
}

bool	hit_plane(const t_ray *c_ray, const t_plane *plane, t_hit_rec *hit_rec)
{
	double	parallel_angle;
	t_vec	ray_to_plane;
	t_vec	scaled_t_pos;

	parallel_angle = vec_dot(plane->normal, c_ray->direction);
	if (fabs(parallel_angle) < EPS)
		return (false);
	ray_to_plane = vec_sub(plane->point, c_ray->origin);
	hit_rec->t = vec_dot(plane->normal, ray_to_plane) / parallel_angle;
	if (hit_rec->t < T_MIN || hit_rec->t > T_MAX)
		return (false);
	scaled_t_pos = vec_scale(c_ray->direction, hit_rec->t);
	hit_rec->intersection = vec_add(c_ray->origin, scaled_t_pos);
	hit_rec->normal = plane->normal;
	hit_rec->color = plane->color;
	hit_rec->type = OBJ_PLANE;
	return (true);
}
