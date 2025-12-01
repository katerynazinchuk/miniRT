/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:11:03 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/12/01 17:12:37 by tchernia         ###   ########.fr       */
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

bool	hit_cyl_body(const t_ray *c_ray, t_cylinder *cylinder, double *t)
{
	t_vec oc = vec_sub(c_ray->origin, cylinder->center);//O - C
	const double oc_dot_V = vec_dot(oc, cylinder->axis);
	t_vec oc_perp = vec_sub(oc, vec_scale(cylinder->axis, oc_dot_V));//possition of the whole vector from camera to axis
	//D - (D · V)*V
	const double D_dot_V = vec_dot(c_ray->direction, cylinder->axis);
	t_vec D_perp = vec_sub(c_ray->direction, vec_scale(cylinder->axis, D_dot_V));// direction
	// Quadratic equation for infinite cylinder: at² + 2bt + c = 0
	double a = vec_dot(D_perp, D_perp); //(D·D); c_ray->direction * c_ray->direction
	double half_b = vec_dot(oc_perp, D_perp);//oc * c_ray->direction;
	double c_perp = vec_dot(oc_perp, oc_perp) - (cylinder->radius * cylinder->radius);//oc * oc - cylinder->radius * cylinder->radius;
	double disc = (half_b * half_b) - (a * c_perp);
	if(disc < 0 )
		return false;
	double sqrt_disk = sqrt(disc);
	double t1 = (-half_b - sqrt_disk) / a;
	double t2 = (-half_b + sqrt_disk) / a;
	double half_height = cylinder->height * 0.5;
	if(t1 >= T_MIN && t1 <= T_MAX)
	{
		// Calculate the actual 3D point where the ray intersects the infinite cylinder
		t_vec p1 = vec_add(c_ray->origin, vec_scale(c_ray->direction, t1));
		// Get vector from cylinder center to intersection point
		t_vec cp1 = vec_sub(p1, cylinder->center);
		// Project cp1 onto the cylinder's axis to find height position
		double height_at_p1 = vec_dot(cp1, cylinder->axis);
		if(height_at_p1 >= -half_height && height_at_p1 <= half_height)
		{
			*t = t1;
			return true;
		}
	}
	if (t2 >= T_MIN && t2 <= T_MAX)
	{
		// Calculate the actual 3D point where the ray intersects the infinite cylinder
		t_vec p2 = vec_add(c_ray->origin, vec_scale(c_ray->direction, t2));
		// Get vector from cylinder center to intersection point
		t_vec cp2 = vec_sub(p2, cylinder->center);
		// Project cp1 onto the cylinder's axis to find height position
		double height_at_p2 = vec_dot(cp2, cylinder->axis);
		if(height_at_p2 >= -half_height && height_at_p2 <= half_height)
		{
			*t = t2;
			return true;
		}
	}
	return false;
}

bool hit_cyl_cap(const t_ray *c_ray, t_vec cap_center, t_vec cap_normal,  double *t, double radius)
{
	t_vec p;
	t_vec cp;
	double dist_sq;
	t_plane cyl_cap;
	t_hit_rec hit_rec;
	

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
	double t_body;
	double t_top;
	double t_bottom;
	t_vec top_center;
	t_vec bottom_center;
	t_vec bottom_normal;
	double half_height;
	double closest;

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
	return true;
}