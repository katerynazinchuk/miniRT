/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:47:23 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/12/03 15:47:26 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	build_graphic(t_scene *scene);
static int	draw_img(t_scene *scene, mlx_image_t *img);

int	main(int argc, char **argv)
{
	t_rt		rt;

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
	mlx_key_hook(mlx, handle_esc, mlx);
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
			ray = create_ray_per_pixel(&scene->camera, x, y);
			color = find_color(ray, scene);
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
	return (0);
}

