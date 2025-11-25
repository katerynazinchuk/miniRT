#include "rt.h"
#include <stdio.h>

void	print_plane(t_plane *pl, size_t i);
void	print_sphere(t_sphere *sp, size_t i);
void	print_cylinder(t_cylinder *cy, size_t i);

void	test_parser(t_scene *scene, t_objects *obj)
{
	size_t	i;

	printf("\nAmbient: \n");
	printf("ratio:	%f\n", scene->ambient.ratio);
	printf("color:	x = %i, y = %i z = %i\n", scene->ambient.color.r, scene->ambient.color.g, scene->ambient.color.b);

	printf("\nCamera: \n");
	printf("possition:	x = %f, y = %f z = %f\n", scene->camera.position.x, scene->camera.position.y, scene->camera.position.z);
	printf("direction:	x = %f, y = %f z = %f\n", scene->camera.direction.x, scene->camera.direction.y, scene->camera.direction.z);
	printf("angle in degrees:					%f\n", (scene->camera.angle * 180 / M_PI));

	printf("\nLight: \n");
	printf("possition:	x = %f, y = %f z = %f\n", scene->light.position.x, scene->light.position.y, scene->light.position.z);
	printf("color:			R = %i, G = %i B = %i\n", scene->light.color.r, scene->light.color.g, scene->light.color.b);

	printf("\nObjects: \n");
	i = 0;
	while (obj->sp_count > i)
	{
		print_sphere(&obj->sps[i], i);
		i++;
	}
	i = 0;
	while (obj->pl_count > i)
	{
		print_plane(&obj->pls[i], i);
		i++;
	}
	i = 0;
	while (obj->cy_count > i)
	{
		print_cylinder(&obj->cys[i], i);
		i++;
	}
}

void	print_plane(t_plane *pl, size_t i)
{
	printf("\n%zu index of plane\n", i);
	printf("point:	x = %f, y = %f z = %f\n", pl->point.x, pl->point.y, pl->point.z);
	printf("normal:	x = %f, y = %f z = %f\n", pl->normal.x, pl->normal.y, pl->normal.z);
	printf("color:	x = %i, y = %i z = %i\n", pl->color.r, pl->color.g, pl->color.b);
}
void	print_sphere(t_sphere *sp, size_t i)
{
	printf("\n%zu index of sphere\n", i);
	printf("center:		x = %f, y = %f z = %f\n", sp->center.x, sp->center.y, sp->center.z);
	printf("diametr:	%f\n", sp->radius * 2);
	printf("color:		x = %i, y = %i z = %i\n", sp->color.r, sp->color.g, sp->color.b);
}

void	print_cylinder(t_cylinder *cy, size_t i)
{
	printf("\n%zu index of cylinder\n", i);
	printf("center:		x = %f, y = %f z = %f\n", cy->center.x, cy->center.y, cy->center.z);
	printf("axis:		x = %f, y = %f z = %f\n", cy->axis.x, cy->axis.y, cy->axis.z);
	printf("diametr:	%f\n", cy->radius * 2);
	printf("height:		%f\n", cy->height);
	printf("color:		x = %i, y = %i z = %i\n", cy->color.r, cy->color.g, cy->color.b);
}
