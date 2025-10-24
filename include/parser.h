/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 14:35:10 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/10/23 14:59:14 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "rt.h"

//parsing.c
int parse_ambient(t_rt *rt, char *line);
int parse_camera(t_rt *rt, char *line);
int parse_light(t_rt *rt, char *line);
int parse_sphere(t_rt *rt, char *line);
int parse_plane(t_rt *rt, char *line, int line_counter);
int parse_cylinder(t_rt *rt, char *line);

//read_lines.c
char **parse_file(const char *filename, t_rt *rt);
void validate_error(int line_counter);
int validate_symb(t_rt *rt, char *line, int line_counter);
int skip_spases(char *line, int *i);


//validate.c
int check_file(char *filename);
int check_rt_extension(char *filename);


#endif