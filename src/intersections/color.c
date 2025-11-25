#include "rt.h"

uint32_t	rgba(int r, int g, int b)
{
	return (((uint32_t)r << 24) | ((uint32_t)g << 16) | (uint32_t)b << 8 | 255);
}


// uint32_t	find_color(t_ray ray, t_scene *scene)
// {
// 	uint32_t	color = 0;
// 	(void)scene;
// 	t_hit_rec hit_rec;
// 	t_objects test_obj;

//     test_obj.material.albedo.r = 0;
//     test_obj.material.albedo.g = 255;
//     test_obj.material.albedo.b = 0;
// //for test
// // pl 0,0,0 0,1,0 150,150,150
// // pl -11,0,0 1,0,0 180,180,255
// // pl 0,0,20 0,0,-1 255,200,200
// 	// t_plane	plane_test;
// 	t_sphere sphere_test;
// 	// t_cylinder cyl_test;
// 	// cyl_test.axis = vec_pos(3.0, 5.0, 4.0);
// 	// cyl_test.axis = vec_normalize(cyl_test.axis);
// 	// cyl_test.center = vec_pos(0.0, 0.0, 0.0);
// 	// cyl_test.height = 5;
// 	// cyl_test.radius = 3;

// 	sphere_test.center = vec_pos(0.0, 0.0, 0.0);
// 	sphere_test.radius = 3;
// 	sphere_test.owner = &test_obj;
// 	// plane_test.point = vec_pos(0.0, 0.0, 0.0);
// 	// plane_test.normal = vec_pos(0.0, 10.0, 0.0);
// 	// plane_test.normal = vec_normalize(plane_test.normal);

// 	// if (hit_plane(&ray, &plane_test, &t))
// 	if(hit_sphere(&ray, &sphere_test, &hit_rec))
// 	//if(hit_cylinder(&ray, &cyl_test, &t))
// 	{
// 		if(find_light_spot(scene, &hit_rec))
// 			color = rgba(hit_rec.color.r, hit_rec.color.g, hit_rec.color.b);
// 	}
// 	else
// 	{
// 		color = rgba(110, 110, 110);
// 	}
// 	//find first hit
// 	//if no hit color = background_color(black)
// 	//else check_light
// 	return (color);
// }


uint32_t	find_color(t_ray ray, t_scene *scene)
{
	t_hit_rec	hit_rec;
	uint32_t	color;

	color = rgba(110, 110, 110);

	if (hit_scene(&ray, scene, &hit_rec))
	{
		if (find_light_spot(scene, &hit_rec))
			color = rgba(hit_rec.color.r, hit_rec.color.g, hit_rec.color.b);
	}
	return (color);
}