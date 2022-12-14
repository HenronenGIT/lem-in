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

void	move_all_ants(t_data *data)
{
	long	ants;

	ants = 1;
	while (ants < data->ants)
	{
		ft_printf("L%d-%s ", ants, data->end->room_name);
		ants += 1;
	}
	ft_printf("L%d-%s", ants, data->end->room_name);
	ft_putchar('\n');
	exit(0);
}

t_room	*find_room(t_room *room, char *link_name)
{
	while (room)
	{
		if (!ft_strcmp(room->room_name, link_name))
			return (room);
		room = room->next;
	}
	return (NULL);
}

static void	vec_link_insert(t_room *dst, t_room *src)
{
	size_t	i;

	i = 0;
	if (!dst->links_vec)
	{
		dst->links_vec = (t_vec *)malloc(sizeof(t_vec));
		if (!dst->links_vec)
			error(MALLOC_ERR);
		vec_new_arr(dst->links_vec, 2);
	}
	if (!dst->links_vec->space_left)
		vec_resize(dst->links_vec);
	while (i < dst->links_vec->space_taken)
	{
		if (dst->links_vec->array[i] == src)
			error(LINK_ERR);
		i += 1;
	}
	dst->links_vec->array[dst->links_vec->space_taken] = src;
	dst->links_vec->space_left--;
	dst->links_vec->space_taken++;
}

void	validate_links(t_data *data, char **rooms)
{
	long	first_hash;
	long	second_hash;
	t_room	*room_1;
	t_room	*room_2;

	if (ft_count_pointers(rooms) != 2)
		error(LINK_ERR);
	first_hash = hashing(data, rooms[0]);
	second_hash = hashing(data, rooms[1]);
	room_1 = find_room(data->rooms_vec->array[first_hash], rooms[0]);
	if (!room_1)
		error(FORMAT_ERR);
	room_2 = find_room(data->rooms_vec->array[second_hash], rooms[1]);
	if (!room_2)
		error(FORMAT_ERR);
	if ((room_1 == data->start && room_2 == data->end)
		|| (room_2 == data->start && room_1 == data->end))
		move_all_ants(data);
	if (room_1 == room_2)
		error(FORMAT_ERR);
	vec_link_insert(room_1, room_2);
	vec_link_insert(room_2, room_1);
}

void	read_links(t_data *data, char *line)
{
	char	**rooms;

	rooms = ft_strsplit(line, '-');
	if (!rooms)
		error(MALLOC_ERR);
	validate_links(data, rooms);
	ft_free_2d_array(rooms);
	vec_insert(data->input_vec, line);
	while (get_next_line(0, &line))
	{
		if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
			error(LINK_ERR);
		if (*line != '#')
		{
			rooms = ft_strsplit(line, '-');
			if (!rooms)
				error(MALLOC_ERR);
			validate_links(data, rooms);
			ft_free_2d_array(rooms);
		}
		vec_insert(data->input_vec, line);
	}
}
