/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere_plane.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:32:39 by tchernia          #+#    #+#             */
/*   Updated: 2025/12/17 13:36:57 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool	hit_sphere(const t_ray *c_ray, const t_sphere *sphere, t_hit *hit)
{
	t_vec	oc;
	double	a;
	double	half_b;
	double	c;
	double	disc;

	oc = vec_sub(c_ray->origin, sphere->center);
	a = vec_dot(c_ray->dir, c_ray->dir);
	half_b = vec_dot(oc, c_ray->dir);
	c = vec_dot(oc, oc) - (sphere->radius * sphere->radius);
	disc = (half_b * half_b) - (a * c);
	if (disc < 0)
		return (false);
	hit->t = (-half_b - sqrt(disc)) / a;
	if (hit->t < T_MIN || hit->t > T_MAX)
	{
		hit->t = (-half_b + sqrt(disc)) / a;
		if (hit->t < T_MIN || hit->t > T_MAX)
			return (false);
	}
	hit->intersection = vec_add(c_ray->origin, vec_scale(c_ray->dir, hit->t));
	hit->normal = vec_sub(hit->intersection, sphere->center);
	hit->normal = vec_normalize(hit->normal);
	hit->color = sphere->color;
	return (true);
}

bool	hit_plane(const t_ray *c_ray, const t_plane *plane, t_hit *hit_rec)
{
	double	parallel_angle;
	t_vec	ray_to_plane;
	t_vec	scaled_t_pos;

	parallel_angle = vec_dot(plane->normal, c_ray->dir);
	if (fabs(parallel_angle) < EPS)
		return (false);
	ray_to_plane = vec_sub(plane->point, c_ray->origin);
	hit_rec->t = vec_dot(plane->normal, ray_to_plane) / parallel_angle;
	if (hit_rec->t < T_MIN || hit_rec->t > T_MAX)
		return (false);
	scaled_t_pos = vec_scale(c_ray->dir, hit_rec->t);
	hit_rec->intersection = vec_add(c_ray->origin, scaled_t_pos);
	hit_rec->normal = plane->normal;
	hit_rec->color = plane->color;
	hit_rec->type = OBJ_PLANE;
	return (true);
}
