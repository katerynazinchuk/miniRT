#include "rt.h"

/* static void	increase_nums(int *obj_count, int *capacity); */

//if I allocate before parsing, I set capacity
//maybe I can make better syntax using void type to make allocation in one function (?)
bool	init_structs(t_rt *rt)
{
	ft_memset(rt, 0, sizeof(t_rt));
	// rt->scene.objects
	rt->scene.objects.sps = (t_sphere*)malloc(sizeof(t_sphere) * ARR_SIZE);
	if (!rt->scene.objects.sps)
		return (false);
	rt->scene.objects.sp_arr_cap = ARR_SIZE;
	rt->scene.objects.cys = (t_cylinder*)malloc(sizeof(t_cylinder) * ARR_SIZE);
	if (!rt->scene.objects.cys)
	{
		free(rt->scene.objects.sps);
		return (false);
	}
	rt->scene.objects.cy_arr_cap = ARR_SIZE;
	rt->scene.objects.pls = (t_plane*)malloc(sizeof(t_plane) * ARR_SIZE);
	if (!rt->scene.objects.cys)
	{
		free(rt->scene.objects.sps);
		free(rt->scene.objects.cys);
		return (false);
	}
	rt->scene.objects.pl_arr_cap = ARR_SIZE;
	return (true);
}

//realloc with potentional grows
//first alloc for 5 or 1?
//do I need to check is it NULL before I call realloc - no, cause I fisrt time make allocation and then try to add new memory
//how I track does array has sth? if not I shouldnt use it for finding intersection
//mayde set some additional flag true/false do we have sp pl cy or not?
//how to check if I have space before I try to write sth in array?
/* void	*growing_realloc(void *old_ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	// size_t	new_size;

	// new_size = old_size * 2;
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
		// if (ptr)
		// 	free(ptr);
		return (NULL);//be carefull and avoid double free
	}
	ft_memcpy(new_ptr, old_ptr, old_size);
	// free(ptr);
	return (new_ptr);
} */

void	*growing_realloc(void *old_ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	new_ptr = ft_calloc(1, new_size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, old_ptr, old_size);
	return (new_ptr);
}


/* //Do I need ARR_SIZE+1 for NULL element?
//this function needed if I allocate inside parser
bool	init_array(t_objects *objects, t_objtype code)
{
	if (code == OBJ_SPHERE)
	{
		objects->spheres = (t_sphere)malloc(sizeof(t_sphere) * ARR_SIZE);
		if (!objects->spheres)
			return (false);
		objects->sp_arr_cap = ARR_SIZE;
		// increase_nums(objects->sp_count, objects->sp_arr_cap);
		return (true);
	}
	if (code == OBJ_CYL)
	{
		objects->cylinders = (t_cylinder)malloc(sizeof(t_cylinder) * ARR_SIZE);
		if (!objects->cylinders)
			return (false);
		objects->cy_arr_cap = ARR_SIZE;
		// increase_nums(objects->cy_count, objects->cy_arr_cap);
		return (true);
	}
	if (code == OBJ_PLANE)
	{
		objects->planes = (t_plane)malloc(sizeof(t_plane) * ARR_SIZE);
		if (!objects->planes)
			return (false);
		objects->pl_arr_cap = ARR_SIZE;
		// increase_nums(objects->pl_count, objects->pl_arr_cap);
		return (true);
	}
} */

/* static void	increase_nums(int *obj_count, int *capacity)
{
	(*obj_count)++;
	(*capacity) = ARR_SIZE;
} */
