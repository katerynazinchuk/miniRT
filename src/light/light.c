/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:55:34 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/11/25 18:44:46 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
 
//recieve a t -> bulitd vec_normalize(t);
//light_ray = vec_add(t, light_sourse);
//light_ray = vec_normalize(light_ray);
//brightness = cos(angle) = vec_dot(normal, light_ray);
// then we have to multiply the object color by the brightness factor vec_scale(t, brightness)
//diffuse = color * intencity

static t_color	get_hit_color(t_scene *scene, t_hit_rec *hit_rec);

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
//memset was added
static t_color   get_hit_color(t_scene *scene, t_hit_rec *hit_rec)
{
	t_color	black;

    if (hit_rec->type == OBJ_SPHERE)
        return (/* & */scene->objects.sps[hit_rec->index].color);
    else if (hit_rec->type == OBJ_PLANE)
        return (/* & */scene->objects.pls[hit_rec->index].color);
    else if (hit_rec->type == OBJ_CYL)
        return (/* & */scene->objects.cys[hit_rec->index].color);
	else
		ft_memset(&black, 0, sizeof(t_color));
    return (black);
}
