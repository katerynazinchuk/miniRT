/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 23:24:57 by tchernia          #+#    #+#             */
/*   Updated: 2025/12/18 18:11:10 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	process_line(t_rt *rt, int fd);

int	parse_file(const char *filename, t_rt *rt)
{
	int		fd;

	if (!rt || !filename)
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (0);
	}
	if (process_line(rt, fd))
	{
		close(fd);
		return (0);
	}
	if (close(fd) < 0)
	{
		perror("close");
		return (0);
	}
	return (1);
}

static int	process_line(t_rt *rt, int fd)
{
	char	*line;
	int		status;

	status = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (status == 0 || line[0] == '\0' || line[0] == '\n' || line[0] == '#')
		{
			free(line);
			continue ;
		}
		if (!validate_identifier(rt, line))
		{
			free(line);
			status = 0;
			rt->exit_code = 1;
			continue ;
		}
		free(line);
	}
	return (status);
}
