/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kat <kat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 12:00:13 by kzinchuk          #+#    #+#             */
/*   Updated: 2026/10/20 12:13:06 by kat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static double	parse_fraction(const char *str, int *i)
{
	double	fraction;
	double	place;

	fraction = 0.0;
	place = 0.1;
	if (str[*i] == '.')
	{
		(*i)++;
		while (ft_isdigit(str[*i]))
		{
			fraction = fraction + (str[*i] - '0') * place;
			place = place * 0.1;
			(*i)++;
		}
	}
	return (fraction);
}

double	ft_atof(const char *line, int *i)
{
	double	num;
	int		sign;

	sign = 1;
	num = 0.0;
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
	return ((num + parse_fraction(line, i)) * sign);
}
