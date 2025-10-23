#include "rt.h"
/*

*/

t_vec	hit_plane(t_camera *camera, t_plane *plane)
{
	t_vec	intersection;
	float	t;

	// t = N * (P0 - O) / D * N
	// avoid divide by 0 (N * D != 0)
	t = (plane->normal * (plane->point - camera->possition))/
	
	t = vec_dot(plane->normal, vec_sub(plane->point, camera->possition)) / vec_dot(plane->normal, camera->direction);
	return (intersection);
}