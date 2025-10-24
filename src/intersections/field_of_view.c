#include "rt.h"

/*
 * norm_x & norm_y - convert (x, y) in (-1, 1) coordinates with center (0, 0) in the center of window
 * aspect ratio - in case if will use window with width > height
 * scale – apply field of view (camera angle)
*/
t_ray	create_ray_per_pixel(t_camera *camera, int x, int y)
{
	t_ray	ray;
	t_vec	temp;
	double	norm_x;
	double	norm_y;
	
	ray.origin = camera->position;
	norm_x = (2.0 * x / (double)WIDTH - 1.0);//not sure do we need cast to float. It should be done automatically
	norm_y = 1.0 - (2.0 * y / (double)HEIGHT);
	norm_x = norm_x * camera->aspect;
	norm_x *= camera->scale;
	norm_y *= camera->scale;
	temp = vec_add(vec_scale(camera->right, norm_x), vec_scale(camera->up, norm_y));
	ray.direction = vec_normalize(vec_add(temp, camera->direction));
	return (ray);
}


