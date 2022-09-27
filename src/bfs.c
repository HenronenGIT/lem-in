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

void print_all_paths_flow(t_data *data)
{
	size_t i;
	size_t j;
	t_room *room;

	i = 0;
	j = 0;
	room = data->start;
	while (i < data->start->links_vec->space_taken)
	{
		if (data->start->flows[i])
		{
			room = data->start->links_vec->array[i];
			printf("New Path\n");
			while (room != data->end)
			{
				while (j < room->links_vec->space_taken)
				{
					if (room->flows[j])
					{
						printf("%s ", room->room_name);
						room = room->links_vec->array[j];
					}
					j++;
				}
				j = 0;
			}
			printf("\n");
		}
		i++;
	}
}

void allocate_flows(t_vec *vector)
{
	size_t i;
	size_t j;
	t_room *tmp;

	i = 0;
	j = 0;
	while (i < vector->length)
	{
		if (vector->array[i])
		{
			tmp = vector->array[i];
			while (tmp)
			{
				tmp->flows = (bool *)malloc(sizeof(tmp->links_vec->space_taken));
				while (tmp->links_vec && j < tmp->links_vec->space_taken)
					tmp->flows[j++] = 0;
				tmp = tmp->next;
				j = 0;
			}
		}
		i++;
	}
}

void print_queue(t_queue *head)
{
	printf("Queue\n");
	while (head)
	{
		printf("%s\n", head->room->room_name);
		head = head->next;
	}
}

void reset_graph_values(t_queue **head)
{
	t_queue *tmp;

	tmp = *head;
	while (tmp)
	{
		tmp->room->parent = NULL;
		tmp->room->visited = 0;
		tmp->room->second_step = 0;
		tmp = tmp->next;
	}
}

void bfs_init(t_data *data, t_queue **head, t_queue **tail, t_queue **cur)
{
	if (!data->start || !data->end || !data->start->links_vec ||
		!data->end->links_vec || data->start == data->end)
		error(FORMAT_ERR);
	if (*head)
		reset_graph_values(head);
	*head = (t_queue *)malloc(sizeof(t_queue));
	if (!head)
		error(MALLOC_ERR);
	(*head)->room = data->start;
	(*head)->next = NULL;
	*tail = *head;
	*cur = *head;
}

/*	Find path from sink to source.
	When we are jumping from one room to another, same time we mark the flows.
*/

void set_flows(t_data *data)
{
	t_room *current;
	t_room *parent;
	size_t i;

	current = data->end;
	parent = current->parent;
	while (parent)
	{
		i = 0;
		ft_printf("%s - ", current->room_name); //! TEMP
		if (current->second_step)
		{
			while (current->flows[i] == false) //! might segfault :D
				i++;
			current->parent = current->links_vec->array[i];
			parent = current->parent;
			current->flows[i] = 0;
		}
		while (((t_room **)parent->links_vec->array)[i] != current)
			i++;
		parent->flows[i] = 1;
		if (parent != data->start)
			parent->is_path = 1;
		i = 0;
		current = current->parent;
		parent = current->parent;
	}
	ft_printf("%s - ", current->room_name); //! TEMP
	ft_printf("\n");						//! TEMP
}

void bfs_driver(t_data *data)
{
	t_queue *head;
	size_t i;

	i = 0;
	head = NULL;
	while (bfs(data, &head))
		;
	print_all_paths_flow(data);
}

void add_to_que(t_queue **tail, t_room *link, t_queue *current)
{
	size_t	i;
	(*tail)->next = (t_queue *)malloc(sizeof(t_queue));
	if (link->second_step == false && link->is_path)
	{
		i = 0;
		while (i < link->links_vec->space_taken)
		{
			if (link->links_vec->array[i] == current->room)
				if (link->flows[i])
					link->second_step = true;
			i++;
		}
	}
	(*tail) = (*tail)->next;
	(*tail)->room = link;
	(*tail)->next = NULL;
	if (!link->parent)
		link->parent = current->room;
}

/* Check that if all rules passes and room is valid for que */
int valid_room(t_room *current, t_room *link, bool flow)
{
	if (current->second_step && !link->parent)
		return (1);
	else if (!current->second_step && flow == true && link->parent != current)
		return (1);
	else
		return (0);
}

void found_old_path(t_data *data, t_queue **tail, t_queue *que)
{
	size_t i;
	size_t j;
	t_room *link;

	i = 0;
	while (i < que->room->links_vec->space_taken)
	{
		j = 0;
		link = que->room->links_vec->array[i];
		if (link != data->start && link->visited < 2)
		{
			while (j < link->links_vec->space_taken)
			{
				if (link->links_vec->array[j] == que->room)			 //? can be optimized
					if (valid_room(que->room, link, link->flows[j])) //? or "valid_edge"
						add_to_que(tail, link, que);
				j += 1;
			}
		}
		i += 1;
	}
}

int bfs(t_data *data, t_queue **head)
{
	t_queue *que;
	t_queue *tail;
	t_room **link_array; //? links_vec_cpy
	t_room *link;
	size_t i;

	que = NULL;
	tail = NULL;
	bfs_init(data, head, &tail, &que);
	while (data->end->parent == NULL && que != NULL)
	{
		link_array = (t_room **)que->room->links_vec->array;
		que->room->visited += 1;
		i = 0;
		if (que->room->is_path)
			found_old_path(data, &tail, que);
		else
		{
			while (i < que->room->links_vec->space_taken)
			{
				link = link_array[i];
				if (link->visited < 2 && que->room->flows[i] == false && link != que->room->parent)
				{
					/* Inits link->parent to room where we are currently*/
					if (link->visited == 0) //? Inits sink rooms parent to sink. Can cause errors?
						link->parent = que->room;
					tail->next = (t_queue *)malloc(sizeof(t_queue));
					tail = tail->next;
					tail->room = link;
					tail->next = NULL;
				}
				i++;
			}
		}
		que = que->next;
	}
	if (!data->end->parent)
		return (0);
	set_flows(data);
	return (1);
}

/*
current room
	for each room connected to the current
		can go to the next room if edge is not visited
		and if edge is not visited in the current BFS cyclew
*/
