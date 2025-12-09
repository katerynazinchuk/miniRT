#include "rt.h"
 
//recieve a t -> bulitd vec_normalize(t);
//light_ray = vec_add(t, light_sourse);
//light_ray = vec_normalize(light_ray);
//brightness = cos(angle) = vec_dot(normal, light_ray);
// then we have to multiply the object color by the brightness factor vec_scale(t, brightness)
//diffuse = color * intencity

// static t_color	get_hit_color_bonus(t_scene *scene, t_hit_rec *hit_rec);
// static bool		is_in_shadow_bonus(t_scene *scene, t_hit_rec *hit_rec);
static t_color	handle_final_color(t_scene *scene, t_hit_rec *hit, t_color final_color);

int	find_light_spot_bonus(t_scene *scene, t_hit_rec *hit_rec)
{
	t_color	final_color;

	// final_color = to_rgba(BACKGROUND_COLOR);
	final_color = (t_color){0,0,0};
	handle_multi_lights(scene, &scene->l_sp, hit_rec, &final_color);//case of error?
	hit_rec->color = handle_final_color(scene, hit_rec, final_color);
	return (0);
}
/* go through all light spots and save information about each ray */
int	handle_multi_lights(t_scene *scene, t_l_spots *light, t_hit_rec *hit, t_color *color)
{
	t_light_basis	base;
	size_t			i;
	t_color			tmp_color;

	i = 0;
	while (i < light->l_count)
	{
		base.l_ray = vec_sub(light->l_arr[i].position, hit->intersection);//L=P_light​−P_hit  ​Lambert model
		base.l_ray = vec_normalize(base.l_ray);
		base.l_color = get_hit_color(scene, hit);
		if(is_in_shadow(scene, hit, i))
			tmp_color = (t_color){0,0,0};
			// tmp_color = to_rgba(0x0);
		else
		{
			base.dif = fmax(0.0, vec_dot(hit->normal, base.l_ray));
			base.dif = base.dif * light->l_arr[i].intensity;
/* 			dif = dif + scene->ambient.ratio;
			dif = fmin(1.0, dif);*/
			tmp_color = color_scale(base.l_color, base.dif);
/* 			this is for all spots  */
			// return (1);
		}
		*color = color_add(*color, tmp_color);
		i++;
	}
	return (0);//how to track error
}

bool is_in_shadow(t_scene *scene, t_hit_rec *hit_rec, int i)
{
	t_vec		light_dir;
	t_hit_rec	temp_rec;
	double		light_distance;
	t_ray 		shadow_ray;

	light_dir = vec_sub(scene->l_sp.l_arr[i].position, hit_rec->intersection);
	light_distance = vec_length(light_dir);
	light_dir = vec_normalize(light_dir);
	shadow_ray.origin = vec_add(hit_rec->intersection, vec_scale(hit_rec->normal, EPS));
	shadow_ray.direction = light_dir;
	temp_rec.t = INFINITY;

	if (hit_scene(&shadow_ray, scene, &temp_rec))//for all lights spot
	{
		if (temp_rec.t < light_distance && temp_rec.t > T_MIN)
			return (true);
	}
	return (false);
}

/* bool is_in_shadow(t_scene *scene, t_hit_rec *hit_rec)
{
	t_vec		light_dir;
	t_hit_rec	temp_rec;
	double		light_distance;
	t_ray 		shadow_ray;

	light_dir = vec_sub(scene->light.position, hit_rec->intersection);
	light_distance = vec_length(light_dir);
	light_dir = vec_normalize(light_dir);
	shadow_ray.origin = vec_add(hit_rec->intersection, vec_scale(hit_rec->normal, EPS));
	shadow_ray.direction = light_dir;
	temp_rec.t = INFINITY;

	if (hit_scene(&shadow_ray, scene, &temp_rec))//for all lights spot
	{
		if (temp_rec.t < light_distance && temp_rec.t > T_MIN)
			return (true);
	}
	return (false);
} */

t_color	get_hit_color(t_scene *scene, t_hit_rec *hit_rec)
{
	t_color	black;

    if (hit_rec->type == OBJ_SPHERE)
        return (scene->objects.sps[hit_rec->index].color);
    else if (hit_rec->type == OBJ_PLANE)
        return (scene->objects.pls[hit_rec->index].color);
    else if (hit_rec->type == OBJ_CYL)
        return (scene->objects.cys[hit_rec->index].color);
	else
		ft_memset(&black, 0, sizeof(t_color));
	return (black);
}

static t_color	handle_final_color(t_scene *scene, t_hit_rec *hit, t_color final_color)
{
	t_color	amb_color;
	double	amb;

	amb = scene->ambient.ratio;
	amb_color = color_scale(get_hit_color(scene, hit), amb);
	final_color = color_add(final_color, amb_color);
	final_color =color_clamp(final_color, 0, 255);
	return (final_color);
}
