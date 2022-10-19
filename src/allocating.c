/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocating.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:33:58 by hmaronen          #+#    #+#             */
/*   Updated: 2022/10/12 11:34:00 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_room	*allocate_new_room(char *room_name, t_coords *coords)
{
	t_room	*new_room;

	new_room = NULL;
	new_room = (t_room *)malloc(sizeof(t_room));
	if (!new_room)
		error(MALLOC_ERR);
	new_room->room_name = room_name;
	new_room->coords = coords;
	new_room->links_vec = NULL;
	new_room->parent = NULL;
	new_room->flow_parent = NULL;
	new_room->flow = NULL;
	new_room->flow_from = false;
	new_room->next = NULL;
	new_room->occupied = false;
	return (new_room);
}

void	allocate_other_flows(t_room *room_ptr)
{
	room_ptr->flow = (t_room **)malloc(sizeof(t_room *) * 2);
	if (!room_ptr->flow)
		error(MALLOC_ERR);
	room_ptr->flow[0] = NULL;
	room_ptr->flow[1] = NULL;
}

void	allocate_start_flows(t_data *data, t_room *room_ptr)
{
	size_t	end_links;
	size_t	i;

	i = 0;
	if (data->end->links_vec == NULL)
		error(NO_LINK_TO_END);
	end_links = data->end->links_vec->space_taken;
	room_ptr->flow = (t_room **)malloc(sizeof(t_room *) * (end_links + 1));
	if (!room_ptr->flow)
		error(MALLOC_ERR);
	while (i <= end_links)
		room_ptr->flow[i++] = NULL;
}

void	allocate_flow_pointers(t_data *data)
{
	size_t	i;
	t_room	*room_ptr;

	i = 0;
	while (i < data->rooms_vec->length)
	{
		if (data->rooms_vec->array[i])
		{
			room_ptr = data->rooms_vec->array[i];
			while (room_ptr)
			{
				if (room_ptr == data->start)
					allocate_start_flows(data, room_ptr);
				else
					allocate_other_flows(room_ptr);
				room_ptr = room_ptr->next;
			}
		}
		i++;
	}
}
