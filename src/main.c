// when light hits the spot ofr can be connected with the sourse of light only then we use property - colour
// so on the beggining we create an object with all nessesary properties and only that, give permision to use some
//closer the light - brighter the color. and oposite
/*for each pixel,
	color c;
	for each shape in the scene
		send a ray through each pixel and see if it collides with a shape
		if it does
			color = calculate color of ray
		else, color = background color
	return color

To calculate color of ray...
	color c = 0,0,0 // rgb
	for each light source in the scene
		make a new ray (shad_ray) that starts at where the original ray hit the shape...
		... and ends at the light source
		see if the shadow ray hits a shape on its way to the light
		if it does, 
			calculate ambient color using ambient color of shape material and...
			... ambient light intensity 
		if not,
			calculate shading with sum of ambient/diffuse/specular components 
*/

//cast many rays per pixel and combine all colors into one, to gt smoother blending of colors = super-sampling
//can impement it with thread multitasking
#include "rt.h"

int main(int argc, char **argv)
{

	t_rt	rt;
	// mlx_t	*mlx;

	//rt = (t_rt *)malloc(sizeof(t_rt*));
	ft_memset(&rt, 0, sizeof(t_rt));
	if(argc != 2)
	{
		ft_putendl_fd("Error: Wrong number of arguments", 2);
		return 1;
	}
	if(check_file(argv[1]))
	{
		parse_file(argv[1], &rt);
		//create camera basis
		//render
		//mlx_loop();// loop window to prewent closing
	}
	//free everything;

//int32_t for width height
//false - resize
/* 	mlx = mlx_init(WIDTH, HEIGHT, "MiniRT", false);
	if (!mlx)
	{
		//show error; mlx_strerror(mlx_errno);
		//destroy from rt;
		return (1);
	} */

	return (0);
}



/*
int main(int argc, char **argv)
{

	t_rt *rt;

	rt = (t_rt *)malloc(sizeof(t_rt*));
	if(argc != 2)
	{
		ft_putendl_fd("Error: Wrong number of arguments", 2);
		return 1;
	}
	if (check_file(argv[1]))
	{
		parse_file(argv[1], rt);
		//create camera basis
		//render
		//mlx_loop();// loop window to prewent closing
	}
	//free everything;
	return (0);
	
}*/

// Add this drawing part in mlx_loop, so we could start our tests,
// after finishing parser and create_ray =))
/* t_ray	ray;
	int		y;
	int		x;

//int32_t for x & y

	y = 0;
	while (y < HEIGTH)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = create_ray_per_pixel(camera, x, y);//here we find our field of view
			color = find_color(ray, scene);//here we looking for intersection
			put_pixel(x, y, color);
			x++;
		}
		y++;
} */

//test main 
// int main (void)
// {
// 	t_vec a = vec_pos(1,2,3);
// 	t_vec b = vec_pos(-2, 0, 5);
// 	t_vec s = vec_add(a,b);
// }

