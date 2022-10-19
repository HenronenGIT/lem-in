/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:38:23 by igaplich          #+#    #+#             */
/*   Updated: 2022/09/12 16:38:25 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
	We have four different cases when we check that can we step to link.
		1. From current room to link, there is positive flow.
		2. Room where we are at the moment, it was first step to old path.
		3. Room where wea re at the moment, it is second step to old path.
		4. From current room to link, there is not any flow.
*/
void	iterate_links(t_queue **tail, t_queue *que)
{
	size_t	i;
	t_room	**link_array;

	link_array = (t_room **)que->room->links_vec->array;
	i = 0;
	while (i < que->room->links_vec->space_taken)
	{
		if (positive_flow(que->room->flow, link_array[i]))
		{
			i++;
			continue ;
		}
		else if (que->room->flow_from && !que->room->flow_parent)
		{
			found_old_path(tail, que);
			return ;
		}
		else if (que->room->flow_from && que->room->flow_parent)
			can_go_everywhere(que->room, link_array[i], tail);
		else if (link_array[i]->parent == NULL
			&& link_array[i]->parent != que->room)
			visit_using_unused_edge(tail, que, link_array[i]);
		i++;
	}
}

void	bfs_init(t_data *data, t_queue **head, t_queue **tail, t_queue **cur)
{
	if (!data->start
		|| !data->end
		|| !data->start->links_vec
		|| !data->end->links_vec
		|| data->start == data->end)
		error(FORMAT_ERR);
	*head = (t_queue *)malloc(sizeof(t_queue));
	if (!*head)
		error(MALLOC_ERR);
	(*head)->room = data->start;
	(*head)->next = NULL;
	*tail = *head;
	*cur = *head;
}

void	reset_graph_values(t_queue *head)
{
	t_queue	*tmp;

	tmp = head;
	while (tmp)
	{
		tmp->room->parent = NULL;
		tmp->room->flow_parent = NULL;
		head = head->next;
		free(tmp);
		tmp = head;
	}
}

static int	bfs(t_data *data, t_queue **head)
{
	t_queue	*que;
	t_queue	*tail;

	que = NULL;
	tail = NULL;
	bfs_init(data, head, &tail, &que);
	while (data->end->parent == NULL && que != NULL)
	{
		iterate_links(&tail, que);
		que = que->next;
	}
	if (!data->end->parent)
		return (0);
	set_flows(data);
	return (1);
}

void	bfs_driver(t_data *data)
{
	t_queue	*head;
	t_queue	*iterator;

	head = NULL;
	while (bfs(data, &head))
	{
		if (head)
			reset_graph_values(head);
		best_paths_set_operations(data);
	}
	if (data->start->flow[0] == NULL)
		error(NO_PATH_ERR);
	iterator = head;
	while (iterator)
	{
		free(iterator);
		iterator = iterator->next;
	}
	if (data->flags->paths == true)
	{
		print_paths_set(data, data->best_set);
		exit(0);
	}
}
