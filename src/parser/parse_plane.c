#include "rt.h"

int	process_plane(t_objects *obj, char *line/* , int line_counter */)
{
	t_plane	pl_temp;

	if (!parse_plane(&pl_temp, line/* , line_counter */))
		return (0);
	if (!check_capacity((void**)&obj->planes, &obj->pl_arr_cap, obj->pl_count, sizeof(t_plane)))
		return (0);
	obj->planes[obj->pl_count] = pl_temp;
	obj->pl_count++;//we need to check growing is neccessary with previous value, so ++ after growing
	return (1);
}

int	parse_plane(t_plane *plane, char *line/* , int line_counter */)
{
	int i;

	i = 2;
	if (!skip_spases(line, &i))
		return (0);
	if(!parse_vector(line, &i, &plane->point, 0))
		return (0);
	if(!skip_spases(line, &i))
		return (0);
	if(!parse_vector(line, &i, &plane->normal, 1))
		return (0);
	plane->normal = vec_normalize(plane->normal);
	if(!skip_spases(line, &i))
		return (0);
	if(!parse_color(line, &i, &plane->color))
		return (0);
	// rt->scene.objects.type = OBJ_PLANE;
	return (1);
}
