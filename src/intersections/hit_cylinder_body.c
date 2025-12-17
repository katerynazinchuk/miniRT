/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder_body.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:11:03 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/12/17 13:58:30 by tchernia         ###   ########.fr       */
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

static void	try_body_root( t_body_ctx *ctx, double t)
{
	t_vec	center_to_hit;
	t_vec	radial_vec;
	t_vec	hit_point;
	double	height_on_axis;
	t_vec	axis_proj;

	if (t < T_MIN || t > ctx->best_t)
		return ;
	hit_point = vec_add(ctx->c_ray->origin, vec_scale(ctx->c_ray->dir, t));
	center_to_hit = vec_sub(hit_point, ctx->cyl->center);
	height_on_axis = vec_dot(center_to_hit, ctx->cyl->axis);
	if (height_on_axis < -ctx->half_height || height_on_axis > ctx->half_height)
		return ;
	axis_proj = vec_scale(ctx->cyl->axis, height_on_axis);
	radial_vec = vec_sub(center_to_hit, axis_proj);
	ctx->best_t = t;
	ctx->hit->t = t;
	ctx->hit->intersection = hit_point;
	ctx->hit->normal = vec_normalize(radial_vec);
	if (vec_dot(ctx->hit->normal, ctx->c_ray->dir) > 0.0)
		ctx->hit->normal = vec_neg(ctx->hit->normal);
	ctx->hit->color = ctx->cyl->color;
}

bool	best_t_for_body(double t_root[2], const t_ray *c_ray,\
	t_cyl *cyl, t_hit *hit)
{
	t_body_ctx	ctx;

	ctx.c_ray = c_ray;
	ctx.cyl = cyl;
	ctx.hit = hit;
	ctx.half_height = cyl->height * 0.5;
	ctx.best_t = T_MAX;
	try_body_root(&ctx, t_root[0]);
	try_body_root(&ctx, t_root[1]);
	if (ctx.best_t == T_MAX)
		return (false);
	return (true);
}
