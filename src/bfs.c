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

// void print_all_paths_flow(t_data *data)
// {
// 	size_t i;
// 	size_t j;
// 	t_room *room;

// 	i = 0;
// 	j = 0;
// 	room = data->start;
// 	while (i < data->start->links_vec->space_taken)
// 	{
// 		if (data->start->flows[i])
// 		{
// 			room = data->start->links_vec->array[i];
// 			printf("New Path\n");
// 			printf("%s ", data->start->room_name);
// 			while (room != data->end)
// 			{
// 				while (j < room->links_vec->space_taken)
// 				{
// 					if (room->flows[j])
// 					{
// 						printf("%s ", room->room_name);
// 						room = room->links_vec->array[j];
// 						// room->path_number = i + 1;
// 						j = 0;
// 					}
// 					j++;
// 				}
// 				j = 0;
// 			}
// 			printf("%s \n", data->end->room_name);
// 		}
// 		i++;
// 	}
// 	printf("\n");
// }

void print_queue(t_queue *head)
{
	t_queue *tmp;

	tmp = head;
	printf("Queue\n");
	while (head)
	{
		printf("%s ", head->room->room_name);
		head = head->next;
	}
	printf("\n");
	head = tmp;
}

void reset_graph_values(t_queue *head)
{
	t_queue *tmp;

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

void bfs_init(t_data *data, t_queue **head, t_queue **tail, t_queue **cur)
{
	if (!data->start || !data->end || !data->start->links_vec || !data->end->links_vec || data->start == data->end)
		error(FORMAT_ERR);

	*head = (t_queue *)malloc(sizeof(t_queue));
	if (!head)
		error(MALLOC_ERR);
	(*head)->room = data->start;
	(*head)->next = NULL;
	*tail = *head;
	*cur = *head;
}

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
	size_t i;

	i = 0;
	current = data->end;
	parent = current->parent;
	while (current != data->start)
	{
		if (parent == data->start)
			allocate_flow_pointer(data, current);
		if (current->flow_parent) //* move towards parent and cut the flow.
		{
			current->flow_parent->flow_from = NULL;
			current = current->flow_parent;
			parent = current->parent;
			current->flow_parent = NULL;
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

void print_path(t_data *data)
{
	t_room *iterator;
	size_t i;

	i = 0;
	while (data->start->flow[i])
	{
		ft_printf("%s -> ", data->start->room_name);
		iterator = data->start->flow[i];
		while (iterator != data->end)
		{
			ft_printf("%s -> ", iterator->room_name);
			iterator = *iterator->flow;
		}
		ft_printf("%s\n", iterator->room_name);
		i += 1;
	}
	ft_printf("\n");
}

void bfs_driver(t_data *data)
{
	t_queue *head;
	size_t i;

	i = 0;
	head = NULL;
	while (bfs(data, &head))
	{
		// print_queue(head);
		if (head)
			reset_graph_values(head);
		print_path(data);
		// print_all_paths_flow(data); //* Print after every bfs
	}
}

void add_to_que(t_queue **tail, t_room *link)
{
	(*tail)->next = (t_queue *)malloc(sizeof(t_queue));
	if (!(*tail)->next)
		error(MALLOC_ERR);
	(*tail) = (*tail)->next;
	(*tail)->room = link;
	(*tail)->next = NULL;
}

void visit_using_flow_edge(t_queue **tail, t_queue *que, t_room *link)
{
	if (link == que->room->parent)
		return;
	add_to_que(tail, link);
}

void visit_using_unused_edge(t_queue **tail, t_queue *que, t_room *link)
{
	size_t i;

	i = 0;
	//* Where we have visited from and is link parent of current room.
	if (que->room->flow[i] == link)
		return;
	if (link == que->room->parent)
		return;
	add_to_que(tail, link);
	link->parent = que->room;
}

void found_old_path(t_queue **tail, t_queue *que)
{
	t_room **link_array;

	link_array = (t_room **)que->room->links_vec->array;
	add_to_que(tail, que->room->flow_from);
	que->room->flow_from->flow_parent = que->room;
}

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

void can_go_everywhere(t_room *current, t_room *link, t_queue **tail)
{
	if (link->flow_parent)
		return;
	if (link->parent)
		return;
	add_to_que(tail, link);
	link->parent = current;
}

void iterate_links(t_queue **tail, t_queue *que)
{
	size_t i;
	t_room **link_array;

	link_array = (t_room **)que->room->links_vec->array;
	i = 0;
	while (i < que->room->links_vec->space_taken) //? jump table possibility
	{
		if (positive_flow(que->room->flow, link_array[i]))
		{
			i++;
			continue ;
		}
		else if (que->room->flow_from && !que->room->flow_parent) //? handle first step
		{
			found_old_path(tail, que); //? handle first step.
			return;
		}
		else if (que->room->flow_from && que->room->flow_parent) //? handle second step
			can_go_everywhere(que->room, link_array[i], tail);
		else if (link_array[i]->parent == NULL && link_array[i]->parent != que->room)
			visit_using_unused_edge(tail, que, link_array[i]);
		i++;
	}
}

int bfs(t_data *data, t_queue **head)
{
	t_queue *que;
	t_queue *tail;

	que = NULL;
	tail = NULL;
	bfs_init(data, head, &tail, &que);
	while (data->end->parent == NULL && que != NULL)
	{
		iterate_links(&tail, que);
		// print_queue(*head); //! temp
		que = que->next;
	}
	if (!data->end->parent)
		return (0);
	set_flows(data);
	return (1);
}
