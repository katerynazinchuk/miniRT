/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular_reflection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 19:36:05 by tchernia          #+#    #+#             */
/*   Updated: 2025/12/17 13:06:32 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	spec_reflection(t_hit *hit, t_light *light, t_light_basis base)
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
	to_camera = vec_normalize(to_camera);
	specular = vec_dot(refl_ray, to_camera);
	if (specular < 0)
		specular = 0;
	else
		specular = pow(specular, SHINE);
	spec_color = color_scale(light->color, specular * light->intensity);
	return (spec_color);
}
