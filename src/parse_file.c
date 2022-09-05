/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:45:31 by hmaronen          #+#    #+#             */
/*   Updated: 2022/09/05 16:45:32 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	read_ants(t_data *data)
{
	char	*line;
	long	ant_count;

	line = NULL;
	ant_count = 0;
	get_next_line(0, &line);
	if (!ft_isnumber(line))
		error(1);
	if (!line)
		error(1);
	ant_count = ft_atoi(line); //! Change to "atou" - unsigned long.
	if (ant_count <= 0) //? Is 0 ant count error?
		error(1);
	data->ants = ant_count;
	free(line);
}

void	read_rooms(t_data *data)
{
	char	*line;

	while (get_next_line(0, &line))
	{
		if (line && *line == '#')
			read_comment(data, line);
		else if (line && *line == 'L')
			error(FORMAT_ERR);
		else
			read_room_name(data, line);
			// read_room_name(data, line, NORMAL);
		free(line);
	}
}

// void	read_room_name(t_data *data, char *line, int decider)
void	read_room_name(t_data *data, char *line)
{
	int		i;
	char	*name;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	name = ft_strsub(line, 0, i);
	vec_insert(&(data->rooms), name);



// 	if (decider == START)
// 		data->start = name;
// 	if (decider == END)
// 		data->end = name;
}

int	read_comment(t_data *data, char *line)
{
	if (!ft_strncmp("##", line, 2)) //? Can segfault in some cases
		read_command(data, line);
// 
	// if (!ft_strcmp("##start", line))
		// read_start(data, line);
	// else if (!ft_strcmp("##end", line))
		// read_end(data, line);
	else
		return (1);
}

void	read_command(t_data *data, char *line)
{
	if (!ft_strcmp("##start", line))
		read_start(data, line);
	else if (!ft_strcmp("##end", line))
		read_end(data, line);
	else
		return ;
}

//? read_start() and read_end() function can bee merged to one function "read_start_end"
void	read_start(t_data *data, char *line)
{
	free(line);
	get_next_line(0, &line);
	free(line);
	read_room_name(data, line);
	// read_room_name(data, line, START);
}

void	read_end(t_data *data, char *line)
{
	printf("line in read_end() = %s\n", line);
	free(line);
	get_next_line(0, &line);
	free(line);
	read_room_name(data, line);
	// read_room_name(data, line, END);
}
