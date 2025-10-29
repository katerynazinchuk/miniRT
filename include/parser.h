/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 14:35:10 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/10/29 16:07:45 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "rt.h"

//parsing.c
int parse_ambient(t_rt *rt, char *line, int line_counter);
int parse_camera(t_rt *rt, char *line, int line_counter);
int parse_light(t_rt *rt, char *line, int line_counter);
int parse_sphere(t_rt *rt, char *line, int line_counter);
int parse_plane(t_rt *rt, char *line, int line_counter);
int parse_cylinder(t_rt *rt, char *line, int line_counter);
int parse_color(char * line, int *i, t_color *color);
int parse_vector(char *line, int *i, t_vec *vec);
int check_vector(double vec);
int check_color(int color);



//read_lines.c
int	parse_file(const char *filename, t_rt *rt);
void validate_error(int line_counter);
int validate_symb(t_rt *rt, char *line, int line_counter);
int skip_spases(char *line, int *i);


//validate.c
int check_file(char *filename);
int check_rt_extension(char *filename);


#endif