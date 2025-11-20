#include "rt.h"



/*
	# Be carefull - now skip spaces show error msg
	# Need to check all parser part with this function
*/
//I dont need force print
int	skip_spases(char *line, int *i)
{
	int	symbol;

	symbol = 0;
	while (line[*i] == ' ' || line[*i] == '\t')
	{
		(*i)++;
		symbol = 1;
	}
	if (!symbol)
		print_error("Missing space on line");
	return (symbol);
}

int	check_color(int color)
{
	int result;
	
	result = (color >= 0 && color <= 255);
	// printf("  check_color(%d) = %d\n", color, result);
	return (result);
}

int	check_vector(double vec)
{
	return (vec >= -1.0 && vec <= 1.0);
}

//keep project return logic
// 1 - success
// 0 - false

//need to return rewrite array if nesseccary
int	check_capacity(void **array, size_t *capacity, size_t count, size_t type_size)
{
	size_t	new_capacity;
	size_t	new_size;
	void	*new_ptr;

	if (count < *capacity)
		return (1);//this is success, cause we dont need to reallocate
	new_capacity = *capacity * 2;
	new_size = new_capacity * type_size;
	new_ptr = NULL;
	new_ptr = growing_realloc(*array, (*capacity * type_size), new_size);
	if (!new_ptr)
		return (0);//check allocation free
	free(*array);
	*array = new_ptr;
	*capacity = new_capacity;
	return (1);
}
