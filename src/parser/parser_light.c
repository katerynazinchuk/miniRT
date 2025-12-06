#include "rt.h"

int	process_light(t_l_spots *multi_l, char *line)
{
	t_light	l_temp;
	size_t	size;

	if (!parse_light(&l_temp, line))
		return (0);
	size = sizeof(t_light);
	if (!check_capacity((void**)&multi_l->multi_spot, &multi_l->l_cap, multi_l->l_count, size))
		return (0);
	multi_l->multi_spot[multi_l->l_count] = l_temp;
	multi_l->l_count++;//we need to check growing is neccessary with previous value, so ++ after growing
	return (1);
}


int	parse_light(t_l_spots *multi_l, char *line)
{
	int	i;

	i = 1;
	if (!skip_spases(line, &i))
		return (0);
	if(!parse_vector(line, &i, &rt->scene.light.position, 0))
		return 0;
	if(!skip_spases(line, &i))
		return (0);
	rt->scene.light.intensity = ft_atof(line, &i);
	if(!skip_spases(line, &i))
		return (0);
	if(!parse_color(line, &i, &rt->scene.light.color))
		return (0);
	return (1);
}
