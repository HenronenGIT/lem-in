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
			read_hashtag(data, line);
		else if (line && *line == 'L')
			error(FORMAT_ERR);
		else
			read_room_name(data, line, NORMAL);
		free(line);
	}
}

// void	read_room_name(t_data *data, char *line)
void	read_room_name(t_data *data, char *line, int decider)
{
	int		i;
	char	*name;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	name = ft_strsub(line, 0, i);
	vec_insert(&(data->rooms_vec), name);



	if (decider == START)
		data->start = name;
	if (decider == END)
		data->end = name;
}

int	read_hashtag(t_data *data, char *line)
{
	char *test;

	// if (!ft_strncmp("##", line, 2)) //? Can segfault in some cases
		// read_command(data, line);
	test = NULL;
	if (!ft_strcmp("##start", line))
	{
		get_next_line(0, &test);
		read_room_name(data, test, START);
	}

	else if (!ft_strcmp("##end", line))
	{
		get_next_line(0, &test);
		read_room_name(data, test, END);
	}
	else
		return (1);
}

