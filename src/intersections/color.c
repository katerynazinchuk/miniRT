#include "rt.h"
static double	clamp(double num, double min, double max);

uint32_t	rgba(int r, int g, int b)
{
	return (((uint32_t)r << 24) | ((uint32_t)g << 16) | (uint32_t)b << 8 | 255);
}

t_color	to_rgba(int hex_num)
{
	t_color	color;

	color.r = (hex_num >> 24) & 0xFF;
	color.g = (hex_num >> 16) & 0xFF;
	color.b = (hex_num >> 8) & 0xFF;
	// color.a = hex_num & 0xFF
	return(color);
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

	color = BACKGROUND_COLOR;
	if (hit_scene(&ray, scene, &hit_rec))
	{
		if (find_light_spot_bonus(scene, &hit_rec))
			color = rgba(hit_rec.color.r, hit_rec.color.g, hit_rec.color.b);
	}
	return (color);
}

t_color	color_add(t_color one, t_color two)
{
	t_color	res;

	res.r = one.r + two.r;
	res.g = one.g + two.g;
	res.b = one.b + two.b;
	return (res);
}

t_color	color_clamp(t_color color, int min, int max)
{
	t_color	res_color;

	res_color.r = clamp(color.r, min, max);
	res_color.g = clamp(color.g, min, max);
	res_color.b = clamp(color.b, min, max);
	return (res_color);
}
static double	clamp(double num, double min, double max)
{
	if (num < min)
		return (min);
	if (num > max)
		return (max);
	return (num);
}
