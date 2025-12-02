/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:13:59 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/12/02 14:43:30 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define ARR_SIZE 5
# define WIDTH 2000
# define HEIGHT 2000
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

//--------------intersections
bool		hit_plane(const t_ray *c_ray, const t_plane *plane, t_hit_rec *hit_rec);
bool		hit_sphere(const t_ray *c_ray, const t_sphere *sphere, t_hit_rec *hit_rec);
bool		hit_cylinder(const t_ray *c_ray, t_cylinder *cylinder, t_hit_rec *hit_rec);
bool		hit_cyl_body(const t_ray *c_ray, t_cylinder *cylinder, t_hit_rec *hit_rec);
bool		hit_cyl_cap(const t_ray *c_ray, t_vec cap_center, t_vec cap_normal, t_hit_rec *hit_rec, double radius);
bool		find_best_t_for_body(double t_root[2], const t_ray *c_ray, t_cylinder *cylinder, t_hit_rec *hit_rec);
bool		hit_scene(const t_ray *c_ray, t_scene *scene, t_hit_rec *hit_rec);

//--------------light
int			find_light_spot(t_scene *scene, t_hit_rec *hit_rec);
t_ray		create_ray_per_pixel(t_camera *camera, int x, int y);
uint32_t	find_color(t_ray ray, t_scene *scene);
uint32_t	rgba(int r, int g, int b);

//--------------utils
void		print_error(const char *msg);
bool		init_structs(t_rt *rt);
void		handle_esc(mlx_key_data_t key_info, void *param);



/* Tests */
void	test_parser(t_scene *scene, t_objects *obj);


#endif