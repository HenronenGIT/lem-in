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

void read_ants(t_data *data)
{
	char *line;
	long ant_count;

	line = NULL;
	ant_count = 0;
	get_next_line(0, &line);
	if (!ft_isnumber(line))
		error(INPUT_ERR);
	if (!line)
		error(INPUT_ERR);
	ant_count = ft_atoi(line); //! Change to "atou" - unsigned long.
	if (ant_count <= 0)		   //? Is 0 ant count error?
		error(INPUT_ERR);
	data->ants = ant_count;
	free(line);
}

void read_rooms(t_data *data)
{
	char *line;

	line = NULL;
	while (get_next_line(0, &line) && !ft_strchr(line, '-'))
	{
		if (line && *line == '#')
			read_hashtag(data, line);
		else if ((line && *line == 'L'))
			error(FORMAT_ERR);
		else
			read_room_name(data, line, NORMAL);
		ft_strdel(&line);
	}
	sort_hash_values(data);
	if (ft_strchr(line, '-'))
	{
		read_links(data, line);
		free(line);
	}
	while (get_next_line(0, &line))
	{
		if (*line != '#')
		{
			if (ft_strchr(line, '-'))
				read_links(data, line);
		}
		free(line);
	}
}

bool handle_command(t_data *data, int decider)
{
	char *room_info;

	room_info = NULL;
	get_next_line(0, &room_info);
	if (room_info[0] == '#' || room_info[0] == '\0')
		error(FORMAT_ERR);
	if (decider == START)
		read_room_name(data, room_info, START);
	else
		read_room_name(data, room_info, END);
	return (true);
}

void read_hashtag(t_data *data, char *line)
{
	char *new_line;
	static bool is_start;
	static bool is_end;

	new_line = NULL;
	if (!ft_strcmp("##start", line) && is_start == false)
		is_start = handle_command(data, START);
	else if (!ft_strcmp("##end", line) && is_end == false)
		is_end = handle_command(data, END);
	else if (*line == '#' && line[1] != '#')
		return;
	else
		error(FORMAT_ERR);
	free(new_line);
}

void read_room_name(t_data *data, char *line, int decider)
{
	int i;
	char *name;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	name = ft_strsub(line, 0, i);
	vec_insert(data->rooms_vec, name);
	if (decider == START)
		data->start = data->rooms_vec->array[data->rooms_vec->space_taken - 1];
	if (decider == END)
		data->end = data->rooms_vec->array[data->rooms_vec->space_taken - 1];
}
