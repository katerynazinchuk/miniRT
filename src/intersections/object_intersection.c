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

bool	hit_cyl_body(t_ray *c_ray, t_cylinder *cylinder, double *t)
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

bool hit_cyl_cap(t_ray *c_ray, t_vec cap_center, t_vec cap_normal,  double *t, double radius)
{
	t_vec p;
	t_vec cp;
	double dist_sq;
	t_plane cyl_cap;

	cyl_cap.point = cap_center;
	cyl_cap.normal = cap_normal;
	double t_cap;
	if(!hit_plane(c_ray, &cyl_cap, &t_cap))
		return false;
	p = vec_add(c_ray->origin, vec_scale(c_ray->direction, t_cap));// looking for the actual t on the surface
	cp = vec_sub(p, cap_center); //vec from intesection to the plane center
	dist_sq = vec_dot(cp, cp);// only operaton that return double for comparison
	if (dist_sq <= radius * radius)
	{ 
		*t = t_cap;
		return (true);
	}
	return (false);
}

bool	hit_cylinder(t_ray *c_ray, t_cylinder *cylinder, double *t)
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
	*t = closest;
	return true;
}

bool	hit_sphere(const t_ray *c_ray, const t_sphere *sphere, double *t)
{
	t_vec oc = vec_sub(c_ray->origin, sphere->center);
	double a = vec_dot(c_ray->direction, c_ray->direction); //(D·D); c_ray->direction * c_ray->direction
	double half_b = vec_dot(oc, c_ray->direction);//oc * c_ray->direction;
	double c = vec_dot(oc, oc) - (sphere->radius * sphere->radius);//oc * oc - sphere->radius * sphere->radius;
	double disc = (half_b * half_b) - (a * c);
	if(disc < 0)
		return false;
	//var for getting root. result of moving elements to the right to find clean t from squere equesion
	double root = (-half_b - sqrt(disc)) / a;//first cross cos it always smaller
	if(root < T_MIN || root > T_MAX)
	{
		root = (-half_b + sqrt(disc)) / a;//second cross cos it bigger
		if(root < T_MIN || root > T_MAX)
			return false;
	}
	*t = root;
	return true;
}

bool	hit_plane(const t_ray *c_ray, const t_plane *plane, double *t)
{
	double	denum;

	//printf("plane normal x = %f, y = %f, z = %f\n", plane->normal.x, plane->normal.y, plane->normal.z);
	denum = vec_dot(plane->normal, c_ray->direction);
	if (fabs(denum) < EPS)
		return (false);
	*t = vec_dot(plane->normal, vec_sub(plane->point, c_ray->origin)) / denum;
	if (*t < T_MIN || *t > T_MAX)
		return (false);
	return (true);
}

// t_vec	find_point(t_ray *c_ray, double t)
// {
// 	t_vec	point;

// 	point = vec_add(c_ray->origin, vec_scale(c_ray->direction, t));
// 	return (point);
// }

// // check all objects in the scene
// int	hit_space ()
// {

// }