/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:25:57 by igaplich          #+#    #+#             */
/*   Updated: 2022/09/06 11:25:59 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

size_t	room_compare(t_data *data, char **line)
{

	// char	*compare;
	// size_t	len;
	// size_t	i;

	// i = 0;
	// compare = NULL;
	// while (i < data->rooms_vec->space_taken)
	// {
	// 	len = ft_strlen(data->rooms_vec->rooms[i]->room_name);
	// 	if (!ft_strncmp(*line, data->rooms_vec->rooms[i]->room_name, len))
	// 		break;
	// 	i++;
	// }
	// if (i == data->rooms_vec->space_taken)
	// 	error(FORMAT_ERR);
	// *line += len;
	// return (i);
}

void	insert_link(t_data *data, size_t first_link, size_t second_link)
{
	// data->rooms_vec->rooms[first_link]->next = (t_room *)malloc(sizeof(t_room));
	// if (!data->rooms_vec->rooms[first_link]->next)
		// error(MALLOC_ERR);
	// data->rooms_vec->rooms[first_link]->next->head = data->rooms_vec->rooms[first_link]->head;
	// data->rooms_vec->rooms[first_link] = data->rooms_vec->rooms[first_link]->next;
	// data->rooms_vec->rooms[first_link]->next = NULL;
	// data->rooms_vec->rooms[first_link]->room_name = data->rooms_vec->rooms[second_link]->head->room_name;
}

t_room		*find_room(t_room *room, char *link_name)
{
	while (room)
	{
		if (!ft_strcmp(room->room_name, link_name))
			return (room);
		room = room->next;
	}
	return (NULL);
}

void	read_links(t_data *data, char *line)
{
	char			**rooms;
	unsigned long	first_hash;
	unsigned long	second_hash;
	t_room			*room_1;
	t_room			*room_2;

	rooms = NULL;
	first_hash = 0;
	rooms = ft_strsplit(line, '-'); //! temp
	first_hash = hashing(data, rooms[0]);
	second_hash = hashing(data, rooms[1]);
	room_1 = find_room(data->rooms_vec->rooms[first_hash], rooms[0]);
	if (!room_1)
		error(FORMAT_ERR);
	room_2 = find_room(data->rooms_vec->rooms[second_hash], rooms[1]);
	if (!room_2)
		error(FORMAT_ERR);
	vec_link_insert(room_1, room_2);
	free(rooms[0]);
	free(rooms[1]);
	free(rooms);

	// find_room(data->rooms_vec->rooms[second_hash]);
}
