/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 12:00:13 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/10/29 18:15:26 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
// with return value of tstr position;
/* static const char *skip_white_space(const char *str)
{
	while (*str == ' ' || *str == '\f' \
|| *str == '\n' || *str == '\r' \
|| *str == '\t' || *str == '\v')
	{
		str++;
	}
	return(str);
} */

static double parse_fraction(const char **str, int *divisor, int *i)
{
	double	fraction;

	fraction = 0.0;
	*divisor = 1;
	if(*str[*i] == '.')
	{
		(*i)++;
		while (ft_isdigit(*str[*i]))
		{
			fraction = fraction * 10.0 + (*str[*i] - '0');
			*divisor *= 10;
			(*i)++;
		}
	}
	return (fraction);
}

double ft_atof(const char *line, int *i)
{
	double	num;
	int	sign;
	int divisor;
	double fraction;

	sign = 1;
	num = 0.0;
	divisor = 1;
	// nptr = skip_white_space(nptr);
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
	fraction = parse_fraction(&line, &divisor, i);
	// if(endp != NULL)
	// 	*endp = (char *)nptr;
	return ((num + fraction/divisor) * sign);
}

/* double ft_atof(const char *nptr, char **endp)
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
} */