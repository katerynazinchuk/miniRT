#include "rt.h"
/*add aspect ratio & scale into t_camera to avoid unneseccary calculation*/
t_ray	create_ray_per_pixel(t_camera *camera, int x, int y)
{
	t_ray	ray;
	t_vec	d;
	double	norm_x;
	double	norm_y;
	
	ray.origin = camera->position;
	norm_x = (2.0 * x / (double)WIDTH - 1.0);//not sure do we need cast to float. It should be done automatically
	norm_y = 1.0 - (2.0 * y / (double)HEIGHT);
	norm_x = norm_x * camera->aspect;
	norm_x *= camera->scale;
	norm_y *= camera->scale;
	ray.d = vec_add(camera->direction, vec_scale(camera->right, norm_x) );
	// d.x = norm_x;
	// d.y = norm_y;
	// d.z = - 1.0;
	ray.direction = vec_normalize(ray.direction);
	return (ray);
}


