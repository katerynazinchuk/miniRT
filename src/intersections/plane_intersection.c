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
// bool	hit_cylinder(t_ray *c_ray, t_plane *plane, double *t)
// {

// }

// bool	hit_sphere(t_ray *c_ray, t_sphere *sphere, double *t)
// {
	
// }
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