/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 13:07:42 by hmaronen          #+#    #+#             */
/*   Updated: 2022/10/18 13:07:42 by hmaronen         ###   ########.fr       */
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