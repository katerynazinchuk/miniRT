/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:11:03 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/12/15 17:55:51 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static bool	cyl_body_quad(const t_ray *c_ray, t_cyl *cyl, t_cyl_quad *q)
{
	t_vec	oc_perp;
	t_vec	d_perp;
	t_vec	oc;
	double	oc_dot_axis;
	double	d_dot_axis;

	oc = vec_sub(c_ray->origin, cyl->center);
	oc_dot_axis = vec_dot(oc, cyl->axis);
	d_dot_axis = vec_dot(c_ray->dir, cyl->axis);
	oc_perp = vec_sub(oc, vec_scale(cyl->axis, oc_dot_axis));
	d_perp = vec_sub(c_ray->dir, vec_scale(cyl->axis, d_dot_axis));
	q->a = vec_dot(d_perp, d_perp);
	if (q->a < EPS)
		return (false);
	q->half_b = vec_dot(oc_perp, d_perp);
	q->c_perp = vec_dot(oc_perp, oc_perp) - (cyl->radius * cyl->radius);
	q->disc = (q->half_b * q->half_b) - (q->a * q->c_perp);
	if (q->disc < 0.0)
		return (false);
	q->sqrt_disc = sqrt(q->disc);
	q->t_root[0] = (-q->half_b - q->sqrt_disc) / q->a;
	q->t_root[1] = (-q->half_b + q->sqrt_disc) / q->a;
	return (true);
}

bool	hit_cyl_body(const t_ray *c_ray, t_cyl *cyl, t_hit *hit_rec)
{
	t_cyl_quad	q;

	if (!cyl_body_quad(c_ray, cyl, &q))
		return (false);
	if (best_t_for_body(q.t_root, c_ray, cyl, hit_rec))
		return (true);
	return (false);
}

bool	best_t_for_body(double t_root[2], const t_ray *c_ray, t_cyl *cyl, t_hit *hit)
{
	double	half_height;
	double	best_t;
	int		i;
	t_vec	center_to_hit;
	t_vec	axis_proj;
	t_vec	radial_vec;
	t_vec	hit_point;
	double	height_on_axis;

	half_height = cyl->height * 0.5;
	best_t = T_MAX;
	i = 0;
	while (i < 2)
	{
		if (t_root[i] >= T_MIN && t_root[i] <= best_t)
		{
			hit_point = vec_add(c_ray->origin, vec_scale(c_ray->dir, t_root[i]));
			center_to_hit = vec_sub(hit_point, cyl->center);
			height_on_axis = vec_dot(center_to_hit, cyl->axis);
			if (height_on_axis >= -half_height && height_on_axis <= half_height)
			{
				axis_proj = vec_scale(cyl->axis, height_on_axis);
				radial_vec = vec_sub(center_to_hit, axis_proj);
				best_t = t_root[i];
				hit->t = t_root[i];
				hit->intersection = hit_point;
				hit->normal = vec_normalize(radial_vec);
				if (vec_dot(hit->normal, c_ray->dir) > 0.0)
					hit->normal = vec_neg(hit->normal);
				hit->color = cyl->color;
			}
		}
		i++;
	}
	if (best_t == T_MAX)
		return (false);
	return (true);
}

void	collect_hits_for_cyl(const t_ray *c_ray, t_cyl *cyl, t_cyl_hits *h)
{
	t_vec	top_center;
	t_vec	bot_center;
	t_vec	bot_normal;
	double	half_h;

	half_h = cyl->height * 0.5;
	h->h_body = hit_cyl_body(c_ray, cyl, &h->body);
	top_center = vec_add(cyl->center, vec_scale(cyl->axis, half_h));
	h->h_top = hit_cyl_cap(c_ray, top_center, cyl->axis, &h->top, cyl);
	bot_center = vec_sub(cyl->center, vec_scale(cyl->axis, half_h));
	bot_normal = vec_neg(cyl->axis);
	h->h_bot = hit_cyl_cap(c_ray, bot_center, bot_normal, &h->bot, cyl);
}

bool	hit_cyl_cap(const t_ray *c_ray, t_vec cap_center, t_vec normal, t_hit *hit_rec, t_cyl *cyl)
{
	t_vec		center_to_hit;
	double		dist_sq;
	t_plane		cap_plane;
	t_hit		cap_hit;

	cap_plane.point = cap_center;
	cap_plane.normal = normal;
	if (!hit_plane(c_ray, &cap_plane, &cap_hit))
		return (false);
	center_to_hit = vec_sub(cap_hit.intersection, cap_center);
	dist_sq = vec_dot(center_to_hit, center_to_hit);
	if (dist_sq <= cyl->radius * cyl->radius)
	{
		*hit_rec = cap_hit;
		hit_rec->color = cap_hit.color;
		hit_rec->type = OBJ_PLANE;
		return (true);
	}
	return (false);
}

bool	hit_cylinder(const t_ray *c_ray, t_cyl *cylinder, t_hit *hit_rec)
{
	t_hit		*closest_hit;
	t_cyl_hits	h;

	collect_hits_for_cyl(c_ray, cylinder, &h);
	closest_hit = NULL;
	if (h.h_body)
		closest_hit = &h.body;
	if (h.h_top && (!closest_hit || h.top.t < closest_hit->t))
		closest_hit = &h.top;
	if (h.h_bot && (!closest_hit || h.bot.t < closest_hit->t))
		closest_hit = &h.bot;
	if (closest_hit == NULL)
		return (false);
	*hit_rec = *closest_hit;
	hit_rec->color = cylinder->color;
	hit_rec->type = OBJ_CYL;
	return (true);
}
