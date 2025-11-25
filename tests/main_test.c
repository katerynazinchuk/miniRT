#include "rt.h"


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
	test_parser(&rt.scene, &rt.scene.objects);
	free_arrays(&rt.scene.objects);
	return (0);
}