#include "rt.h"
/*
 so logic:
 1 - build intersections for plane & sphere (find is it happens, if yes find dot)
 2 - build rays to light
 3 - choose color based on previuos calculations

 if num == 0 it means plane and ray are parallel / orthogonal, so no intersection
 	// t = N * (P0 - O) / D * N
	// avoid divide by 0 (N * D != 0)
 if t < 0 then intersection behind camera

 need to check how to take into account math errors(Uncertainty) and whether it is necessary
*/

/* function check is there intersection by using bool and setup value in t */
bool	hit_cylinder_body(t_ray *c_ray, t_cylinder *cylinder, double *t)
{
	//P(t) = O + tD;
	//|(P - C) - ((P − C)· V)V|² = r²
	//|(O + tD - C) - ((O + tD − C)· V)V|² = r²
	t_vec oc = vec_sub(c_ray->origin, cylinder->center);//O - C
	//|(oc + tD) - ((oc + tD)· V)V|² = r²;
	// (oc + tD)·V = (ox + t dx) vx + (oy + t dy) vy + (oz + t dz) vz
    //= (ox vx + oy vy + oz vz) + t (dx vx + dy vy + dz vz)
    //= oc·V + t (D·V)
	//(oc+tD)⋅V=(oc⋅V)+t(D⋅V)
	//oc - (oc · V)*V -  searching for the perp to the axis between part of the oc vector inside cylinder and its projection
	// Project oc and ray direction onto plane perpendicular to axis
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
	double t1 = (-half_b + sqrt_disk) / a;
	double t2 = (-half_b - sqrt_disk) / a;
	double half_heigth = cylinder->height * 0.5;
	if(t1 >= T_MIN || t1 <= T_MAX)
	{
		// Calculate the actual 3D point where the ray intersects the infinite cylinder
		// Formula: P = Origin + t × Direction
		t_vec p1 = vec_add(c_ray->origin, vec_scale(c_ray->direction, t1));
		// Get vector from cylinder center to intersection point
		// This tells us where p1 is relative to the cylinder's center
		t_vec cp1 = vec_sub(p1, cylinder->center);
		// Project cp1 onto the cylinder's axis to find height position
		double height_at_p1 = vec_dot(cp1, cylinder->axis);
		if(height_at_p1 >= -half_heigth && height_at_p1 <= half_heigth)
		{
			*t = t1;
			return true;
		}
	}
	if(t2 >= T_MIN || t2 <= T_MAX)
	{
		// Calculate the actual 3D point where the ray intersects the infinite cylinder
		// Formula: P = Origin + t × Direction
		t_vec p2 = vec_add(c_ray->origin, vec_scale(c_ray->direction, t2));
		// Get vector from cylinder center to intersection point
		// This tells us where p1 is relative to the cylinder's center
		t_vec cp2 = vec_sub(p1, cylinder->center);
		// Project cp1 onto the cylinder's axis to find height position
		double height_at_p2 = vec_dot(cp2, cylinder->axis);
		if(height_at_p2 >= -half_heigth && height_at_p2 <= half_heigth)
		{
			*t = t2;
			return true;
		}
	}
	return false;
}
	//oc_perp + t * D_perp = r;
	int camera_pos = 0;
	double r2 = cylinder->radius * cylinder->radius;
	double distance2 = vec_dot(oc_perp, oc_perp);
	if(fabs(distance2 -r2) < EPS)
		camera_pos = 1
	else if(distance2 < r2)
		camera_pos = -1;
	else
		camera_pos = 0;
	
	// find two discs that cut the infinite cylinder
	//and by comparing two vectors distinguish is my dot within the range of height
	//choose the minimal t
	

bool hit_cyl_cap(t_ray *c_ray, t_cylinder *cylinder, double *t)
{
	
}

bool	hit_cylinder(t_ray *c_ray, t_cylinder *cylinder, double *t)
{
	//V - cylinder axis
	double half_heigth = cylinder->height * 0.5;
	hit_cylinder;
	hit_cyl_cap;
	hit_cyl_cap;


}

bool	hit_sphere(const t_ray *c_ray, const t_sphere *sphere, double *t)
{
	//P(t) = O + tD
	//|X − C|² = r²
	//|(O + tD) − C|² = r²
	//oc = O - C
	t_vec oc = vec_sub(c_ray->origin, sphere->center);//to know how far camers is from sphere center
	//|(oc + tD|² = r²
	//|(oc + tD|² = (oc + t·D) · (oc + t·D) = oc·oc + 2t (oc·D) + t² (D·D)
	// oc·oc + 2t (oc·D) + t² (D·D) = r²
	//t² (D·D) + 2t (oc·D) + (oc·oc − r²) = 0, where a = (D·D), b = 2(oc·D), c = oc·oc - r²
	//at² + 2·half_b·t + c = 0
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

t_vec	find_point(t_ray *c_ray, double t)
{
	t_vec	point;

	point = vec_add(c_ray->origin, vec_scale(c_ray->direction, t));
	return (point);
}

// check all objects in the scene
