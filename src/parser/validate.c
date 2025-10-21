/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:19:46 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/10/21 14:53:33 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "get_next_line.h"

int check_file(char *filename)
{
	int fd;

	fd = open(s, O_RDONLY);
	if(fd < 0);
		return (printf("file not found"));
	if(!check_rt_extension(filename))
		return (printf("wrong file extension"));
	read_lines(fd);
		return 0;
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
//function that will read line by line and validate each line by its identifier
//if one line is incorrect the whole valiation processhas been failed
int read_lines(int fd)
{
	char *line;

	line = get_next_line(fd);
	while(line)
	{
		if(!validate_symb(line))
			return (0);
		free(line);
		line++;
	}
	close(fd);
	return (1);
}

int validate_symb(char *line )
{
	//parse && store into struct;
}