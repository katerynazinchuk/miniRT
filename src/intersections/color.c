#include "rt.h"

uint32_t	rgba(int r, int g, int b)
{
	return (((uint32_t)r << 24) | ((uint32_t)g << 16) | (uint32_t)b << 8 | 255);
}


uint32_t	find_color(t_ray ray, t_scene *scene)
{
	uint32_t	color;
	double	t;
	(void)scene;
//for test
// pl 0,0,0 0,1,0 150,150,150
// pl -11,0,0 1,0,0 180,180,255
// pl 0,0,20 0,0,-1 255,200,200
	// t_plane	plane_test;

	// t_hit_record closest = find_closest_hit();
	t_sphere sphere_test;
	sphere_test.center = vec_pos(0.0, 0.0, 2.0);
	sphere_test.radius = 2.0;
	// plane_test.point = vec_pos(0.0, 0.0, 0.0);
	// plane_test.normal = vec_pos(0.0, 10.0, 0.0);
	// plane_test.normal = vec_normalize(plane_test.normal);

	// if (hit_plane(&ray, &plane_test, &t))
	// printf("Ray dir length: %f\n", vec_length(ray.direction));
	if(hit_sphere(&ray, &sphere_test, &t))
	{
		color = rgba(0, 0, 255);
	}
	else
	{
		color = rgba(50, 50, 50);
	}
	//find first hit
	//if no hit color = background_color(black)
	//else check_light
	return (color);
}