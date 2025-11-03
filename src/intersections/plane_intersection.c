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

bool	hit_plane(t_ray *c_ray, t_plane *plane, double *t)
{
	double	num;

	num = vec_dot(plane->normal, c_ray->direction);
	if (num == 0)
		return (false);
	*t = vec_dot(plane->normal, vec_sub(plane->point, c_ray->origin)) / num;
	if (*t < 0)
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