/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:13:59 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/12/18 14:47:41 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define ARR_SIZE 5
# define WIDTH 500
# define HEIGHT 500
# define M_PI 3.14159265358979323846
# define EPS 1e-6
# define T_MIN 1e-4
# define T_MAX 1e30
# define SHINE 20

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
bool		hit_plane(const t_ray *c_ray, const t_plane *plane, t_hit *hit_rec);
bool		hit_sphere(const t_ray *c_ray, const t_sphere *sphere,\
	t_hit *hit_rec);
bool		hit_cylinder(const t_ray *c_ray, t_cyl *cylinder, t_hit *hit_rec);
bool		hit_cyl_body(const t_ray *c_ray, t_cyl *cylinder, t_hit *hit_rec);
bool		hit_cyl_cap(t_h_cyl_vecs cyl_vecs, t_vec normal,\
	t_hit *hit_rec, t_cyl *cyl);
bool		best_t_for_body(double t_root[2], const t_ray *c_ray,\
	t_cyl *cylinder, t_hit *hit_rec);
bool		hit_scene(const t_ray *c_ray, t_scene *scene, t_hit *hit_rec);
//--------------light
int			find_light_spot(t_scene *scene, t_hit *hit_rec);
t_ray		create_ray_per_pix(t_camera *camera, int x, int y);
uint32_t	find_color(t_ray ray, t_scene *scene);
int			check_lights(t_scene *sc, t_l_spots *light, t_hit *hit,\
	t_color *color);
void		set_light_base(t_light_basis *base, t_hit *hit, t_vec l_pos);
bool		is_in_shadow(t_scene *scene, t_hit *hit, t_light_basis base);
t_color		spec_reflection(t_hit *hit, t_light *light, t_light_basis base);
t_color		handle_final_color(t_scene *scene, t_hit *hit, t_color final_color);
//--------------color operations
uint32_t	rgba(int r, int g, int b);
t_color		to_rgba(int hex_num);
t_color		color_add(t_color one, t_color two);
t_color		color_clamp(t_color color, int min, int max);
t_color		color_mult(t_color one, t_color two);
//--------------utils
void		print_error(const char *msg);
bool		init_structs(t_rt *rt);
void		handle_esc(mlx_key_data_t key_info, void *param);
/* Tests */
void		test_parser(t_scene *scene, t_objects *obj);

#endif