/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:13:59 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/11/04 17:16:57 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define WIDTH 1000
# define HEIGHT 1000
# define M_PI 3.14159265358979323846

# include <MLX42/MLX42.h>
# include <fcntl.h>
# include <stdbool.h>
# include "vec_structs.h"
# include <math.h>
# include "libft.h"
# include "get_next_line.h"
# include "vec_utils.h"
# include "parser.h"

bool		hit_plane(t_ray *c_ray, t_plane *plane, double *t);
t_ray		create_ray_per_pixel(t_camera *camera, int x, int y);
uint32_t	find_color(t_ray ray, t_scene *scene);
uint32_t	rgba(int r, int g, int b);
void		print_error(const char *msg);

#endif