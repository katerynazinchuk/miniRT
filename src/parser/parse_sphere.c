/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 00:45:48 by tchernia          #+#    #+#             */
/*   Updated: 2025/12/19 15:42:13 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	parse_sphere(t_sphere *sphere, char *line);

int	process_sphere(t_objects *obj, char *line)
{
	t_sphere	sp_temp;
	ssize_t		s;

	if (!parse_sphere(&sp_temp, line))
		return (0);
	s = sizeof(t_sphere);
	if (!check_capacity((void **)&obj->sps, &obj->sp_arr_cap, obj->sp_count, s))
		return (0);
	obj->sps[obj->sp_count] = sp_temp;
	obj->sp_count++;
	return (1);
}

static int	parse_sphere(t_sphere *sphere, char *line)
{
	int		i;

	i = 2;
	if (!skip_spases(line, &i))
		return (0);
	if (!parse_vector(line, &i, &sphere->center, 0))
		return (0);
	if (!skip_spases(line, &i))
		return (0);
	sphere->radius = (ft_atof(line, &i) / 2);
	if (sphere->radius <= 0)
	{
		print_error("Diametr must be bigger than 0");
		return (0);
	}
	if (!skip_spases(line, &i))
		return (0);
	if (!parse_color(line, &i, &sphere->color))
		return (0);
	return (1);
}
