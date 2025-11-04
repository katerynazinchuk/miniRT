#include "rt.h"

void	print_error(const char *msg)
{
	ft_putendl_fd("Error", 2);
	write(2, &msg, ft_strlen(msg));
	write(2, "\n", 1);
}