#include "rt.h"

void	print_error(const char *msg)
{
	ft_putendl_fd("Error", 2);
	write(2, &msg, ft_strlen(msg));
	write(2, "\n", 1);
}

void	free_arrays(t_objects *obj)
{
	free(obj->spheres);
	free(obj->planes);
	free(obj->cylinders);
}
