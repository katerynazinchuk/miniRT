/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:13:59 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/11/03 16:17:00 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define WIDTH 1000
# define HEIGHT 1000
# define M_PI 3.14159265358979323846
# define EPS 1e-6
# define T_MIN 1e-4
# define T_MAX 1e30

# include <MLX42/MLX42.h>
# include <fcntl.h>
# include <stdbool.h>
# include "vec_structs.h"
# include <math.h>
# include "libft.h"
# include "get_next_line.h"
# include "vec_utils.h"
# include "parser.h"

bool	hit_plane(t_ray *c_ray, t_plane *plane, double *t);

#endif