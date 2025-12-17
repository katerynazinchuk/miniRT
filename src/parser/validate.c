/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:19:46 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/12/15 00:42:59 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	check_file(char *filename)
{
	int	fd;

	if (!check_rt_extension(filename))
	{
		print_error("Wrong file extension");
		return (0);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		print_error("File not found");
		return (0);
	}
	if (close(fd) < 0)
	{
		perror("close");
		return (0);
	}
	return (1);
}

int	check_rt_extension(char *file)
{
	int	len;

	if (!file)
		return (0);
	len = ft_strlen(file);
	if (len < 4)
		return (0);
	if (file[len - 3] == '.' && file[len - 2] == 'r' && file[len - 1] == 't')
		return (1);
	return (0);
}
