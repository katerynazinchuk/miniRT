#include "rt.h"

/* bool	init_structs(t_rt *rt)
{
	ft_memset(&rt, 0, sizeof(t_rt));
	rt->scene->spheres = (t_sphere)malloc(sizeof(t_sphere * 5));
	if (!rt->scene->spheres)
		return (false);
	rt->scene->cylinders = (t_cylinder)malloc(t_cylinder * 5);
	if (!rt->scene->cylinders)
	{
		free(rt->scene->spheres);
		return (false);
	}
	rt->scene->planes = (t_plane)malloc(t_plane * 5);
	if (!rt->scene->cylinders)
	{
		free(rt->scene->spheres);
		free(rt->scene->cylinders);
		return (false);
	}
	return (true);
} */

//realloc with potentional grows
//first alloc for 5 or 1?
//do I need to check is it NULL before I call realloc - no, cause I fisrt time make allocation and then try to add new memory
//how I track does array has sth? if not I shouldnt use it for finding intersection
//mayde set some additional flag true/false do we have sp pl cy or not?
//how to check if I have space before I try to write sth in array?
void	*growing_realloc(void *ptr, size_t old_size)
{
	void	*new_ptr;
	size_t	new_size;

	new_size = old_size * 2;
	// if (new_size == 0)
	// {
	// 	if (ptr)
	// 		free(ptr);
	// 	return (NULL);
	// }
	new_ptr = ft_calloc(1, new_size);
	if (!new_ptr)
	{
		//error? lets do it level up
		if (ptr)
			free(ptr);
		return (NULL);//be carefull and avoid double free
	}
	ft_memcpy(new_ptr, ptr, old_size);
	free(ptr);
	return (new_ptr);
}

bool	init_array(t_objects *objects, t_objtype code)
{
	if (code == OBJ_SPHERE)
	{
		objects->spheres = (t_sphere)malloc(sizeof(t_sphere) * ARR_SIZE);
		if (!objects->spheres)
			return (false);
		objects->sp_count++;
		return (true);
	}
	if (code == OBJ_CYL)
	{
		objects->cylinders = (t_cylinder)malloc(sizeof(t_cylinder) * ARR_SIZE);
		if (!objects->cylinders)
			return (false);
		objects->cy_count++;
		return (true);
	}
	if (code == OBJ_PLANE)
	{
		objects->planes = (t_plane)malloc(sizeof(t_plane) * ARR_SIZE);
		if (!objects->planes)
			return (false);
		objects->pl_count++;
		return (true);
	}
}
