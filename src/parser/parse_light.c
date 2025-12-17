#include "rt.h"

static int	parse_light(t_light *light, char *line);

int	process_light(t_l_spots *l_sp, char *line)
{
	t_light	l_temp;
	size_t	siz;

	if (!parse_light(&l_temp, line))
		return (0);
	siz = sizeof(t_light);
	if (!check_capacity((void**)&l_sp->l_arr, &l_sp->l_cap, l_sp->l_count, siz))
		return (0);
	l_sp->l_arr[l_sp->l_count] = l_temp;
	l_sp->l_count++;//we need to check growing is neccessary with previous value, so ++ after growing
	return (1);
}

static int	parse_light(t_light *light, char *line)
{
	int	i;

	i = 1;
	if (!skip_spases(line, &i))
		return (0);
	if(!parse_vector(line, &i, &light->position, 0))
		return 0;
	if(!skip_spases(line, &i))
		return (0);
	light->intensity = ft_atof(line, &i);
	if(!skip_spases(line, &i))
		return (0);
	if(!parse_color(line, &i, &light->color))
		return (0);
	return (1);
}
