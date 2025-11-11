/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:13:59 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/11/11 16:14:05 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define ARR_SIZE 5
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

bool		hit_plane(const t_ray *c_ray, const t_plane *plane, double *t);
bool		hit_sphere(const t_ray *c_ray, const t_sphere *sphere, double *t);
t_ray		create_ray_per_pixel(t_camera *camera, int x, int y);
uint32_t	find_color(t_ray ray, t_scene *scene);
uint32_t	rgba(int r, int g, int b);
void		print_error(const char *msg);

#endif