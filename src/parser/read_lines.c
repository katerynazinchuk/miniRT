#include "rt.h"


//function that will read line by line and validate each line by its identifier
//if one line is incorrect the whole valiation processhas been failed
int	parse_file(const char *filename, t_rt *rt)
{
	int		fd;
	char	*line;

	if (!rt || !filename)
		return (0);
	fd = open(filename, O_RDONLY);
	if(fd < 0)
	{
		perror("open");
		return (0);
	}
	rt->line_counter = 0;
	while(1)
	{
		line = get_next_line(fd);
		if(!line)
			break;//close (fd) ?
		// rt->line++
		if (line[0] == '\0' || line[0] == '\n' || line[0] == '#')
		{
			free(line);
			continue;
		}
		if (!validate_identifier(rt, line/* , rt->line_counter */))
		{
			free(line);
			close(fd);
			return (0);
		}
		free(line);
	}
	if(close(fd) < 0)
	{
		perror("close");
		return(0);
	}
	return (1);
}

/*
void validate_error(int line_counter)
{
	char *message;

	message = "Error: missing space on line";
	printf("%s %d", message, line_counter);
}
*/

static int	set_i_line(char *line, int *i_line)
{
	int	i;

	i = 0;
	*i_line = 0;
	if(line[i] == 'A' || line[i] == 'C' || line[i] == 'L')
	{
		*i_line = 1;
	}
	if((line[i] == 's' && line[i + 1] == 'p') ||
		(line[i] == 'p' && line[i + 1] == 'l') ||
		(line[i] == 'c' && line[i + 1] == 'y'))
	{
		*i_line = 2;
	}
	return (1);
}

static int validate_line(char *line, int i_line)
{
	while(line[i_line] != '\0' && line[i_line] != '\n')
	{
		if(!(ft_isdigit(line[i_line]) ||
		line[i_line] == ' ' ||
		line[i_line] == ' ' ||
		line[i_line] == ',' ||
		line[i_line] == '.' ||
		line[i_line] == '-' ||
		line[i_line] == '+'))
		{
			ft_putendl_fd("Error: Invalid character in input", 2);
			return (0);
		}
		i_line++;
	}
	return(1);
}

int validate_identifier(t_rt *rt, char *line/* , int line_counter */)
{
	int	i_line;
	int	code;

	//we make this check in upper level
	// if(line[i] == '\n' || line[i] == '\0')
	// 	return (1);
	set_i_line(line, &i_line);
	//write a funk that setup i_line identifier based on identifier
	if(!validate_line(line, i_line))
		return (0);
	if (i_line == 1)
		code = validate_singe_element(rt, line/* , line_counter */);
	else
		code = validate_geometric_objects(&rt->scene.objects, line/* , line_counter */);
	return (code);
}

/* 
	# !!!! this project not about parser, so we will use just last one data we get abot A & C
	# we need to check that we have only one A, C, according to project rules
	# we can do it with flag and check this flag in upper level
	# need to check is it the same with light, because it depends on bonus part
	#
*/
int	validate_singe_element(t_rt *rt, char *line/* , int line_counter */)
{
	int	i;

	i = 0;
	if(line[i] == 'A')
		return(parse_ambient(rt, line/* , line_counter */));
	else if(line[i] == 'C')
		return(parse_camera(rt, line/* , line_counter */));
	else if(line[i] == 'L')
		return(parse_light(rt, line/* , line_counter */));
	return (1);
}

int	validate_geometric_objects(t_objects *obj, char *line/* , int line_counter */)
{
	int	i;

	i = 0;
	if(line[i] == 's' && line[i + 1] == 'p')
		return (process_sphere(obj, line/* , line_counter */));//need to check how I go through levels to free heap
	else if(line[i] == 'p' && line[i + 1] == 'l')
		return(process_plane(obj, line/* , line_counter */));
	else if(line[i] == 'c' && line[i + 1] == 'y')
		return(process_cylinder(obj, line/* , line_counter */));
	return (1);
}
