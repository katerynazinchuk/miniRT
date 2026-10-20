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

int	parse_ambient(t_rt *rt, char *line)
{
	int	i;

	i = 1;
	if (!skip_spases(line, &i))
		return (0);
	if (!parse_double(line, &i, &rt->scene.ambient.ratio))
		return (0);
	if (rt->scene.ambient.ratio < 0 || rt->scene.ambient.ratio > 1)
	{
		print_error("Ambient ratio must be between 0 and 1");
		return (0);
	}
	if (!skip_spases(line, &i))
		return (0);
	if (!parse_color(line, &i, &rt->scene.ambient.color))
		return (0);
	rt->scene.ambient.flag = true;
	return (1);
}

int	parse_vector(char *line, int *i, t_vec *vec, int normal_range)
{
	if (!parse_double(line, i, &vec->x))
		return (0);
	if (!check_comma(line, i))
		return (0);
	if (!parse_double(line, i, &vec->y))
		return (0);
	if (!check_comma(line, i))
		return (0);
	if (!parse_double(line, i, &vec->z))
		return (0);
	if (normal_range)
	{
		if (!check_vector(vec->x) || !check_vector(vec->y) \
|| !check_vector(vec->z) || vec_length(*vec) < EPS)
		{
			print_error("Input outside of the range");
			return (0);
		}
	}
	return (1);
}

int	parse_color(char *line, int *i, t_color *color)
{
	if (!parse_color_value(line, i, &color->r))
		return (0);
	if (!check_comma(line, i))
		return (0);
	if (!parse_color_value(line, i, &color->g))
		return (0);
	if (!check_comma(line, i))
		return (0);
	if (!parse_color_value(line, i, &color->b))
		return (0);
	if (!check_line_end(line, *i))
		return (0);
	return (1);
}
