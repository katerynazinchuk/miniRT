/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 14:00:04 by tchernia          #+#    #+#             */
/*   Updated: 2025/12/14 14:00:05 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	clamp(double num, double min, double max);

t_color	color_scale(t_color color, double brightness)
{
	t_color	scale_c;

	scale_c.r = color.r * brightness;
	scale_c.g = color.g * brightness;
	scale_c.b = color.b * brightness;
	return (scale_c);
}

t_color	color_add(t_color one, t_color two)
{
	t_color	res;

	res.r = one.r + two.r;
	res.g = one.g + two.g;
	res.b = one.b + two.b;
	return (res);
}

t_color	color_clamp(t_color color, int min, int max)
{
	t_color	res_color;

	res_color.r = clamp(color.r, min, max);
	res_color.g = clamp(color.g, min, max);
	res_color.b = clamp(color.b, min, max);
	return (res_color);
}

static double	clamp(double num, double min, double max)
{
	if (num < min)
		return (min);
	if (num > max)
		return (max);
	return (num);
}

t_color	color_mult(t_color one, t_color two)
{
	t_color	res;

	res.r = (int)(((double)one.r * two.r) / 255);
	res.g = (int)(((double)one.g * two.g) / 255);
	res.b = (int)(((double)one.b * two.b) / 255);
	return (res);
}
