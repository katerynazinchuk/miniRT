/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 01:02:04 by tchernia          #+#    #+#             */
/*   Updated: 2025/12/15 01:03:56 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	parse_cylinder(t_cylinder *cylinder, char *line);

int	process_cylinder(t_objects *obj, char *line)
{
	t_cylinder	cy_temp;
	ssize_t		s;

	if (!parse_cylinder(&cy_temp, line))
		return (0);
	s = sizeof(t_cylinder);
	if (!check_capacity((void **)&obj->cys, &obj->cy_arr_cap, obj->cy_count, s))
		return (0);
	obj->cys[obj->cy_count] = cy_temp;
	obj->cy_count++;
	return (1);
}

static int	parse_cylinder(t_cylinder *cylinder, char *line)
{
	int	i;

	i = 2;
	if (!skip_spases(line, &i))
		return (0);
	if (!parse_vector(line, &i, &cylinder->center, 0))
		return (0);
	if (!skip_spases(line, &i))
		return (0);
	if (!parse_vector(line, &i, &cylinder->axis, 1))
		return (0);
	cylinder->axis = vec_normalize(cylinder->axis);
	if (!skip_spases(line, &i))
		return (0);
	cylinder->radius = (ft_atof(line, &i) / 2);
	if (cylinder->radius <= 0)
		return (0);
	if (!skip_spases(line, &i))
		return (0);
	cylinder->height = ft_atof(line, &i);
	if (!skip_spases(line, &i))
		return (0);
	if (!parse_color(line, &i, &cylinder->color))
		return (0);
	return (1);
}
