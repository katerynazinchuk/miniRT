/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:19:46 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/11/04 16:52:43 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int check_file(char *filename)
{
	int fd;

	if(!check_rt_extension(filename))
	{
		print_error("Wrong file extension");
		// ft_putendl_fd("Wrong file extension", 2);
		return (0);
	}
	fd = open(filename, O_RDONLY);
	if(fd < 0)
	{
		ft_putendl_fd("File not found", 2);//perror("open")
		return (0);
	}
	if(close(fd) < 0)
	{
		perror("close");
		return 0;
	}
	return 1;
}

int check_rt_extension(char *filename)
{
	int	len;

	if(!filename)
		return (0);//or error
	len = ft_strlen(filename);
	if(len < 4)
		return (0);
	if(filename[len - 3] == '.' && filename[len - 2] == 'r' && filename[len - 1] == 't')
		return (1);
	return 0;
}
