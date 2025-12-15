/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 00:43:51 by tchernia          #+#    #+#             */
/*   Updated: 2025/12/15 00:49:22 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	skip_spases(char *line, int *i)
{
	int	symbol;

	symbol = 0;
	while (line[*i] == ' ' || line[*i] == '\t')
	{
		(*i)++;
		symbol = 1;
	}
	if (!symbol)
		print_error("Missing space on line");
	return (symbol);
}

int	check_color(int color)
{
	int	result;

	result = (color >= 0 && color <= 255);
	return (result);
}

int	check_vector(double vec)
{
	return (vec >= -1.0 && vec <= 1.0);
}

int	check_capacity(void **arr, size_t *capacity, size_t count, size_t type_size)
{
	size_t	new_capacity;
	size_t	new_size;
	void	*new_ptr;

	if (count < *capacity)
		return (1);
	new_capacity = *capacity * 2;
	new_size = new_capacity * type_size;
	new_ptr = NULL;
	new_ptr = growing_realloc(*arr, (*capacity * type_size), new_size);
	if (!new_ptr)
		return (0);
	free(*arr);
	*arr = new_ptr;
	*capacity = new_capacity;
	return (1);
}

bool	check_obj_symbols(char *line, int i)
{
	if ((line[i] == 's' && line[i + 1] == 'p') || \
(line[i] == 'p' && line[i + 1] == 'l') || \
(line[i] == 'c' && line[i + 1] == 'y'))
	{
		return (true);
	}
	return (false);
}
