/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:00:36 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/12/16 19:45:43 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_UTILS_H
# define VEC_UTILS_H

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

t_vec	vec_pos(double x, double y, double z);
t_vec	vec_add(t_vec a, t_vec b);
t_vec	vec_sub(t_vec a, t_vec b);
t_vec	vec_scale(t_vec v, double s);
t_color	color_scale(t_color color, double brightness);
double	vec_dot(t_vec a, t_vec b);
t_vec	vec_cross(t_vec a, t_vec b);
double	vec_length(t_vec v);
t_vec	vec_normalize(t_vec v);
t_vec	vec_neg(t_vec v);

#endif