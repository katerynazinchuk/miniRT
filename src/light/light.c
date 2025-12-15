/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:55:34 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/12/15 17:04:51 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
 
//recieve a t -> bulitd vec_normalize(t);
//light_ray = vec_add(t, light_sourse);
//light_ray = vec_normalize(light_ray);
//brightness = cos(angle) = vec_dot(normal, light_ray);
// then we have to multiply the object color by the brightness factor vec_scale(t, brightness)
//diffuse = color * intencity

static t_color	get_hit_color(t_scene *scene, t_hit *hit_rec);
static bool is_in_shadow(t_scene *scene, t_hit *hit_rec);

int find_light_spot(t_scene *scene, t_hit *hit_rec)
{
	t_vec	light_ray;
	double	brightness;
	t_color	base;

	light_ray = vec_sub(scene->light.position, hit_rec->intersection);
	light_ray = vec_normalize(light_ray);
	base = get_hit_color(scene, hit_rec);
	if(is_in_shadow(scene, hit_rec))
	{
		hit_rec->color = color_scale(base, scene->ambient.ratio);
		return (1);
	}
	else
	{
		brightness = fmax(0.0, vec_dot(hit_rec->normal, light_ray));
		brightness = brightness * scene->light.intensity;
		brightness = brightness + scene->ambient.ratio;
		brightness = fmin(1.0, brightness);
		hit_rec->color = color_scale(base, brightness);
		return (1);
	}
	return (0);
}

// int find_light_spot(t_scene *scene, t_hit_rec *hit_rec)
// {
// 	t_vec light_ray;
// 	double brightness;
// 	t_color base;
	
// 	light_ray = vec_sub(scene->light.position, hit_rec->intersection);
// 	light_ray = vec_normalize(light_ray);
// 	brightness = fmax(0.0, vec_dot(hit_rec->normal, light_ray));
// 	brightness = brightness * scene->light.intensity;
// 	brightness = brightness + scene->ambient.ratio;
// 	brightness = fmin(1.0, brightness);
// 	base = get_hit_color(scene, hit_rec);
// 	hit_rec->color = color_scale(base, brightness);

// 	return (1);
// }

bool is_in_shadow(t_scene *scene, t_hit *hit_rec)
{
	t_vec		light_dir;
	t_hit	temp_rec;
	double		light_distance;
	t_ray 		shadow_ray;

	light_dir = vec_sub(scene->light.position, hit_rec->intersection);
	light_distance = vec_length(light_dir);
	light_dir = vec_normalize(light_dir);
	shadow_ray.origin = vec_add(hit_rec->intersection, vec_scale(hit_rec->normal, EPS));
	shadow_ray.direction = light_dir;
	temp_rec.t = INFINITY;

	if (hit_scene(&shadow_ray, scene, &temp_rec))
	{
		if (temp_rec.t < light_distance && temp_rec.t > T_MIN)
			return (true);
	}
	return (false);
}
//memset was added
static t_color	get_hit_color(t_scene *scene, t_hit *hit_rec)
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
