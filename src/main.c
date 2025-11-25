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

//int32_t for width height
//false - resize

#include "rt.h"

static int	build_graphic(t_scene *scene);
static int	draw_img(t_scene *scene, mlx_image_t *img);

int	main(int argc, char **argv)
{
	t_rt		rt;

	//rt = (t_rt *)malloc(sizeof(t_rt*));
	// ft_memset(&rt, 0, sizeof(t_rt));
	if(argc != 2)
	{
		print_error("Wrong number of arguments");
		return (1);
	}
	if (!init_structs(&rt))
	{
		print_error("Can't allocate memory");
		return (1);
	}
	if(!check_file(argv[1]))
	{
		free_arrays(&rt.scene.objects);
		return (1);
	}
	if (!parse_file(argv[1], &rt))
	{
		free_arrays(&rt.scene.objects);
		return (1);
	}
	if (!build_graphic(&rt.scene))
	{
		free_arrays(&rt.scene.objects);
		return (1);
	}
	free_arrays(&rt.scene.objects);
	return (0);
}

static int	build_graphic(t_scene *scene)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = mlx_init(WIDTH, HEIGHT, "MiniRT", false);
	if (!mlx)
	{
		print_error(mlx_strerror(mlx_errno));
		return (0);
	}
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
	{
		mlx_terminate(mlx);
		print_error(mlx_strerror(mlx_errno));
		return (0);
	}
	draw_img(scene, img);
	// mlx_loop_hook(); - need function to handle hooks
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (1);
}

static int draw_img(t_scene *scene, mlx_image_t *img)
{
	t_ray		ray;
	uint32_t	y;
	uint32_t	x;
	uint32_t	color;

	y = 0;
	while (y < (uint32_t)HEIGHT)
	{
		x = 0;
		while (x < (uint32_t)WIDTH)
		{
			ray = create_ray_per_pixel(&scene->camera, x, y);//here we find our field of view
			color = find_color(ray, scene);//here we looking for intersection
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
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

//test main 
// int main (void)
// {
// 	t_vec a = vec_pos(1,2,3);
// 	t_vec b = vec_pos(-2, 0, 5);
// 	t_vec s = vec_add(a,b);
// }

