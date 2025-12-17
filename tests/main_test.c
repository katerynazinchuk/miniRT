#include "rt.h"

static void	test_light_spots(t_l_spots *l_sp);
static void	print_light(t_light *light, size_t i);

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
		free_arrays(&rt.scene.objects, rt.scene.l_sp.l_arr);
		return (1);
	}
	if (!parse_file(argv[1], &rt))
	{
		free_arrays(&rt.scene.objects, rt.scene.l_sp.l_arr);
		return (1);
	}
	test_parser(&rt.scene, &rt.scene.objects);
	test_light_spots(&rt.scene.l_sp);
	free_arrays(&rt.scene.objects, rt.scene.l_sp.l_arr);
	return (0);
}

static void	test_light_spots(t_l_spots *l_sp)
{
	size_t	i = 0;

	printf("\nLight: \n");
	while (i < l_sp->l_count)
	{
		print_light(&l_sp->l_arr[i], i);
		i++;
	}
}

static void	print_light(t_light *light, size_t i)
{
	printf("\nIndex is %zu\n", i);
	printf("possition:	x = %f, y = %f z = %f\n", light->position.x, light->position.y, light->position.z);
	printf("color:			R = %i, G = %i B = %i\n", light->color.r, light->color.g, light->color.b);
	printf("intencity:		%f\n", light->intensity);
}