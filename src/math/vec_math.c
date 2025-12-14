#include "rt.h"

//move a poit by a vector
//usage: pos + offset, normal + something, color1 + color2
t_vec	vec_add(t_vec a, t_vec b)
{
	t_vec	add_p;

	add_p.x = a.x + b.x;
	add_p.y = a.y + b.y;
	add_p.z = a.z + b.z;
	return (add_p);
}

//substitution. build directions vectors (to light or to sphere center)
//usage to_light = light.pos - hit.pint ==> vec_sub(light.pos, hit_point)
//(light_possition, hit_point)
t_vec	vec_sub(t_vec a, t_vec b)
{
	t_vec	sub_p;

	sub_p.x = a.x - b.x;
	sub_p.y = a.y - b.y;
	sub_p.z = a.z - b.z;
	return (sub_p);
}

//scale a direction by distance t,
//scale colors by intensities or material coefficients
//usage P(t) = O + D * t, where D * t is vec_scale; diffuse = color * intencity
t_vec	vec_scale(t_vec v, double s)
{
	t_vec	scale_p;

	scale_p.x = v.x * s;
	scale_p.y = v.y * s;
	scale_p.z = v.z * s;
	return (scale_p);
}

//made the vector oposite direction oriented 
// if normal looks to the wrong direction
//if ray is inside the object
t_vec	vec_neg(t_vec v)
{
	t_vec	negative;

	negative.x = -v.x;
	negative.y = -v.y;
	negative.z = -v.z;
	return (negative);
}
