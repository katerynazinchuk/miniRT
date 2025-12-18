/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 00:13:58 by tchernia          #+#    #+#             */
/*   Updated: 2025/12/15 00:40:13 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	set_i_line(char *line, int *i_line);
static int	validate_line(char *line, int i_line);
static int	validate_singe_element(t_rt *rt, char *line);
static int	validate_geometric_objects(t_objects *obj, char *line);

int	validate_identifier(t_rt *rt, char *line)
{
	int	i_line;
	int	code;

	set_i_line(line, &i_line);
	if (!validate_line(line, i_line))
		return (0);
	if (i_line == 1)
		code = validate_singe_element(rt, line);
	else
		code = validate_geometric_objects(&rt->scene.objects, line);
	return (code);
}

static int	set_i_line(char *line, int *i_line)
{
	int	i;

	i = 0;
	*i_line = 0;
	if (line[i] == 'A' || line[i] == 'C' || line[i] == 'L')
		*i_line = 1;
	if (check_obj_symbols(line, i))
		*i_line = 2;
	return (1);
}

static int	validate_line(char *line, int i_line)
{
	while (line[i_line] != '\0' && line[i_line] != '\n')
	{
		if (!(ft_isdigit(line[i_line]) || \
line[i_line] == ' ' || \
line[i_line] == ' ' || \
line[i_line] == ',' || \
line[i_line] == '.' || \
line[i_line] == '-' || \
line[i_line] == '+'))
		{
			print_error("Error: Invalid character in input");
			return (0);
		}
		i_line++;
	}
	return (1);
}

static int	validate_singe_element(t_rt *rt, char *line)
{
	int	i;

	i = 0;
	if (line[i] == 'A' && !rt->scene.ambient.flag)
		return (parse_ambient(rt, line));
	else if (line[i] == 'C' && !rt->scene.camera.flag)
		return (parse_camera(rt, line));
	else if (line[i] == 'L')
		return (process_light(&rt->scene.l_sp, line));
	print_error("Too many capital identifiers");
	return (0);
}

static int	validate_geometric_objects(t_objects *obj, char *line)
{
	int	i;

	i = 0;
	if (line[i] == 's' && line[i + 1] == 'p')
		return (process_sphere(obj, line));
	else if (line[i] == 'p' && line[i + 1] == 'l')
		return (process_plane(obj, line));
	else if (line[i] == 'c' && line[i + 1] == 'y')
		return (process_cylinder(obj, line));
	return (1);
}
