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
	return 1;
}

int validate_symb(t_rt *rt, char *line, int counter)
{
	int i;
	
	i = 0;

	if(line[i] == '\n' || line[i] == '\0')
		return 0;
	if(line[i] == 'A')
	{
		i++;
		skip_spases(line, &i);
		parse_ambient();
	}
	else if(line[i] == 'C')
	{
		i++;
		skip_spases(line, &i);
		parse_camera();
	}
	else if(line[i] == 'L')
	{
		i++;
	skip_spases(line, &i);
		parse_light();
	}
	else if(line[i] == 's' && line[i + 1] == 'p')
	{
		i++;
		skip_spases(line, &i);
		parse_sphere();
	}
	else if(line[i] == 'p' && line[i + 1] == 'l')
	{
		i++;
		skip_spases(line, &i);
		parse_plane();
	}
	else if(line[i] == 'c' && line[i + 1] == 'y')
	{
		i++;
		skip_spases(line, &i);
		parse_cylinder();
	}
	return 1;

	//can params be in the random order?
	//should we check for that?
	// do we validate first letters of the line first and only then parse?
	//parse && store into struct;
}

void skip_spases(char *line, int *i)
{
	while(line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}