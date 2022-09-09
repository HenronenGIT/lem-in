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


void	vec_free_links(t_room **room)
{	
	if ((*room)->links_vec)
	{
		if ((*room)->links_vec->links_arr)
			free((*room)->links_vec->links_arr);
		free((*room)->links_vec);
	}
}

void	vec_copy_links(t_room *new_room, t_room *old_room)
{
	size_t	i;

	i = 0;
	while (i < old_room->links_vec->space_taken)
	{
		new_room->links_vec->links_arr[i] = old_room->links_vec->links_arr[i];
		i++;
	}
	new_room->links_vec->space_left = new_room->links_vec->length - i;
	new_room->links_vec->space_taken = i;

}

void	vec_resize_links(t_room **room)
{
	t_links	*new_vec; //!

	vec_allocate_links(new_vec, (*room)->links_vec->length * 2); //!
	vec_copy_links(new_vec, (*room));
	vec_free_links(room);
	(*room) = new_vec;
}

void	vec_allocate_links(t_room *room, size_t length)
{
	size_t	i;

	room->links_vec = (t_links *)malloc(sizeof(t_links));
	if (!room->links_vec)
		error(MALLOC_ERR);
	i = 0;
	room->links_vec->links_arr = (t_room **)malloc(sizeof(t_room *) * length);
	if (!room->links_vec->links_arr)
		error(MALLOC_ERR);
	while (i < 2)
		room->links_vec->links_arr[i++] = NULL;
	room->links_vec->length = length;
	room->links_vec->space_left = length;
	room->links_vec->space_taken = 0;
}

void	vec_link_insert(t_room *room_1, t_room *room_2)
{
	if (!room_1->links_vec)
		vec_allocate_links(room_1, 2)
	if (!room_2->links_vec)
		vec_allocate_links(room_2, 2);
	if (!room_1->links_vec->space_left)
		vec_resize_links(&room_1);

	room_1->links_vec->links_arr[]
}

void	vec_allocate_rooms(t_vec *dst, size_t i)
{
	size_t	j;

	dst->rooms[i] = (t_room *)malloc(sizeof(t_room));
	if (!dst->rooms[i])
		error(MALLOC_ERR);
	dst->rooms[i]->next = NULL;
	dst->rooms[i]->links_vec = NULL;

	// dst->rooms[i]->links_vec = (t_links *)malloc(sizeof(t_links));

	if (!dst->rooms[i]->links_vec)
		error(MALLOC_ERR);
	dst->rooms[i]->links_vec->link_ptr = (t_room **)malloc(sizeof(t_room *) * 3);
	if (!dst->rooms[i]->links_vec->link_ptr)
		error(MALLOC_ERR);
	j = 0;
	while (j < 3)
	{
		dst->rooms[i]->links_vec->link_ptr[j] = NULL;
		j++;
	}
	dst->rooms[i]->links_vec->length = 3;
	dst->rooms[i]->links_vec->space_taken = 0;
	dst->rooms[i]->links_vec->space_left = 3;
}
