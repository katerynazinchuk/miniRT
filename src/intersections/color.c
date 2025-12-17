/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 13:59:51 by tchernia          #+#    #+#             */
/*   Updated: 2025/12/17 12:40:54 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

uint32_t	find_color(t_ray ray, t_scene *scene)
{
	t_hit_rec	hit_rec;
	uint32_t	color;

	color = scene->background;
	if (hit_scene(&ray, scene, &hit_rec))
	{
		hit_rec.camera_pos = scene->camera.position;
		find_light_spot_bonus(scene, &hit_rec);
		color = rgba(hit_rec.color.r, hit_rec.color.g, hit_rec.color.b);
	}
	return (color);
}

uint32_t	rgba(int r, int g, int b)
{
	return (((uint32_t)r << 24) | ((uint32_t)g << 16) | (uint32_t)b << 8 | 255);
}

t_color	to_rgba(int hex_num)
{
	t_color	color;

	color.r = (hex_num >> 24) & 0xFF;
	color.g = (hex_num >> 16) & 0xFF;
	color.b = (hex_num >> 8) & 0xFF;
	return (color);
}
