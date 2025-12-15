/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:40:37 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/12/03 15:40:39 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

uint32_t	rgba(int r, int g, int b)
{
	return (((uint32_t)r << 24) | ((uint32_t)g << 16) | (uint32_t)b << 8 | 255);
}

uint32_t	find_color(t_ray ray, t_scene *scene)
{
	t_hit_rec	hit_rec;
	uint32_t	color;

	color = rgba(110, 110, 110);
	if (hit_scene(&ray, scene, &hit_rec))
	{
		if (find_light_spot(scene, &hit_rec))
			color = rgba(hit_rec.color.r, hit_rec.color.g, hit_rec.color.b);
	}
	return (color);
}
