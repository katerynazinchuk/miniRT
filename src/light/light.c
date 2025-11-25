/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kat <kat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:55:34 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/11/18 18:28:04 by kat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
 
//recieve a t -> bulitd vec_normalize(t);
//light_ray = vec_add(t, light_sourse);
//light_ray = vec_normalize(light_ray);
//brightness = cos(angle) = vec_dot(normal, light_ray);
// then we have to multiply the object color by the brightness factor vec_scale(t, brightness)
//diffuse = color * intencity

int find_light_spot(t_scene *scene, t_hit_rec *hit_rec)
{
	t_vec light_ray;
	double brightness;
	t_color base;

	light_ray = vec_sub(scene->light.position, hit_rec->intersection);
	light_ray = vec_normalize(light_ray);
	brightness = fmax(0.0, vec_dot(hit_rec->normal, light_ray));
	brightness = brightness * scene->light.intensity;
	brightness = brightness + scene->ambient.ratio;
	brightness = fmin(1.0, brightness);
	base = get_hit_color(scene, hit_rec);
	hit_rec->color = color_scale(base, brightness);
	return (1);
}

t_color   get_hit_color(t_scene *scene, t_hit_rec *hit_rec)
{
    if (hit_rec->type == OBJ_SPHERE)
        return (&scene->objects.spheres[hit_rec->index].color);
    else if (hit_rec->type == OBJ_PLANE)
        return (&scene->objects.planes[hit_rec->index].color);
    else if (hit_rec->type == OBJ_CYL)
        return (&scene->objects.cyls[hit_rec->index].color);
    return (rgba(0, 0, 0));
}