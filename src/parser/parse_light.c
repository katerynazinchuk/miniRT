/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 01:04:48 by tchernia          #+#    #+#             */
/*   Updated: 2025/12/15 01:04:49 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	parse_light(t_light *light, char *line);

int	process_light(t_l_spots *l_sp, char *line)
{
	t_light	l_temp;
	size_t	s;

	if (!parse_light(&l_temp, line))
		return (0);
	s = sizeof(t_light);
	if (!check_capacity((void **)&l_sp->l_arr, &l_sp->l_cap, l_sp->l_count, s))
		return (0);
	l_sp->l_arr[l_sp->l_count] = l_temp;
	l_sp->l_count++;
	return (1);
}

static int	parse_light(t_light *light, char *line)
{
	int	i;

	i = 1;
	if (!skip_spases(line, &i))
		return (0);
	if (!parse_vector(line, &i, &light->position, 0))
		return (0);
	if (!skip_spases(line, &i))
		return (0);
	light->intensity = ft_atof(line, &i);
	if (!skip_spases(line, &i))
		return (0);
	if (!parse_color(line, &i, &light->color))
		return (0);
	return (1);
}
