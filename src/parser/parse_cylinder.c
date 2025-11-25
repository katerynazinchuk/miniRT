#include "rt.h"

int	process_cylinder(t_objects *obj, char *line/* , int line_counter */)
{
	t_cylinder	cy_temp;

	if (!parse_cylinder(&cy_temp, line/* , line_counter */))
		return (0);
	if (!check_capacity((void**)&obj->cys, &obj->cy_arr_cap, obj->cy_count, sizeof(t_cylinder)))
		return (0);
	obj->cys[obj->cy_count] = cy_temp;
	obj->cy_count++;//we need to check growing is neccessary with previous value, so ++ after growing
	return (1);
}

int	parse_cylinder(t_cylinder *cylinder, char *line/* , int line_counter */)
{
	int	i;

	i = 2;
	if (!skip_spases(line, &i))
		return (0);
	if(!parse_vector(line, &i, &cylinder->center, 0))
		return (0);
	if(!skip_spases(line, &i))
		return (0);
	if(!parse_vector(line, &i, &cylinder->axis, 1))
		return (0);
	cylinder->axis = vec_normalize(cylinder->axis);
	if(!skip_spases(line, &i))
		return (0);
	cylinder->radius = (ft_atof(line, &i) / 2);
	if (cylinder->radius <=0)
		return (0);
	if(!skip_spases(line, &i))
		return (0);
	cylinder->height = ft_atof(line, &i); 
	if(!skip_spases(line, &i))
		return (0);
	if(!parse_color(line, &i, &cylinder->color))
		return (0);
	return (1);
}
