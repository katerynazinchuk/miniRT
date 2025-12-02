/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:11:03 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/12/01 20:23:24 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

//P(t) = O + tD;
//|(P - C) - ((P − C)· V)V|² = r²
//|(O + tD - C) - ((O + tD − C)· V)V|² = r²
//t_vec oc = vec_sub(c_ray->origin, cylinder->center);//O - C
//|(oc + tD) - ((oc + tD)· V)V|² = r²;
// (oc + tD)·V = (ox + t dx) vx + (oy + t dy) vy + (oz + t dz) vz
//= (ox vx + oy vy + oz vz) + t (dx vx + dy vy + dz vz)
//= oc·V + t (D·V)
//(oc+tD)⋅V=(oc⋅V)+t(D⋅V)
//oc - (oc · V)*V -  searching for the perp to the axis between part of the oc vector inside cylinder and its projection
// Project oc and ray direction onto plane perpendicular to axis

bool	hit_cyl_body(const t_ray *c_ray, t_cylinder *cylinder, t_hit_rec *hit_rec)
{
	t_vec	oc;
    double	oc_dot_axis;
    double	D_dot_axis;
    t_vec	oc_perp;
    t_vec	D_perp;
    double	a;
    double	half_b;
    double	c_perp;
    double	disc;
    double	sqrt_disc;
    double	t_root[2];
	
	oc = vec_sub(c_ray->origin, cylinder->center);//O - C
	oc_dot_axis = vec_dot(oc, cylinder->axis);
	//D - (D · V)*V
	const double D_dot_axis = vec_dot(c_ray->direction, cylinder->axis);
	oc_perp = vec_sub(oc, vec_scale(cylinder->axis, oc_dot_axis));//possition of the whole vector from camera to axis
	D_perp = vec_sub(c_ray->direction, vec_scale(cylinder->axis, D_dot_axis));// direction
	// Quadratic equation for infinite cylinder: at² + 2bt + c = 0
	a = vec_dot(D_perp, D_perp); //(D·D); c_ray->direction * c_ray->direction
	if (a < EPS)
		return false;
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
	t_vec	pc;
	t_vec	proj;
	t_vec	radial;
	t_vec	p;
	double	height_at_p;

	half_height = cylinder->height * 0.5;
	best_t = T_MAX;
	i = 0;
	
	while (i < 2)
	{
		if(t_root[i] >= T_MIN && t_root[i] <= best_t)
		{
			// Calculate the actual 3D point where the ray intersects the infinite cylinder
			p = vec_add(c_ray->origin, vec_scale(c_ray->direction, t_root[i]));
			// Get vector from cylinder center to intersection point
			pc = vec_sub(p, cylinder->center);
			// Project pc onto the cylinder's axis to find height position
			height_at_p = vec_dot(pc, cylinder->axis);
			if(height_at_p >= -half_height && height_at_p <= half_height)
			{
				proj = vec_scale(cylinder->axis, vec_dot(pc, cylinder->axis));
				radial = vec_sub(pc, proj);
				best_t = t_root[i];
				hit_rec->t = t_root[i];
				hit_rec->intersection = p;
				hit_rec->normal = vec_normalize(radial);
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
	t_vec		p;
	t_vec		cp;
	double		dist_sq;
	t_plane		cyl_cap;
	t_hit_rec	hit_rec;
	

	cyl_cap.point = cap_center;
	cyl_cap.normal = cap_normal;
	if(!hit_plane(c_ray, &cyl_cap, &hit_rec))
		return false;
	p = vec_add(c_ray->origin, vec_scale(c_ray->direction, hit_rec.t));// looking for the actual t on the surface
	cp = vec_sub(p, cap_center); //vec from intesection to the plane center
	dist_sq = vec_dot(cp, cp);// only operaton that return double for comparison
	if (dist_sq <= radius * radius)
	{ 
		*t = hit_rec.t;
		return (true);
	}
	return (false);
}

bool	hit_cylinder(const t_ray *c_ray, t_cylinder *cylinder, t_hit_rec *hit_rec)
{
	double		t_body;
	double		t_top;
	double		t_bottom;
	t_vec		top_center;
	t_vec		bottom_center;
	t_vec		bottom_normal;
	double		half_height;
	double		closest;

	t_body = -1;
	t_top = -1;
	t_bottom = -1;
	closest = -1;
	hit_cyl_body(c_ray, cylinder, &t_body);
	half_height = cylinder->height * 0.5;
	top_center = vec_add(cylinder->center, vec_scale(cylinder->axis, half_height));
	hit_cyl_cap(c_ray, top_center, cylinder->axis, &t_top, cylinder->radius);
	bottom_center = vec_sub(cylinder->center, vec_scale(cylinder->axis, half_height));
	bottom_normal = vec_neg(cylinder->axis);
	hit_cyl_cap(c_ray, bottom_center, bottom_normal, &t_bottom, cylinder->radius);
	if (t_body > 0)
		closest = t_body;
	if (t_top > 0 && (closest < 0 || t_top < closest))
		closest = t_top;
	if (t_bottom > 0 && (closest < 0 || t_bottom < closest))
		closest = t_bottom;
	if(closest < 0)
		return false;
	hit_rec->t = closest;
	// hit_rec->intersection = ;
	// hit_rec->normal = ;
	// hit_rec->object = cylinder->owner;
	return true;
}