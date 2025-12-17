/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder_caps.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 12:24:36 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/12/17 13:08:52 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

bool	hit_cyl_cap(const t_ray *c_ray, t_vec cap_center, t_vec normal,\
	t_hit *hit_rec, t_cyl *cyl)
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
