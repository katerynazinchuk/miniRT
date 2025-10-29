#include "rt.h"


//function that will read line by line and validate each line by its identifier
//if one line is incorrect the whole valiation processhas been failed
int	parse_file(const char *filename, t_rt *rt)
{
	int fd;
	char *line;

	if (!rt || !filename)
        return (0);
	fd = open(filename, O_RDONLY);
	if(fd < 0)
	{
		perror("open");
		return 0;
	}
	rt->line = 0;
	while(1)
	{
		line = get_next_line(fd);
		if(!line)
			break;
		rt->line++;
		if (line[0] == '\0' || line[0] == '\n' || line[0] == '#')
        {
            free(line);
            continue;
        }
		if (!validate_symb(rt, line, rt->line))
        {
            free(line);
            close(fd);
            return 0;
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

void validate_error(int line_counter)
{
	char *message;

	message = "Error: missing space on line";
	printf("%s %d", message, line_counter);
}

int validate_line(char *line, int i_line)
{
	while(line[i_line] != '\0' && line[i_line] != '\n')
	{
		if(!(ft_isdigit(line[i]) ||
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

int validate_identifier(t_rt *rt, char *line, int line_counter)
{
	int i;
	
	i = 0;
	if(line[i] == '\n' || line[i] == '\0')
		return 1;
	//write a funk that setup i_line identifier based on identifier
	if(!validate_line(line, i_line))
	{
		ft_putendl_fd("Error: Unrecogizable symbol", 2);
		return(0);
	}
	//find place to prove that there is no chars in input exept identifier
	if(line[i] == 'A')
		return(parse_ambient(rt, line, line_counter));
	else if(line[i] == 'C')
		return(parse_camera(rt, line, line_counter));
	else if(line[i] == 'L')
		return(parse_light(rt, line, line_counter));
	else if(line[i] == 's' && line[i + 1] == 'p')
		return(parse_sphere(rt, line, line_counter));
	else if(line[i] == 'p' && line[i + 1] == 'l')
		return(parse_plane(rt, line, line_counter));
	else if(line[i] == 'c' && line[i + 1] == 'y')
		return(parse_cylinder(rt, line, line_counter));
	else
	{
		ft_putendl_fd("Error: Unrecognizable symbol", 2);
		return (0);
	}
}

int skip_spases(char *line, int *i)
{
	int symbol;

	symbol = 0;
	while(line[*i] == ' ' || line[*i] == '\t')
	{
		(*i)++;
		symbol = 1;
	}
	return (symbol);
}


/* float float_check(char *str, int *i)
{
	//identify some value from beggining to the comma, comma is a separator. dont has to be stored
	//we gonna have *pos
} */
