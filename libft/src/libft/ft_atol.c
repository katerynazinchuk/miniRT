/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 12:00:13 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/10/24 12:16:01 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

double atol(const char * nptr, char **endp)
{
	double	num;
	int	sign;
	double fraction;

	fraction = 0.0;
	sign = 1;
	num = 0.0;
	while (*nptr == ' ' || *nptr == '\f' \
|| *nptr == '\n' || *nptr == '\r' \
|| *nptr == '\t' || *nptr == '\v')
	{
		nptr++;
	}
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -sign;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		num = num * 10.0 + (*nptr - '0');
		nptr++;
	}
	if(*nptr == '.')
	{
		*nptr++;
		while (*nptr >= '0' && *nptr <= '9')
		{
			fraction = fraction * 10.0 + (*nptr - '0');
			nptr++;
		}
	}
	if(endp != NULL)
		*endp = *nptr;
	return ((num + fraction) * sign);
}

// with return value of tstr position;