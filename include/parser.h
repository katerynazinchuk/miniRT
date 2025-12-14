/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 14:35:10 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/12/11 13:00:10 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "rt.h"

//parsing.c
int		parse_ambient(t_rt *rt, char *line/* , int line_counter */);
int		parse_camera(t_rt *rt, char *line/* , int line_counter */);
// int		parse_light(t_rt *rt, char *line/* , int line_counter */);
// int parse_sphere(t_rt *rt, char *line/* , int line_counter */);
int		parse_sphere(t_sphere *sphere, char *line/* , int line_counter */);

int		parse_plane(t_plane *plane, char *line/* , int line_counter */);
int		parse_cylinder(t_cylinder *cylinder, char *line/* , int line_counter */);
int		parse_color(char * line, int *i, t_color *color);
int		parse_vector(char *line, int *i, t_vec *vec, int normal_range);
int		check_vector(double vec);
int		check_color(int color);

int		process_sphere(t_objects *obj, char *line/* , int line_counter */);
int		process_plane(t_objects *obj, char *line/* , int line_counter */);
int		process_cylinder(t_objects *obj, char *line/* , int line_counter */);


int		check_capacity(void **array, size_t *capacity, size_t count, size_t type_size);//need to return rewrite array if nesseccary
void	*growing_realloc(void *old_ptr, size_t old_size, size_t new_size);
int		free_arrays(t_objects *obj, t_light *arr);

int		validate_singe_element(t_rt *rt, char *line);
int		validate_geometric_objects(t_objects *obj, char *line);

int		process_light(t_l_spots *l_sp, char *line);


//read_lines.c
int		parse_file(const char *filename, t_rt *rt);
// void	validate_error(int line_counter);
int		validate_identifier(t_rt *rt, char *line/* , int line_counter */);
int		skip_spases(char *line, int *i);


//validate.c
int		check_file(char *filename);
int		check_rt_extension(char *filename);


#endif