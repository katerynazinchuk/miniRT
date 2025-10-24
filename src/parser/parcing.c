#include <fcntl.h>
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

int parse_ambient(t_rt *rt, char *line)
{
	//line *on the current nessesary symbol
	//i need to read it and store tor the structure
	//skip spases
	//get new symbol ==> so new chaunk of information 
	//store it to the same struct 

	//then return soe error if that stuct fail?
	//or if malloc fail somewher in the middle?

	



}

int parse_camera(t_rt *rt, char *line)
{

}

int parse_light(t_rt *rt, char *line)
{

}

int parse_sphere(t_rt *rt, char *line)
{

}
//three inputs:first - coordinates of point on a plane
//second - normalised vector
//colors
int parse_plane(t_rt *rt, char *line, int line_counter)
{
	t_vec *point;
	t_vec *normal;
	t_color *color;
	int i;

	line[i] =+ 2;
	skip_spases(&line, &i);
	rt->scene.objects.type = OBJ_PLANE;
	//scan for correct vector value
	point = parse_vector(rt, line);
	if(!skip_spases(line, line_counter))
		validate_error(line_counter);
	normal = parse_vector(rt, line);
	if(!skip_spases(line, line_counter))
		validate_error(line_counter);
		//check for the length and normalization
	color = validate_color(rt, line);
	//combine clor into one chanel??
	return (1);
}
// also three values
int parse_cylinder(t_rt *rt, char *line)
{
	

}

int parse_vector(char *line, t_vec **vec)
{
	char *endp;
	

	*vec->x = ft_atol(&line, &endp);
	vec->y = ft_atol(&line, &endp);
	vec->z = ft_atol(&line, &endp);
	return (vec);
}

t_color *parse_color(t_color *color, char * line)
{



}



//point->z = (float)ft_atoi(value);
