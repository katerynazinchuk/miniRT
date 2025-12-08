#include "rt.h"
 
//recieve a t -> bulitd vec_normalize(t);
//light_ray = vec_add(t, light_sourse);
//light_ray = vec_normalize(light_ray);
//brightness = cos(angle) = vec_dot(normal, light_ray);
// then we have to multiply the object color by the brightness factor vec_scale(t, brightness)
//diffuse = color * intencity

static t_color	get_hit_color_bonus(t_scene *scene, t_hit_rec *hit_rec);
static bool is_in_shadow_bonus(t_scene *scene, t_hit_rec *hit_rec);

int find_light_spot_bonus(t_scene *scene, t_hit_rec *hit_rec)
{
	t_light_basis	l_base;

	if (!init_light_basis(scene, l_base))
		return (0);//handle_error and go upper in clear way
	handle_multi_lights(scene, scene->l_sp, l_base);//case of error?
	handle_final_color();
	return (0);
}

int	handle_multi_lights(t_scene *scene, t_l_spots *spot, t_light_basis *base, t_hit_rec *hit_rec)
{
	while ()
	{
		base->l_ray = vec_sub(scene->light.position, hit_rec->intersection);//L=P_light​−P_hit  ​Lambert model
		base->l_ray = vec_normalize(base->l_ray);
		l_color = get_hit_color(scene, hit_rec);
		if(is_in_shadow(scene, hit_rec))//
		{
			l_sp->color = color_scale(base, scene->ambient.ratio);
			return (1);
		}
		else
		{
			brightness = fmax(0.0, vec_dot(hit_rec->normal, l_sp->l_ray));
			brightness = brightness * scene->light.intensity;
/* 			brightness = brightness + scene->ambient.ratio;
			brightness = fmin(1.0, brightness);
			hit_rec->color = color_scale(base, brightness);
			this is for all spots */
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
