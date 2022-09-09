/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:24:05 by hmaronen          #+#    #+#             */
/*   Updated: 2022/09/07 15:24:06 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"


void	vec_free_links(t_room *room)
{	
	if (room->links_vec)
	{
		if (room->links_vec->links_arr)
			free(room->links_vec->links_arr);
		free(room->links_vec);
	}
}

void	vec_copy_links(t_links *new_vec, t_links *old_vec)
{
	size_t	i;

	i = 0;
	while (i < old_vec->space_taken)
	{
		new_vec->links_arr[i] = old_vec->links_arr[i];
		i++;
	}
	new_vec->space_left = new_vec->length - i;
	new_vec->space_taken = i;
}

void	vec_resize_links(t_room *room)
{
	t_links	*new_vec;

	new_vec = NULL;
	allocate_links_vec(&new_vec, room->links_vec->length * 2);
	vec_copy_links(new_vec, room->links_vec);
	vec_free_links(room);
	room->links_vec = new_vec;
}

void	vec_allocate_links_array(t_links **links_vec, size_t length)
{
	size_t	i;

	i = 0;
	(*links_vec)->links_arr = (t_room **)malloc(sizeof(t_room *) * length);
	if (!(*links_vec)->links_arr)
		error(MALLOC_ERR);
	while (i < length)
		(*links_vec)->links_arr[i++] = NULL;
	(*links_vec)->length = length;
	(*links_vec)->space_left = length;
	(*links_vec)->space_taken = 0;
}

void	allocate_links_vec(t_links **vec, size_t length)
{
	(*vec) = (t_links *)malloc(sizeof(t_links));
	if (!(*vec))
		error(MALLOC_ERR);
	vec_allocate_links_array(vec, length);
}

void	vec_link_insert(t_room *room_1, t_room *room_2)
{
	if (!room_1->links_vec)
		allocate_links_vec(&room_1->links_vec, 2);
	if (!room_2->links_vec)
		allocate_links_vec(&room_2->links_vec, 2);
	if (!room_1->links_vec->space_left)
		vec_resize_links(room_1);
	if (!room_2->links_vec->space_left)
		vec_resize_links(room_2);
	room_1->links_vec->links_arr[room_1->links_vec->space_taken] = room_2;
	room_1->links_vec->space_left--;
	room_1->links_vec->space_taken++;
	room_2->links_vec->links_arr[room_2->links_vec->space_taken] = room_1;
	room_2->links_vec->space_left--;
	room_2->links_vec->space_taken++;
}

void	vec_allocate_rooms(t_vec *dst, size_t i)
{
	dst->rooms[i] = (t_room *)malloc(sizeof(t_room));
	if (!dst->rooms[i])
		error(MALLOC_ERR);
	dst->rooms[i]->next = NULL;
	dst->rooms[i]->links_vec = NULL;
}
