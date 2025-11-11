#include "rt.h"

bool	init_structs(t_rt *rt)
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
}

//realloc with potentional grows
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
