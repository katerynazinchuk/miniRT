/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:13:30 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/11/17 14:39:23 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool hit_all_spheres(t_ray *c_ray, t_scene *scene, t_hit_rec *hit_rec)
{
	
	return true;
}

bool hit_all_planes(t_ray *c_ray, t_scene *scene, t_hit_rec *hit_rec)
{
	
	return true;
}

bool hit_all_cylinders(t_ray *c_ray, t_scene *scene, t_hit_rec *hit_rec)
{
	bool hit_any = false;
	double closest_t = T_MAX;
	t_hit_rec hit;
	int i;
	
	i = 0;
	
	while(i < scene->objects.cyl_count)
	{
		if(hit_cylinder(c_ray, &scene->objects.cyl[i], &hit))
		{
			if(hit.t < closest_t && hit.t > T_MIN)
			{
				hit_any = true;
				closest_t = hit.t;
				*hit_rec = hit;
				hit_rec->type = OBJ_CYL;
				hit_rec->index = i;
			}
		}
		i++;
	}
	return (hit_any);
}

bool hit_scene(const t_ray *c_ray, t_scene *scene, t_hit_rec *hit_rec)
{
	bool hit_any = false;
	double closest_t = T_MAX;
	t_hit_rec hit;

	if(hit_all_planes(c_ray, scene, &hit) && hit.t < closest_t)
	{
		hit_any = true;
		closest_t = hit.t;
		*hit_rec = hit;
	}
	if(hit_all_spheres(c_ray, scene, &hit) && hit.t < closest_t)
	{
		hit_any = true;
		closest_t = hit.t;
		*hit_rec = hit;
	}
	if(hit_all_cylinders(c_ray, scene, &hit) && hit.t < closest_t)
	{
		hit_any = true;
		closest_t = hit.t;
		*hit_rec = hit;
	}
	return (hit_any);
}
