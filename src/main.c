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

static int	build_graphic(t_scene *scene, t_data_img *data_i);
static void	loop_handler(void *data);
static void	draw_img_dither(t_scene *scene, t_data_img *data_i);

int	main(int argc, char **argv)
{
	t_rt		rt;

	if (argc != 2)
	{
		print_error("Wrong number of arguments");
		return (1);
	}
	if (!init_structs(&rt))
	{
		print_error("Can't allocate memory");
		return (free_arrays(&rt.scene.objects, rt.scene.l_sp.l_arr));
	}
	if (!check_file(argv[1]))
		return (free_arrays(&rt.scene.objects, rt.scene.l_sp.l_arr));
	if (!parse_file(argv[1], &rt))
		return (free_arrays(&rt.scene.objects, rt.scene.l_sp.l_arr));
	if (!build_graphic(&rt.scene, &rt.scene.data_i))
		return (free_arrays(&rt.scene.objects, rt.scene.l_sp.l_arr));
	free_arrays(&rt.scene.objects, rt.scene.l_sp.l_arr);
	return (0);
}

static int	build_graphic(t_scene *scene, t_data_img *data_i)
{
	mlx_t		*mlx;

	mlx = mlx_init(WIDTH, HEIGHT, "MiniRT", false);
	if (!mlx)
	{
		print_error(mlx_strerror(mlx_errno));
		return (0);
	}
	data_i->img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!data_i->img || (mlx_image_to_window(mlx, data_i->img, 0, 0) < 0))
	{
		mlx_terminate(mlx);
		print_error(mlx_strerror(mlx_errno));
		return (0);
	}
	mlx_key_hook(mlx, handle_esc, mlx);
	mlx_loop_hook(mlx, loop_handler, scene);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (1);
}

static void	loop_handler(void *data)
{
	t_scene	*scene;

	scene = data;
	draw_img_dither(scene, &scene->data_i);
}

static void	draw_img_dither(t_scene *scene, t_data_img *data_i)
{
	t_ray		ray;
	static int	map[8][8] = {{0, 32, 8, 40, 2, 34, 10, 42}, {48, 16, 56, 24, 50,
		18, 58, 26}, {12, 44, 4, 36, 14, 46, 6, 38}, {60, 28, 52, 20, 62,
		30, 54, 22}, {3, 35, 11, 43, 1, 33, 9, 41}, {51, 19, 59, 27, 49, 17,
		57, 25}, {15, 47, 7, 39, 13, 45, 5, 37}, {63, 31, 55, 23, 61, 29,
		53, 21}};

	if (scene->render < 0)
		return ;
	while (data_i->y < (uint32_t)HEIGHT)
	{
		if (map[data_i->x % 8][data_i->y % 8] == scene->render)
		{
			ray = create_ray_per_pix(&scene->camera, data_i->x, data_i->y);
			data_i->color = find_color(ray, scene);
			mlx_put_pixel(data_i->img, data_i->x, data_i->y, data_i->color);
		}
		data_i->x++;
		if (data_i->x == (uint32_t)WIDTH)
		{
			data_i->x = 0;
			data_i->y++;
		}
	}
	scene->render--;
}
