/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 15:55:00 by kzinchuk          #+#    #+#             */
/*   Updated: 2026/10/20 15:55:00 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	check_number_format(char *line, int i)
{
	int	int_digits;
	int	frac_digits;

	int_digits = 0;
	frac_digits = 0;
	if (line[i] == '-' || line[i] == '+')
		i++;
	while (ft_isdigit(line[i + int_digits]))
		int_digits++;
	i += int_digits;
	if (line[i] == '.')
	{
		i++;
		while (ft_isdigit(line[i + frac_digits]))
			frac_digits++;
	}
	if (int_digits + frac_digits == 0)
		return (0);
	if (int_digits > MAX_INT_DIGITS)
		return (0);
	return (1);
}

int	parse_double(char *line, int *i, double *num)
{
	if (!check_number_format(line, *i))
	{
		print_error("Invalid number");
		return (0);
	}
	*num = ft_atof(line, i);
	return (1);
}

int	parse_color_value(char *line, int *i, int *color)
{
	int	digits;

	*color = 0;
	digits = 0;
	while (ft_isdigit(line[*i]) && digits < 4)
	{
		*color = *color * 10 + (line[*i] - '0');
		(*i)++;
		digits++;
	}
	if (digits == 0 || line[*i] == '.' || !check_color(*color))
	{
		print_error("Color input outside of the range");
		return (0);
	}
	return (1);
}

int	check_comma(char *line, int *i)
{
	if (line[*i] != ',')
	{
		print_error("Missing comma on line");
		return (0);
	}
	(*i)++;
	return (1);
}

int	check_line_end(char *line, int i)
{
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] != '\0' && line[i] != '\n')
	{
		print_error("Invalid input");
		return (0);
	}
	return (1);
}
