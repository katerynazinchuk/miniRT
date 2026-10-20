/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 15:55:00 by kzinchuk          #+#    #+#             */
/*   Updated: 2026/10/20 15:55:00 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	handle_angle(t_rt *rt, char *line, int *i);
static void	calculate_camera(t_camera *camera);

//in radiant so angle = 70 * M_PI / 180.0 
//  result will be in radiant
//scale = tan((camera->angle * 0,5));
//aspect = (double)WIDTH / (double)HEIGHT;
int	parse_camera(t_rt *rt, char *line)
{
	int		i;

	i = 1;
	if (!skip_spases(line, &i))
		return (0);
	if (!parse_vector(line, &i, &rt->scene.camera.position, 0))
		return (0);
	if (!skip_spases(line, &i))
		return (0);
	if (!parse_vector(line, &i, &rt->scene.camera.direction, 1))
		return (0);
	rt->scene.camera.direction = vec_normalize(rt->scene.camera.direction);
	if (!skip_spases(line, &i))
		return (0);
	if (!handle_angle(rt, line, &i))
		return (0);
	calculate_camera(&rt->scene.camera);
	rt->scene.camera.flag = true;
	return (1);
}

static int	handle_angle(t_rt *rt, char *line, int *i)
{
	if (!parse_double(line, i, &rt->scene.camera.angle))
		return (0);
	if (rt->scene.camera.angle <= 0 || rt->scene.camera.angle >= 180)
	{
		print_error("FOV must be between 0 and 180");
		return (0);
	}
	if (!check_line_end(line, *i))
		return (0);
	return (1);
}

static void	calculate_camera(t_camera *camera)
{
	t_vec	world_up;

	camera->aspect = (double)WIDTH / (double)HEIGHT;
	world_up = vec_pos(0, 1, 0);
	camera->right = vec_cross(world_up, camera->direction);
	camera->right = vec_normalize(camera->right);
	camera->up = vec_cross(camera->direction, camera->right);
	camera->up = vec_normalize(camera->up);
	camera->angle = camera->angle * M_PI / 180.0;
	camera->scale = tan(camera->angle * 0.5);
}
