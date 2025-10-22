/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:19:46 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/10/22 13:53:56 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int check_file(char *filename)
{
	int fd;

	if(!check_rt_extension(filename))
	{
		ft_putendl_fd("Wrong file extension", 2);
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
