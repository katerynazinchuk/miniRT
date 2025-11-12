/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:55:34 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/11/12 18:38:34 by kzinchuk         ###   ########.fr       */
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

	light_ray = vec_sub(scene->light.position, hit_rec->intersection);
	light_ray = vec_normalize(light_ray);
	brightness = fmax(0.0, vec_dot(hit_rec->normal, light_ray));
	hit_rec->color = color_scale(hit_rec->object->material.albedo, brightness);
	return (1);
}

