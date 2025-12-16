/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_of_view.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 12:29:48 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/12/16 12:43:40 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_ray	create_ray_per_pix(t_camera *camera, int x, int y)
{
	t_ray	ray;
	t_vec	temp;
	double	norm_x;
	double	norm_y;

	ray.origin = camera->position;
	norm_x = 2.0 * (x + 0.5) / (double)WIDTH - 1.0;
	norm_y = 1.0 - 2.0 * (y + 0.5) / (double)HEIGHT;
	norm_x = norm_x * camera->scale * camera->aspect;
	norm_y = norm_y * camera->scale;
	temp = vec_add(vec_scale(camera->right, norm_x), \
vec_scale(camera->up, norm_y));
	ray.dir = vec_normalize(vec_add(camera->direction, temp));
	return (ray);
}
