#include "rt.h"
 
//recieve a t -> bulitd vec_normalize(t);
//light_ray = vec_add(t, light_sourse);
//light_ray = vec_normalize(light_ray);
//brightness = cos(angle) = vec_dot(normal, light_ray);
// then we have to multiply the object color by the brightness factor vec_scale(t, brightness)
//diffuse = color * intencity

static t_color	get_hit_color_bonus(t_scene *scene, t_hit_rec *hit_rec);
static bool		is_in_shadow_bonus(t_scene *scene, t_hit_rec *hit_rec);

int	find_light_spot_bonus(t_scene *scene, t_hit_rec *hit_rec)
{
	t_color	final_color;

	final_color = to_rgb(BACKGROUND_COLOR);
	handle_multi_lights(scene, scene->l_sp, hit_rec, &final_color);//case of error?
	hit_rec->color = handle_final_color(scene, final_color);
	return (0);
}
/* go through all light spots and save information about each ray */
int	handle_multi_lights(t_scene *scene, t_l_spots *light, t_hit *hit, t_color *color)
{
	t_light_basis	base;
	size_t			i;
	t_color			tmp;

	i = 0;
	while (i < light->l_count)
	{
		base.l_ray = vec_sub(l_sp->l_arr[i].position, hit->intersection);//L=P_light​−P_hit  ​Lambert model
		base.l_ray = vec_normalize(base.l_ray);
		base.l_color = get_hit_color(scene, hit);
		if(is_in_shadow(scene, hit))
			tmp = to_rgb(0x0);
		else
		{
			base.dif = fmax(0.0, vec_dot(hit->normal, l_sp->l_ray));
			base.dif = base.dif * scene->light.intensity;
/* 			dif = dif + scene->ambient.ratio;
			dif = fmin(1.0, dif);*/
			*color = color_scale(base, dif);
/* 			this is for all spots  */
			return (1);
		}
	}

	return (0);//how to track error
}


bool is_in_shadow_bonus(t_scene *scene, t_hit_rec *hit_rec)
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
}

static t_color	get_hit_color_bonus(t_scene *scene, t_hit_rec *hit_rec)
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
