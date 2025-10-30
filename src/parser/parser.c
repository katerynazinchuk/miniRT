/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:36:24 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/10/29 19:52:09 by kzinchuk         ###   ########.fr       */
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

int parse_ambient(t_rt *rt, char *line, int line_counter)
{
	int	i;

	i = 1;
	if(!skip_spases(line, &i))
		validate_error(line_counter);
	rt->scene.ambient.ratio = ft_atof(line, &i);
	if(!skip_spases(line, &i))
		validate_error(line_counter);
	if(!parse_color(line, &i, &rt->scene.ambient.color))
	{
		ft_putendl_fd("Error: Input outside of the range", 2);
		return 0;
	}
	return(1);
}
//float	angle;//in radiant so angle = 70 * M_PI / 180.0 and result will be in radiant
//float	scale;// scale = tan((camera->angle * 0,5));
//float	aspect;// aspect = (double)WIDTH / (double)HEIGHT;
int parse_camera(t_rt *rt, char *line, int line_counter)
{
	t_vec world_up;
	// float aspect;//if we gonna make not square window
	int i;

	i = 1;
	if(!skip_spases(line, &i))
		validate_error(line_counter);
	if(!parse_vector(line, &i, &rt->scene.camera.position, 0))
	{
		ft_putendl_fd("Error: Input outside of the range", 2);
		return 0;
	}
	world_up = vec_pos(0,1,0);
	rt->scene.camera.right = vec_cross(rt->scene.camera.position, world_up);
	rt->scene.camera.right = vec_normalize(rt->scene.camera.right);
	rt->scene.camera.up = vec_cross(rt->scene.camera.position, rt->scene.camera.right);
	rt->scene.camera.up = vec_normalize(rt->scene.camera.up);
	// aspect = (double)WIDTH / (double)HEIGHT;
	//keep the screen squere
	rt->scene.camera.angle = ft_atof(line, &i);
	rt->scene.camera.angle = rt->scene.camera.angle * M_PI/ 180.0;

	return (1);
}

int parse_light(t_rt *rt, char *line, int line_counter)
{
	int	i;

	i = 1;
	if(!skip_spases(line, &i))
		validate_error(line_counter);
	if(!parse_vector(line, &i, &rt->scene.light.position, 0))
	{
		ft_putendl_fd("Error: Input outside of the range", 2);
		return 0;
	}
	if(!skip_spases(line, &i))
	{
		validate_error(line_counter);
		return (0);
	}
	rt->scene.light.intensity = ft_atof(line, &i);
	if(!skip_spases(line, &i))
	{
		validate_error(line_counter);
		return (0);
	}
	if(!parse_color(line, &i, &rt->scene.light.color))
	{
		ft_putendl_fd("Error: Color outside of range", 2);
		return (0);
	}
	return (1);
}

int parse_sphere(t_rt *rt, char *line, int line_counter)
{
	double	radius;
	t_color	color;
	int		i;
	
	i = 2;
	if(!skip_spases(line, &i))
		validate_error(line_counter);
	if(!parse_vector(line, &i, &rt->scene.objects.shape.sp.center, 0))
	{
		ft_putendl_fd("Error: Input outside of the range", 2);
		return 0;
	}
	if(!skip_spases(line, &i))
	{
		validate_error(line_counter);
		return (0);
	}
	radius = (ft_atof(line, &i) / 2);
	if(!skip_spases(line, &i))
	{
		validate_error(line_counter);
		return (0);
	}
	if(!parse_color(line, &i, &color))
	{
		ft_putendl_fd("Error: Color outside of range", 2);
		return (0);
	}
	rt->scene.objects.type = OBJ_SPHERE;
	rt->scene.objects.shape.sp.radius = radius;
	return (1);
}

int parse_plane(t_rt *rt, char *line, int line_counter)
{
	int i;

	i = 2;
	if(!skip_spases(line, &i))
	{
		validate_error(line_counter);
		return (0);
	}
	if(!parse_vector(line, &i, &rt->scene.objects.shape.pl.point, 0))
	{
		ft_putendl_fd("Error: Input outside of the range", 2);
		return (0);
	}
	if(!skip_spases(line, &i))
	{
		validate_error(line_counter);
		return (0);
	}
	if(!parse_vector(line, &i, &rt->scene.objects.shape.pl.normal, 1))
	{
		ft_putendl_fd("Error: Input outside of the range", 2);
		return (0);
	}
	rt->scene.objects.shape.pl.normal = vec_normalize(rt->scene.objects.shape.pl.normal);
	if(!skip_spases(line, &i))
	{
		validate_error(line_counter);
		return (0);
	}
	if(!parse_color(line, &i, &rt->scene.objects.shape.pl.mat.albedo))
	{
		ft_putendl_fd("Error: Color outside of range", 2);
		return (0);
	}
	rt->scene.objects.type = OBJ_PLANE;
	return (1);
}

int parse_cylinder(t_rt *rt, char *line, int line_counter)
{
	int	i;

	i = 2;
	if(!skip_spases(line, &i))
	{
		validate_error(line_counter);
		return (0);
	}
	if(!parse_vector(line, &i, &rt->scene.objects.shape.cy.center, 0))
	{
		ft_putendl_fd("Error: Input outside of the range", 2);
		return (0);
	}
	if(!skip_spases(line, &i))
	{
		validate_error(line_counter);
		return (0);
	}
	if(!parse_vector(line, &i, &rt->scene.objects.shape.cy.axis, 1))
	{
		ft_putendl_fd("Error: Input outside of the range", 2);
		return (0);
	}
	rt->scene.objects.shape.cy.axis = vec_normalize(rt->scene.objects.shape.cy.axis);
	if(!skip_spases(line, &i))
	{
		validate_error(line_counter);
		return (0);
	}
	rt->scene.objects.shape.cy.radius = (ft_atof(line, &i) / 2);
	if(!skip_spases(line, &i))
	{
		validate_error(line_counter);
		return (0);
	}
	rt->scene.objects.shape.cy.height = ft_atof(line, &i); 
	if(!skip_spases(line, &i))
	{
		validate_error(line_counter);
		return (0);
	}
	if(!parse_color(line, &i, &rt->scene.objects.shape.cy.mat.albedo))
	{
		ft_putendl_fd("Error: Input outside of the range", 2);
		return (0);
	}
	return (1);
}

int parse_vector(char *line, int *i, t_vec *vec, int normal_range)
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
}

int parse_color(char *line, int *i, t_color *color)
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
}


int check_color(int color)
{
	int result = (color >= 0 && color <= 255);
    printf("  check_color(%d) = %d\n", color, result);
    return (result);
}

int check_vector(double vec)
{
	return (vec >= -1.0 && vec <= 1.0);
}

