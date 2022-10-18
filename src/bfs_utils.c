/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:54:12 by hmaronen          #+#    #+#             */
/*   Updated: 2022/10/07 13:54:13 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int positive_flow(t_room **flows, t_room *link)
{
	size_t i;

	i = 0;
	while (flows[i])
	{
		if (flows[i] == link)
			return (1);
		i += 1;
	}
	return (0);
}

void	found_old_path(t_queue **tail, t_queue *que)
{
	t_room **link_array;

	link_array = (t_room **)que->room->links_vec->array;
	add_to_que(tail, que->room->flow_from);
	que->room->flow_from->flow_parent = que->room;
}

void	can_go_everywhere(t_room *current, t_room *link, t_queue **tail)
{
	if (link->parent)
		return;
	add_to_que(tail, link);
	if (current->flow_from == link)
		link->flow_parent = current;
	else
		link->parent = current;
}

void	visit_using_unused_edge(t_queue **tail, t_queue *que, t_room *link)
{
	size_t i;

	i = 0;
	if (que->room->flow[i] == link)
		return;
	if (link == que->room->parent)
		return;
	add_to_que(tail, link);
	link->parent = que->room;
}

void	add_to_que(t_queue **tail, t_room *link)
{
	(*tail)->next = (t_queue *)malloc(sizeof(t_queue));
	if (!(*tail)->next)
		error(MALLOC_ERR);
	(*tail) = (*tail)->next;
	(*tail)->room = link;
	(*tail)->next = NULL;
}
