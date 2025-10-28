#include "rt.h"

int parser ()
{
	read_lines();
	validate_symb();
	parse_elements();...
}

//function that will read line by line and validate each line by its identifier
//if one line is incorrect the whole valiation processhas been failed
char **parse_file(const char *filename, t_rt *rt)
{
	int fd;
	char *line;

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
	//this one should return something to parser
	//so next function can catch the logic and prociede with the next step
	//array of lines?????
}
void validate_error(int line_counter)
{
	char *message;

	message = "Incorrect input:missing space on line";
	printf("%s %d", message, line_counter);
}

int validate_symb(t_rt *rt, char *line, int line_counter)
{
	int i;
	
	i = 0;

	if(line[i] == '\n' || line[i] == '\0')
		return 1;
	if(line[i] == 'A')
	{
		if(!skip_spases(line, &i))
			validate_error(line_counter);
		parse_ambient(rt, line);
	}
	else if(line[i] == 'C')
	{
		if(!skip_spases(line, &i))
			validate_error(line_counter);
		parse_camera(rt, line);
	}
	else if(line[i] == 'L')
	{
		if(!skip_spases(line, &i))
			validate_error(line_counter);
		parse_light(rt, line);
	}
	else if(line[i] == 's' && line[i + 1] == 'p')
	{
		if(!skip_spases(line, &i))
			validate_error(line_counter);
		//find place to prove that there is no chars in input exept identifier
		parse_sphere(rt, line);
	}
	else if(line[i] == 'p' && line[i + 1] == 'l')
	{
		if(!skip_spases(line, &i))
			validate_error(line_counter);
		parse_plane(rt, line, line_counter);
	}
	else if(line[i] == 'c' && line[i + 1] == 'y')
	{
		if(!skip_spases(line, &i))
			validate_error(line_counter);
		parse_cylinder(rt, line);
	}
	else
	{
		ft_putendl_fd("Unrecognizable symbol", 2);
		return (0);
	}
	return 1;
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


float float_check(char *str, int *i)
{
	//identify some value from beggining to the comma, comma is a separator. dont has to be stored
	//we gonna have *pos
}

int vec_check()
{
	
}