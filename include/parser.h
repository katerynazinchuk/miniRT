/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 14:35:10 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/12/16 19:48:50 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "rt.h"

int		parse_ambient(t_rt *rt, char *line);
int		parse_camera(t_rt *rt, char *line);
int		parse_color(char *line, int *i, t_color *color);
int		parse_vector(char *line, int *i, t_vec *vec, int normal_range);
int		check_vector(double vec);
int		check_color(int color);
int		process_sphere(t_objects *obj, char *line);
int		process_plane(t_objects *obj, char *line);
int		process_cylinder(t_objects *obj, char *line);
int		check_capacity(void **array, size_t *capacity, size_t count,\
	size_t type_size);
void	*growing_realloc(void *old_ptr, size_t old_size, size_t new_size);
int		free_arrays(t_objects *obj, t_light *arr);
int		process_light(t_l_spots *l_sp, char *line);
int		parse_file(const char *filename, t_rt *rt);
int		validate_identifier(t_rt *rt, char *line);
int		skip_spases(char *line, int *i);
int		check_file(char *filename);
int		check_rt_extension(char *filename);
bool	check_obj_symbols(char *line, int i);

#endif