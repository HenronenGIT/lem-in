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

void allocate_flow_pointer(t_data *data, t_room *current)
{
	size_t i;

	i = 0;
	while (data->start->flow[i])
		i += 1;
	data->start->flow[i] = (t_room *)malloc(sizeof(t_room));
	if (!data->start->flow[i])
		error(MALLOC_ERR);
	data->start->flow[i] = current;
}

void allocate_flow_from_pointer(t_room *current, t_room *parent)
{
	current->flow_from = (t_room *)malloc(sizeof(t_room));
	if (!current->flow_from)
		error(MALLOC_ERR);
	current->flow_from = parent;
}

void set_flows(t_data *data)
{
	t_room *current;
	t_room *parent;

	current = data->end;
	parent = current->parent;
	while (current != data->start)
	{
		if (parent == data->start)
			allocate_flow_pointer(data, current);
		// if (current->flow_parent) //* old if
		//* This if fixed map 5 issue
		if (current->flow_parent && current->flow_parent->flow_from == current) //* move towards parent and cut the flow.
		{
			current->flow_parent->flow_from = NULL;
			current = current->flow_parent;
			parent = current->parent;
			// current->flow_parent = NULL; //! breaks map augment_7, but  but fixes augment_5
		}
		else //* move towards parent
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