/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:13:59 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/10/29 12:06:37 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define WIDTH 1000
# define HEIGHT 1000

#include <MLX42/MLX42.h>
#include <fcntl.h>
#include <stdbool.h>
#include "vec_structs.h"
# include <math.h>
#include "libft.h"
#include "get_next_line.h"
#include "vec_utils.h"
#include "parser.h"

bool	hit_plane(t_ray *c_ray, t_plane *plane, double *t);

#endif