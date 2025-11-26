#include "rt.h"

//from first parser version we have return logic:
// 0 as false
// 1 as success
// add description what is line_counter to make navigation easy
int	process_sphere(t_objects *obj, char *line/* , int line_counter */)
{
	t_sphere	sp_temp;

	if (!parse_sphere(&sp_temp, line/* , line_counter */))
		return (0);
	if (!check_capacity((void**)&obj->sps, &obj->sp_arr_cap, obj->sp_count, sizeof(t_sphere)))
		return (0);
	obj->sps[obj->sp_count] = sp_temp;
	obj->sp_count++;//we need to check growing is neccessary with previous value, so ++ after growing
	return (1);
}

//experiment 
//we need to keep amount of sphere and update memory if capacity is low
	/*
		# can ft_atof return to us negative radius value (?)
		# 
	*/

int	parse_sphere(t_sphere *sphere, char *line/* , int line_counter */)
{
	int		i;
	
	i = 2;
	if (!skip_spases(line, &i))
		return (0);
	if(!parse_vector(line, &i, &sphere->center, 0))
		return 0;
	if(!skip_spases(line, &i))
		return (0);
	sphere->radius = (ft_atof(line, &i) / 2);
	if (sphere->radius <= 0)
		return(0);
	if(!skip_spases(line, &i))
		return (0);
	if(!parse_color(line, &i, &sphere->color))
		return (0);
	sphere->type = OBJ_SPHERE;
	return (1);
}

/* int	parse_sphere(t_rt *rt, char *line, int line_counter)
{
	double	radius;
	t_color	color;
	int		i;
	
	i = 2;
	if(!skip_spases(line, &i))
		validate_error(line_counter);
	if(!parse_vector(line, &i, &rt->scene.objects.shape.sp.center, 0))
	{
		ft_putendl_fd("Error: Input outside of the range", 2);
		return 0;
	}
	if(!skip_spases(line, &i))
	{
		validate_error(line_counter);
		return (0);
	}
	radius = (ft_atof(line, &i) / 2);
	if(!skip_spases(line, &i))
	{
		validate_error(line_counter);
		return (0);
	}
	if(!parse_color(line, &i, &color))
	{
		ft_putendl_fd("Error: Color outside of range", 2);
		return (0);
	}
	rt->scene.objects.type = OBJ_SPHERE;
	rt->scene.objects.shape.sp.radius = radius;
	return (1);
} */