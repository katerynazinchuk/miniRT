/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 12:00:13 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/10/24 15:25:39 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
// with return value of tstr position;
static const char *skip_white_space(const char *str)
{
	while (*str == ' ' || *str == '\f' \
|| *str == '\n' || *str == '\r' \
|| *str == '\t' || *str == '\v')
	{
		str++;
	}
	return(str);
}

static double parse_fraction(const char **str, int *divisor)
{
	double	fraction;

	fraction = 0.0;
	*divisor = 1;
	if(**str == '.')
	{
		(*str)++;
		while (ft_isdigit(**str))
		{
			fraction = fraction * 10.0 + (**str - '0');
			*divisor *= 10;
			(*str)++;
		}
	}
	return (fraction);
}

double atof(const char * nptr, char **endp)
{
	double	num;
	int	sign;
	int divisor;
	double fraction;

	sign = 1;
	num = 0.0;
	divisor = 1;
	nptr = skip_white_space(nptr);
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -sign;
		nptr++;
	}
	while (ft_isdigit(*nptr))
	{
		num = num * 10.0 + (*nptr - '0');
		nptr++;
	}
	fraction = parse_fraction(&nptr, &divisor);
	if(endp != NULL)
		*endp = (char *)nptr;
	return ((num + fraction/divisor) * sign);
}