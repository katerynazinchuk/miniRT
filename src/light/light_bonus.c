/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:00:03 by tchernia          #+#    #+#             */
/*   Updated: 2025/12/16 19:20:56 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
 
//recieve a t -> bulitd vec_normalize(t);
//light_ray = vec_add(t, light_sourse);
//light_ray = vec_normalize(light_ray);
//brightness = cos(angle) = vec_dot(normal, light_ray);
// then we have to multiply the object color by the brightness factor vec_scale(t, brightness)
//diffuse = color * intencity

bool	is_in_shadow(t_scene *scene, t_hit_rec *hit, t_light_basis base);
static t_color	handle_final_color(t_scene *scene, t_hit_rec *hit, t_color final_color);
static t_color	spec_reflection(t_hit_rec *hit, t_light *light, t_light_basis base);

int	find_light_spot_bonus(t_scene *scene, t_hit_rec *hit_rec)
{
	t_color	final_color;

	final_color = scene->black;
	handle_multi_lights(scene, &scene->l_sp, hit_rec, &final_color);
	hit_rec->color = handle_final_color(scene, hit_rec, final_color);
	return (0);
}

int	handle_multi_lights(t_scene *scene, t_l_spots *light, t_hit_rec *hit, t_color *color)
{
	t_light_basis	base;
	size_t			i;
	t_color			tmp_color;
	t_color			spec_color;

	i = 0;
	while (i < light->l_count)
	{
		base.l_ray = vec_sub(light->l_arr[i].position, hit->intersection);
		base.l_len = vec_length(base.l_ray);
		base.l_ray = vec_normalize(base.l_ray);
		if(is_in_shadow(scene, hit, base))
			tmp_color = scene->black;
		else
		{
			base.dif = fmax(0.0, vec_dot(hit->normal, base.l_ray));
			base.dif = base.dif * light->l_arr[i].intensity;
			spec_color = spec_reflection(hit, &light->l_arr[i], base);
			tmp_color = color_scale(hit->color, base.dif);
			tmp_color = color_mult(tmp_color, light->l_arr[i].color);
			tmp_color = color_add(tmp_color, spec_color);
		}
		*color = color_add(*color, tmp_color);
		i++;
	}
	return (0);
}



bool	is_in_shadow(t_scene *scene, t_hit_rec *hit, t_light_basis base)
{
	t_hit_rec	temp_rec;
	t_ray 		shadow_ray;

	shadow_ray.origin = vec_add(hit->intersection, vec_scale(hit->normal, EPS));
	shadow_ray.direction = base.l_ray;
	temp_rec.t = INFINITY;

	if (hit_scene(&shadow_ray, scene, &temp_rec))
	{
		if (temp_rec.t < base.l_len && temp_rec.t > T_MIN)
			return (true);
	}
	return (false);
}

static t_color	handle_final_color(t_scene *scene, t_hit_rec *hit, t_color final_color)
{
	t_color	amb_color;
	double	amb;

	amb = scene->ambient.ratio;
	amb_color = color_scale(hit->color, amb);
	final_color = color_add(final_color, amb_color);
	final_color = color_clamp(final_color, 0, 255);
	return (final_color);
}

static t_color	spec_reflection(t_hit_rec *hit, t_light *light, t_light_basis base)
{
	t_color	spec_color;
	t_vec	refl_ray;
	t_vec	to_camera;
	double	dp;
	double	specular;

	dp = vec_dot(hit->normal, base.l_ray);
	refl_ray = vec_sub(vec_scale(hit->normal, 2.0 * dp), base.l_ray);
	refl_ray = vec_normalize(refl_ray);
	to_camera = vec_sub(hit->camera_pos, hit->intersection);
	to_camera = vec_normalize(to_camera);//why here we have Conditional jump or move depends on uninitialised value(s)
	specular = vec_dot(refl_ray, to_camera);
	if (specular < 0)
		specular = 0;
	else
		specular = pow(specular, SHINE);
	spec_color = color_scale(light->color, specular * light->intensity);
	return (spec_color);
}
