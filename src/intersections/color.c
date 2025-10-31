#include "rt.h"

uint32_t	rgba(uint8_t r, uint8_t g, uint8_t b)
{
	return ((uint32_t)r << 24 | (uint32_t)b << 16 | (uint32_t)g << 8 );
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
	t_plane	plane_test;
	t_vec	norm;
	norm = vec_pos(0.0, 1.0, 0.0);
	plane_test.point = vec_pos(0.0, 0.0, 0.0);
	plane_test.normal = vec_normalize(norm);

	if (hit_plane(&ray, &plane_test, &t))
	{
		color = rgba(255, 0, 0);
		// color.r= 255;
		// color.g= 128;
		// color.b= 0;
	}
	else
	{
		color = rgba(0, 255, 0);
		// color.r= 0;
		// color.g= 0;
		// color.b= 0;
	}
	//find first hit
	//if no hit color = background_color(black)
	//else check_light
	return (color);
}
/* t_color	find_color(t_ray ray, t_scene *scene)
{
	t_color	color;

	//find first hit
	//if no hit color = background_color(black)
	//else check_light
	if (!hit())
		ft_memset(color, '0', sizeof(t_color));
	
	return (color);
} */
