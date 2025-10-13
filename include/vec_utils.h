/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:00:36 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/10/13 18:22:23 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_UTILS_H
# define vVEC_UTILS_H

typedef struct s_vec {
    float x;
    float y;
    float z;
} t_vec;

t_vec	vec_pos(float x, float y, float z);
t_vec	vec_add(t_vec a, t_vec b);
t_vec	vec_sub(t_vec a, t_vec b);
t_vec	vec_scale(t_vec v, float s);
float	vec_dot(t_vec a, t_vec b);
t_vec	vec_cross(t_vec a, t_vec b);
float	vec_length(t_vec v);
t_vec	vec_normalize(t_vec v);
t_vec	vec_neg(t_vec v);

#endif