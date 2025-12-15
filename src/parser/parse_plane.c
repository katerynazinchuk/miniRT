/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 00:58:31 by tchernia          #+#    #+#             */
/*   Updated: 2025/12/15 00:59:39 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	parse_plane(t_plane *plane, char *line);

int	process_plane(t_objects *obj, char *line)
{
	t_plane	pl_temp;
	ssize_t	s;

	if (!parse_plane(&pl_temp, line))
		return (0);
	s = sizeof(t_plane);
	if (!check_capacity((void **)&obj->pls, &obj->pl_arr_cap, obj->pl_count, s))
		return (0);
	obj->pls[obj->pl_count] = pl_temp;
	obj->pl_count++;
	return (1);
}

static int	parse_plane(t_plane *plane, char *line)
{
	int	i;

	i = 2;
	if (!skip_spases(line, &i))
		return (0);
	if (!parse_vector(line, &i, &plane->point, 0))
		return (0);
	if (!skip_spases(line, &i))
		return (0);
	if (!parse_vector(line, &i, &plane->normal, 1))
		return (0);
	plane->normal = vec_normalize(plane->normal);
	if (!skip_spases(line, &i))
		return (0);
	if (!parse_color(line, &i, &plane->color))
		return (0);
	return (1);
}
