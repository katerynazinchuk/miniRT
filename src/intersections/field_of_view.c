/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_of_view.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 14:00:14 by tchernia          #+#    #+#             */
/*   Updated: 2025/12/14 16:23:09 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		x_normalise(double x, double *norm_x, t_camera *camera);
static void		y_normalise(double y, double *norm_y, t_camera *camera);
static t_vec	calculate_direction(t_camera *camera, double x, double y);

/*
 * NDC space (which stands for Normalized Device Coordinates)
 * norm_x & norm_y - convert (x, y) in (-1, 1) coordinates with
 *  center (0, 0) in the center of window
 * aspect ratio - in case if will use window with width > height
 * scale – apply field of view (camera angle)
*/
t_ray	create_ray_per_pix(t_camera *camera, int x, int y)
{
	t_ray	ray;
	double	norm_x;
	double	norm_y;

	x_normalise(x, &norm_x, camera);
	y_normalise(y, &norm_y, camera);
	ray.direction = calculate_direction(camera, norm_x, norm_y);
	ray.origin = camera->position;
	return (ray);
}

static void	x_normalise(double x, double *norm_x, t_camera *camera)
{
	*norm_x = 2.0 * (x + 0.5) / (double)WIDTH - 1.0;
	*norm_x = *norm_x * camera->scale * camera->aspect;
}

static void	y_normalise(double y, double *norm_y, t_camera *camera)
{
	*norm_y = 1.0 - 2.0 * (y + 0.5) / (double)HEIGHT;
	*norm_y = *norm_y * camera->scale;
}

static t_vec	calculate_direction(t_camera *camera, double x, double y)
{
	t_vec	x_offset;
	t_vec	y_offset;
	t_vec	ray_direction;

	x_offset = vec_scale(camera->right, x);
	y_offset = vec_scale(camera->up, y);
	ray_direction = vec_add(camera->direction, vec_add(x_offset, y_offset));
	ray_direction = vec_normalize(ray_direction);
	return (ray_direction);
}
