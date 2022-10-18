/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flow_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:00:33 by hmaronen          #+#    #+#             */
/*   Updated: 2022/10/07 17:00:34 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	allocate_flow_pointer(t_data *data, t_room *current)
{
	size_t	i;

	i = 0;
	while (data->start->flow[i])
		i += 1;
	data->start->flow[i] = current;
}

void	allocate_flow_from_pointer(t_room *current, t_room *parent)
{
	current->flow_from = parent;
}

/*
		set_flows() is basically backtracking function.
	We start backstracking from end room and our goal is to find start room again.
	We have 2 different cases when we are deciding which way we want to go:
		1. Room has only parent pointer initialized.
		2. Room have parent pointer AND flow_parent pointer initialized.
	We always prioritize a room which is case 2.
	Otherwise we move towards room which is case 1.
		Same time when we backtrack we set flows and also cut "double flows".
*/
void	set_flows(t_data *data)
{
	t_room	*current;
	t_room	*parent;

	current = data->end;
	parent = current->parent;
	while (current != data->start)
	{
		if (parent == data->start)
			allocate_flow_pointer(data, current);
		if (current->flow_parent && current->flow_parent->flow_from == current)
		{
			current->flow_parent->flow_from = NULL;
			current = current->flow_parent;
			parent = current->parent;
		}
		else
		{
			if (parent != data->start)
				*parent->flow = current;
			if (current != data->end)
				allocate_flow_from_pointer(current, parent);
			current = current->parent;
			parent = parent->parent;
		}
	}
}
