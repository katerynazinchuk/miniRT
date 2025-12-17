/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:11:03 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/12/17 12:41:12 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool	hit_cyl_body(const t_ray *c_ray, t_cylinder *cylinder, t_hit_rec *hit_rec)
{
	t_vec	oc;//origin to center
    double	oc_dot_axis;//dot product of oc and axis
    double	D_dot_axis;// dot product of direction and axis
    t_vec	oc_perp;//part of ac which perp to axis
    t_vec	D_perp;//part of direction which perp to axis
    double	a;
    double	half_b;
    double	c_perp;
    double	disc;
    double	sqrt_disc;
    double	t_root[2];
	
	oc = vec_sub(c_ray->origin, cylinder->center);
	oc_dot_axis = vec_dot(oc, cylinder->axis);
	D_dot_axis = vec_dot(c_ray->direction, cylinder->axis);
	oc_perp = vec_sub(oc, vec_scale(cylinder->axis, oc_dot_axis));//possition of the whole vector from camera to axis
	D_perp = vec_sub(c_ray->direction, vec_scale(cylinder->axis, D_dot_axis));// direction
	// Quadratic equation for infinite cylinder: at² + 2bt + c = 0
	a = vec_dot(D_perp, D_perp); //(D·D); c_ray->direction * c_ray->direction
	if (a < EPS)
		return (false);
	half_b = vec_dot(oc_perp, D_perp);//oc * c_ray->direction;
	c_perp = vec_dot(oc_perp, oc_perp) - (cylinder->radius * cylinder->radius);//oc * oc - cylinder->radius * cylinder->radius;
	disc = (half_b * half_b) - (a * c_perp);
	if(disc < 0.0 )
		return false;
	sqrt_disc = sqrt(disc);
	t_root[0] = (-half_b - sqrt_disc) / a;
	t_root[1] = (-half_b + sqrt_disc) / a;

	if(find_best_t_for_body(t_root, c_ray, cylinder, hit_rec))
		return true;
	return false;
}

bool find_best_t_for_body(double t_root[2], const t_ray *c_ray, t_cylinder *cylinder, t_hit_rec *hit_rec)
{
	double	half_height;
	double	best_t;
	int		i;
	t_vec	center_to_hit;
	t_vec	axis_proj;
	t_vec	radial_vec;//perp radial vector from axis to the surface point
	t_vec	hit_point;
	double	height_on_axis;

	half_height = cylinder->height * 0.5;
	best_t = T_MAX;
	i = 0;
	while (i < 2)
	{
		if(t_root[i] >= T_MIN && t_root[i] <= best_t)
		{
			hit_point = vec_add(c_ray->origin, vec_scale(c_ray->direction, t_root[i]));// Calculate the actual 3D point where the ray intersects the infinite cylinder
			center_to_hit = vec_sub(hit_point, cylinder->center);// Get vector from cylinder center to intersection point
			height_on_axis = vec_dot(center_to_hit, cylinder->axis);//is it within the height range // Project center_to_hit onto the cylinder's axis to find height position
			if(height_on_axis >= -half_height && height_on_axis <= half_height)
			{
				axis_proj = vec_scale(cylinder->axis, height_on_axis);// proj of center_to_hit vec on axis to know its height
				radial_vec = vec_sub(center_to_hit, axis_proj);//take off the axis part to get the radial vector so perp to axis so surface as well
				best_t = t_root[i];
				hit_rec->t = t_root[i];
				hit_rec->intersection = hit_point;
				hit_rec->normal = vec_normalize(radial_vec);
				if (vec_dot(hit_rec->normal, c_ray->direction) > 0.0)
					hit_rec->normal = vec_neg(hit_rec->normal);
				hit_rec->color = cylinder->color;
			}
		}
		i++;
	}
	if(best_t == T_MAX)
		return(false);
	return(true);
}

bool hit_cyl_cap(const t_ray *c_ray, t_vec cap_center, t_vec cap_normal, t_hit_rec *hit_rec, double radius)
{
	t_vec		center_to_hit;
	double		dist_sq;
	t_plane		cap_plane;
	t_hit_rec	cap_hit;
	

	cap_plane.point = cap_center;
	cap_plane.normal = cap_normal;
	if(!hit_plane(c_ray, &cap_plane, &cap_hit))
		return (false);
	center_to_hit = vec_sub(cap_hit.intersection, cap_center); //vec from intesection to the plane center
	dist_sq = vec_dot(center_to_hit, center_to_hit);
	if (dist_sq <= radius * radius)
	{ 
		*hit_rec = cap_hit;
		hit_rec->color = cap_hit.color;//??
		hit_rec->type = OBJ_PLANE;
		return (true);	
	}
	return (false);
}

bool	hit_cylinder(const t_ray *c_ray, t_cylinder *cylinder, t_hit_rec *hit_rec)
{
	t_vec		top_center;
	t_vec		bottom_center;
	t_vec		bottom_normal;
	double		half_height;
	t_hit_rec	body_hit;
	t_hit_rec	top_cap_hit;
	t_hit_rec	bottom_cap_hit;
	t_hit_rec	*closest_hit;
	bool		is_body_hit;
	bool		is_top_hit;
	bool		is_bottom_hit;
	
	half_height = cylinder->height * 0.5;
	hit_rec->color = cylinder->color;
	is_body_hit = hit_cyl_body(c_ray, cylinder, &body_hit);
	top_center = vec_add(cylinder->center, vec_scale(cylinder->axis, half_height));
	is_top_hit = hit_cyl_cap(c_ray, top_center, cylinder->axis, &top_cap_hit, cylinder->radius);
	bottom_center = vec_sub(cylinder->center, vec_scale(cylinder->axis, half_height));
	bottom_normal = vec_neg(cylinder->axis);
	is_bottom_hit = hit_cyl_cap(c_ray, bottom_center, bottom_normal, &bottom_cap_hit, cylinder->radius);
	closest_hit = NULL;
	if (is_body_hit)
		closest_hit = &body_hit;
	if (is_top_hit && (!closest_hit || top_cap_hit.t < closest_hit->t))
		closest_hit = &top_cap_hit;
	if (is_bottom_hit && (!closest_hit || bottom_cap_hit.t < closest_hit->t))
		closest_hit = &bottom_cap_hit;
	if (closest_hit == NULL)
		return false;
	*hit_rec = *closest_hit;
	hit_rec->type = OBJ_CYL;
	hit_rec->color = cylinder->color;
	return true;
}
