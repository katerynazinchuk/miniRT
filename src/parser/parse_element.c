/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:36:24 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/12/14 23:24:36 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	calculate_camera(t_camera *camera);

int	parse_ambient(t_rt *rt, char *line)
{
	int	i;

	i = 1;
	if (!skip_spases(line, &i))
		return (0);
	rt->scene.ambient.ratio = ft_atof(line, &i);
	if (!skip_spases(line, &i))
		return (0);
	if (!parse_color(line, &i, &rt->scene.ambient.color))
		return (0);
	rt->scene.ambient.flag = true;
	return (1);
}

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
	if (!parse_vector(line, &i, &rt->scene.camera.direction, 0))
		return (0);
	rt->scene.camera.direction = vec_normalize(rt->scene.camera.direction);
	if (!skip_spases(line, &i))
		return (0);
	rt->scene.camera.angle = ft_atof(line, &i);
	calculate_camera(&rt->scene.camera);
	rt->scene.camera.flag = true;
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

int	parse_vector(char *line, int *i, t_vec *vec, int normal_range)
{
	vec->x = ft_atof(line, i);
	if (line[*i] != ',')
	{
		print_error("Input outside of the range");
		return (0);
	}
	(*i)++;
	vec->y = ft_atof(line, i);
	if (line[*i] != ',')
	{
		print_error("Input outside of the range");
		return (0);
	}
	(*i)++;
	vec->z = ft_atof(line, i);
	if (normal_range)
	{
		if (!check_vector(vec->x) || !check_vector(vec->y) \
|| !check_vector(vec->z))
		{
			print_error("Input outside of the range");
			return (0);
		}
	}
	return (1);
}

int	parse_color(char *line, int *i, t_color *color)
{
	color->r = (int)ft_atof(line, i);
	if (line[*i] != ',')
	{
		print_error("Color input outside of the range");
		return (0);
	}
	(*i)++;
	color->g = (int)ft_atof(line, i);
	if (line[*i] != ',')
	{
		print_error("Color input outside of the range");
		return (0);
	}
	(*i)++;
	color->b = (int)ft_atof(line, i);
	if (!check_color(color->r) || !check_color(color->g) \
|| !check_color(color->b))
	{
		print_error("Color input outside of the range");
		return (0);
	}
	return (1);
}
