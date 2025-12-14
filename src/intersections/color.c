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

uint32_t	find_color(t_ray ray, t_scene *scene)
{
	t_hit_rec	hit_rec;
	uint32_t	color;

	hit_rec.camera_pos = scene->camera.position;
	// hit_rec.c_direction = vec_normalize(vec_neg(ray.direction));
	// hit_rec.c_direction = vec_normalize(vec_scale(ray.direction, -1));
	// vec_normalize(vec_scale(hit->direction, -1))
	color = rgba(110, 110, 110);
	if (hit_scene(&ray, scene, &hit_rec))
	{
		find_light_spot_bonus(scene, &hit_rec);
		color = rgba(hit_rec.color.r, hit_rec.color.g, hit_rec.color.b);
		// printf("here/n");
		// if (find_light_spot_bonus(scene, &hit_rec))
		// 	color = rgba(hit_rec.color.r, hit_rec.color.g, hit_rec.color.b);
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

t_color	color_mult(t_color one, t_color two)
{
	t_color	res;

	res.r = (int)(((double)one.r * two.r) / 255);
	res.g = (int)(((double)one.g * two.g) / 255);
	res.b = (int)(((double)one.b * two.b) / 255);
	return (res);
}
