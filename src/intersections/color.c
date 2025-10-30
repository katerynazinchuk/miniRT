#include "rt.h"

uint32_t	find_color(t_ray ray, t_scene *scene)
{
	uint32_t	color;
	double	t;
	(void)scene;
//for test
	t_plane	plane_test;
	plane_test.point = vec_pos(0.0, 0.0, -10.0);
	plane_test.normal = vec_pos(0.0, 1.0, 0.0);

	if (hit_plane(&ray, &plane_test, &t))
	{
		color = 0xFF90EE90;
		// color.r= 255;
		// color.g= 128;
		// color.b= 0;
	}
	else
	{
		color = 0x0;
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