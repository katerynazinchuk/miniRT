/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 12:00:13 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/12/19 15:21:38 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static double	parse_fraction(const char *str, int *divisor, int *i)
{
	double	fraction;

	fraction = 0.0;
	*divisor = 1;
	if (str[*i] == '.')
	{
		(*i)++;
		while (ft_isdigit(str[*i]))
		{
			fraction = fraction * 10.0 + (str[*i] - '0');
			*divisor *= 10;
			(*i)++;
		}
	}
	return (fraction);
}

double	ft_atof(const char *line, int *i)
{
	double	num;
	int		sign;
	int		divisor;
	double	fraction;

	sign = 1;
	num = 0.0;
	divisor = 1;
	if (line[*i] == '-' || line[*i] == '+')
	{
		if (line[*i] == '-')
			sign = -sign;
		(*i)++;
	}
	while (ft_isdigit(line[*i]))
	{
		num = num * 10.0 + (line[*i] - '0');
		(*i)++;
	}
	fraction = parse_fraction(line, &divisor, i);
	return ((num + fraction / divisor) * sign);
}
