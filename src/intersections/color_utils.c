#include "rt.h"

t_color	color_scale(t_color color, double brightness)
{
	t_color scale_c;

	scale_c.r = color.r * brightness;
	scale_c.g = color.g * brightness;
	scale_c.b = color.b * brightness;
	return (scale_c);
}
