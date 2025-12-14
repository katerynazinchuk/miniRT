#include "rt.h"

static bool	init_sps(t_rt *rt);
static bool	init_cys(t_rt *rt);
static bool	init_pls(t_rt *rt);
static bool	init_lights(t_rt *rt);

bool	init_structs(t_rt *rt)
{
	ft_memset(rt, 0, sizeof(t_rt));
	if (!init_sps(rt))
		return (false);
	if (!init_cys(rt))
		return (false);
	if (!init_pls(rt))
		return (false);
	if (!init_lights(rt))
		return (false);
	rt->scene.render = 64;
	return (true);
}

static bool	init_sps(t_rt *rt)
{
	rt->scene.objects.sps = (t_sphere*)malloc(sizeof(t_sphere) * ARR_SIZE);
	if (!rt->scene.objects.sps)
		return (false);
	rt->scene.objects.sp_arr_cap = ARR_SIZE;
	return (true);
}

static bool	init_cys(t_rt *rt)
{
	rt->scene.objects.cys = (t_cylinder*)malloc(sizeof(t_cylinder) * ARR_SIZE);
	if (!rt->scene.objects.cys)
		return (false);
	rt->scene.objects.cy_arr_cap = ARR_SIZE;
	return (true);
}

static bool	init_pls(t_rt *rt)
{
	rt->scene.objects.pls = (t_plane*)malloc(sizeof(t_plane) * ARR_SIZE);
	if (!rt->scene.objects.pls)
		return (false);
	rt->scene.objects.pl_arr_cap = ARR_SIZE;
	return (true);
}
static bool	init_lights(t_rt *rt)
{
	rt->scene.l_sp.l_arr = (t_light*)malloc(sizeof(t_light) * ARR_SIZE);
	if (!rt->scene.l_sp.l_arr)
		return (false);
	rt->scene.l_sp.l_cap = ARR_SIZE;
	return (true);
}

// bool	init_structs(t_rt *rt)
// {
// 	ft_memset(rt, 0, sizeof(t_rt));
// 	rt->scene.objects.sps = (t_sphere*)malloc(sizeof(t_sphere) * ARR_SIZE);
// 	if (!rt->scene.objects.sps)
// 		return (false);
// 	rt->scene.objects.sp_arr_cap = ARR_SIZE;
// 	rt->scene.objects.cys = (t_cylinder*)malloc(sizeof(t_cylinder) * ARR_SIZE);
// 	if (!rt->scene.objects.cys)
// 	{
// 		free(rt->scene.objects.sps);
// 		return (false);
// 	}
// 	rt->scene.objects.cy_arr_cap = ARR_SIZE;
// 	rt->scene.objects.pls = (t_plane*)malloc(sizeof(t_plane) * ARR_SIZE);
// 	if (!rt->scene.objects.cys)
// 	{
// 		free(rt->scene.objects.sps);
// 		free(rt->scene.objects.cys);
// 		return (false);
// 	}
// 	rt->scene.objects.pl_arr_cap = ARR_SIZE;
// 	rt->scene.l_sp.l_arr = (t_light*)malloc(sizeof(t_light) * ARR_SIZE);
// 	if (!rt->scene.l_sp.l_arr)
// 	{
// 		free(rt->scene.objects.sps);
// 		free(rt->scene.objects.cys);
// 		free(rt->scene.objects.pls);
// 		return (false);
// 	}
// 	rt->scene.l_sp.l_cap = ARR_SIZE;
// 	rt->scene.render = 64;
// 	return (true);
// }