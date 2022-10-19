/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:45:31 by hmaronen          #+#    #+#             */
/*   Updated: 2022/09/05 16:45:32 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static t_coords	*read_coordinates(char *coord_x, char *coord_y)
{
	t_coords	*coords;

	coords = NULL;
	if (ft_isnumber(coord_x) == false || ft_isnumber(coord_y) == false)
		error(COORD_ERR);
	coords = (t_coords *)malloc(sizeof(t_coords));
	if (!coords)
		error(MALLOC_ERR);
	(coords)->x = ft_atol(coord_x);
	(coords)->y = ft_atol(coord_y);
	return (coords);
}

static void	read_room_info(t_data *data, char *line)
{
	char		**info;
	t_coords	*coords;
	t_room		*room;

	room = NULL;
	coords = NULL;
	info = ft_strsplit(line, ' ');
	if (!info)
		error(MALLOC_ERR);
	if (ft_count_pointers(info) != 3)
		error(FORMAT_ERR);
	coords = read_coordinates(info[1], info[2]);
	room = allocate_new_room(info[0], coords);
	vec_insert(data->rooms_vec, room);
	vec_insert(data->input_vec, line);
	free(info[1]);
	free(info[2]);
	free(info);
}

static void	handle_hashtag(t_data *data, char *line)
{
	char	*room_info;

	room_info = NULL;
	vec_insert(data->input_vec, line);
	if (*line == '#' && line[1] != '#')
		return ;
	get_next_line(0, &room_info);
	if (room_info[0] == '#' || room_info[0] == '\0')
		error(FORMAT_ERR);
	read_room_info(data, room_info);
	if (!ft_strcmp("##start", line) && data->start == NULL)
		data->start = data->rooms_vec->array[data->rooms_vec->space_taken - 1];
	else if (!ft_strcmp("##end", line) && data->end == NULL)
		data->end = data->rooms_vec->array[data->rooms_vec->space_taken - 1];
	else if (line[0] == '#' && line[1] == '#')
		return ;
	else
		error(FORMAT_ERR);
}

void	read_rooms(t_data *data)
{
	char	*line;

	line = NULL;
	while (get_next_line(0, &line))
	{
		if (line && *line == 'L')
			error(FORMAT_ERR);
		if (line && *line == '#')
			handle_hashtag(data, line);
		else if (!ft_strchr(line, ' '))
			break ;
		else
			read_room_info(data, line);
	}
	sort_hash_values(data);
	read_links(data, line);
}

/*
	Read amount of ants and add that value to data->ants.
	Add readed value also in data->input_vec.
	If invalid input, call error() function.
*/
void	read_ants(t_data *data)
{
	char	*line;
	long	ant_count;

	line = NULL;
	ant_count = 0;
	get_next_line(0, &line);
	if (line && (line[0] == '-' || line[0] == '0'))
		error(ANT_ERR);
	if (!ft_isnumber(line))
		error(ANT_ERR);
	if (!line)
		error(ANT_ERR);
	ant_count = ft_atol(line);
	if (ant_count <= 0)
		error(ANT_ERR);
	data->ants = ant_count;
	vec_insert(data->input_vec, line);
}
