/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:55:34 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/11/11 15:44:14 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
 
//recieve a t -> bulitd vec_normalize(t);
//light_ray = vec_add(t, light_sourse);
//light_ray = vec_normalize(light_ray);
//brightness = cos(angle) = vec_dot(normal, light_ray);
// then we have to multiply the object color by the brightness factor vec_scale(t, brightness)
//diffuse = color * intencity

int find_light_spot(double t, t_scene *scene, t_color *color)
{
	t_vec hit_point;
	t_vec light_ray;
	double brightness;
	t_vec normal_for_t;

	normal_for_t = find_normal(scene, t, OBJ_SPHERE);

	light_ray = ved_add(t, scene->light.position);
	light_ray = vec_normalize(light_ray);
	brightness = vec_dot(normal_for_t, light_ray);
	*color = vec_scale(t, brightness);// how will i get actual color if i return t_vec here
	//but actually i need a different color parametr then one i recieve from the input;
}

t_vec find_normal(t_scene *scene, t_vec *t, t_objtype type)
{
	t_vec normalized_vec;
	
	if(scene->objects.type == OBJ_PLANE)
	{
		
	}
	else if(scene->objects.type == OBJ_SPHERE)
	{
		normalized_vec = vec_sub(scene->objects.shape.sp.center, t);//is this a corect way to normalize things?
		return (normalized_vec);
	}
	else if(scene->objects.type == OBJ_CYL)
	{
		if(recieved t is from cyl_body)
		{
			//one formula;
		}
		if(recieved t is from cyl_cap)
		{
			//another formula;
		}
	}
	return (normalized_vec);
}