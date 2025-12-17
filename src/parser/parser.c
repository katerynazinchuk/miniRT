/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:36:24 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/12/06 20:26:06 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

is the file name ends with .rt

1. parcing and reading input files
- file management (nonexistent, empty file)
- the types correspond to the requested types and nothing else
- there is a MAXIMUM of one camera, one diffused light and one ambient light
- each line corresponding to a type must have the right number of elements
- if its a color, it has to be in the right range (0-255) and the same goes for orientation vectors (-1,1), etc. 
Make sure all digits are in the correct range for each type.
- For each object, you also need to pay attention to its specific characteristics 
(whether the diameter or height of a cylinder is non-negative, for example, or other things).
___________________________________________________________________________________________________

2. intersections and ray tracing
- Send rays from the camera position to each pixel of the screen.
- Determine where each ray intersects with the objects in the scene (spheres, planes, cylinders).
- Calculate the precise points of intersection by solving equations or using geometric methods.
   - Intersection with a sphere
   - Intersection with a plane
   - Intersection with a cylinder
- Evaluate the distance between the camera and the intersection points to understand what's closest.
- Decide which object the ray hits first by comparing distances to the intersection points
- Once the closest object is identified we can try to find out what color the pixel will be and how bright it will be (next step)
3. managemet of light, shadows, colours
- Once the closest object is identified, cast new rays from the intersection point towards light sources.
- If one of these rays intersects with another object before it reaches the light source, it's like catching the object casting a shadow on itself. This shadow indicates that the point is not directly illuminated by the light.
- Conversely, if the ray reaches the light source without obstruction, the point basks in direct illumination – it's in the light.
    - When a point is in the light, assess the angle at which the light strikes the object's surface. This angle helps determine how intense the light's effect should be on the point (or any other method if you find a better one)
- Introduce the concept of ambient light, which mimics the soft, indirect illumination from all directions in the environment. This is like a gentle, uniform glow that helps prevent overly dark shadows.
- Contemplate how light attenuates, growing weaker as it travels. Objects farther from the light source receive less light intensity, which influences their brightness.
- Blend all these factors together, calculating how they contribute to the final color of the pixel at that point on the screen. This color is a result of intricate interactions between light and the object's characteristics.
4. graphic management (windows, hooks) with the MLX42
- Initialize minilibx
- Create a window
- Handler user inputs / hooks (close the program/window with the cross or by pressing ESC)
- Render the image (call your raytracing function)
- Display the image (put your pixels one by one)
*/

//https://42-cursus.gitbook.io/guide/4-rank-04/minirt/building-the-thing
#include "rt.h"

int	parse_ambient(t_rt *rt, char *line/* , int line_counter */)
{
	int	i;

	i = 1;
	if (!skip_spases(line, &i))
		return (0);
	rt->scene.ambient.ratio = ft_atof(line, &i);
	if (!skip_spases(line, &i))
		return (0);
	if (!parse_color(line, &i, &rt->scene.ambient.color))
		return 0;
	rt->scene.ambient.flag = true;
	return (1);
}

//float	angle;//in radiant so angle = 70 * M_PI / 180.0 and result will be in radiant
//float	scale;// scale = tan((camera->angle * 0,5));
//float	aspect;// aspect = (double)WIDTH / (double)HEIGHT;
int	parse_camera(t_rt *rt, char *line/* , int line_counter */)
{
	t_vec	world_up;
	int		i;

	i = 1;
	if (!skip_spases(line, &i))
		return (0);
	if (!parse_vector(line, &i, &rt->scene.camera.position, 0))
		return 0;
	if (!skip_spases(line, &i))
		return (0);
	if (!parse_vector(line, &i, &rt->scene.camera.direction, 0))
		return 0;
	rt->scene.camera.direction = vec_normalize(rt->scene.camera.direction);
	if (!skip_spases(line, &i))
		return (0); 
	rt->scene.camera.aspect = (double)WIDTH / (double)HEIGHT;
	world_up = vec_pos(0,1,0);
	rt->scene.camera.right = vec_cross(world_up, rt->scene.camera.direction);
	rt->scene.camera.right = vec_normalize(rt->scene.camera.right);
	rt->scene.camera.up = vec_cross(rt->scene.camera.direction, rt->scene.camera.right);
	rt->scene.camera.up = vec_normalize(rt->scene.camera.up);
	rt->scene.camera.angle = ft_atof(line, &i);
	rt->scene.camera.angle = rt->scene.camera.angle * M_PI/ 180.0;
	rt->scene.camera.scale = tan(rt->scene.camera.angle * 0.5);
	rt->scene.camera.flag = true;
	return (1);
}

int	parse_vector(char *line, int *i, t_vec *vec, int normal_range)
{
	vec->x = ft_atof(line, i);
	if (line[*i] != ',')
	{
		print_error("Input outside of the range");
		return (0);
	}
	(*i)++;
	vec->y = ft_atof(line, i);
	if (line[*i] != ',')
	{
		print_error("Input outside of the range");
		return (0);
	}
	(*i)++;
	vec->z = ft_atof(line, i);
	if(normal_range)
	{
		if(!check_vector(vec->x) || !check_vector(vec->y) || !check_vector(vec->z))
		{
			print_error("Input outside of the range");
			return (0);
		}
	}
	return (1);
}

/* int parse_vector(char *line, int *i, t_vec *vec, int normal_range)
{
	vec->x = ft_atof(line, i);
	if (line[*i] != ',')
        return (0);
	(*i)++;
	vec->y = ft_atof(line, i);
	if (line[*i] != ',')
    	return (0);
	(*i)++;
	vec->z = ft_atof(line, i);
	
	if(normal_range)
	{
		if(!check_vector(vec->x) || !check_vector(vec->y) || !check_vector(vec->z))
            return (0);
	}
	return (1);
} */

int	parse_color(char *line, int *i, t_color *color)
{
	color->r = (int)ft_atof(line, i);
	if (line[*i] != ',')
	{
		print_error("Color input outside of the range");
		return (0);
	}
	(*i)++;
	color->g = (int)ft_atof(line, i);
	if (line[*i] != ',')
	{
		print_error("Color input outside of the range");
		return (0);
	}
	(*i)++;
	color->b = (int)ft_atof(line, i);
	if(!check_color(color->r) || !check_color(color->g) || !check_color(color->b))
	{
		print_error("Color input outside of the range");
		return (0);
	}
	return(1);
}

/* int parse_color(char *line, int *i, t_color *color)
{
	color->r = (int)ft_atof(line, i);
	if (line[*i] != ',')
        return (0);
	(*i)++;
	color->g = (int)ft_atof(line, i);
	if (line[*i] != ',')
        return (0);
	(*i)++;
	color->b = (int)ft_atof(line, i);
	if(!check_color(color->r) || !check_color(color->g) || !check_color(color->b))
		return (0);
	return(1);
} */

