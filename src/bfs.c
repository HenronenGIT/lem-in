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

void	allocate_flows(t_vec *vector)
{
	size_t	i;
	size_t	j;
	t_room	*tmp;

	i = 0;
	j = 0;
	while (i < vector->length)
	{
		if (vector->array[i])
		{
			tmp = vector->array[i];
			while(tmp)
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

void	reset_graph_values(t_queue **head)
{
	t_queue	*tmp;

	tmp = *head;
	while (tmp)
	{
		tmp->room->parent = NULL;
		tmp->room->visited = 0;
		tmp = tmp->next;
	}
}

void	bfs_init(t_data *data, t_queue **head, t_queue **tail, t_queue **que)
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
	*que = *head;
}

/*	Find path from sink to source.
	When we are jumping from one room to another, same time we mark the flows.
*/
void	recreate_path(t_data *data)
{
	// t_room	*tmp;
	// t_room	*parent;
	// size_t	i;

	// i = 0;
	// tmp = data->end;
	// parent = tmp->parent;
	// while ()
// 	while (parent)
// 	{
// 		while (((t_room **)parent->links_vec->array)[i] != tmp)
// 			i++;
// 		parent->flows[i] = 1;
// 		parent->is_path = 1;
// 		i = 0;
// 		parent = parent->parent;
// 		tmp = tmp->parent;
// 	}
	t_room	*iterator;
	
	while (iterator != data->start)
	{
		
	}
}

void	print_all_paths_flow(t_data *data)
{
	size_t	i;
	size_t	j;
	t_room	*room;

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

void	bfs_driver(t_data *data)
{
	t_queue	*head;
	size_t	i;

	i = 0;
	head = NULL;
	while (bfs(data, &head))
		;
	print_all_paths_flow(data);
}

int	bfs(t_data *data, t_queue **head)
{
	t_queue	*que;
	t_queue	*tail;
	// t_room	**room_arr; //! old
	t_room	**link_array; //? links_vec_cpy
	t_room	*link;
	size_t	i;

	que = NULL;
	tail = NULL;
	bfs_init(data, head, &tail, &que);
	/* Loop until end node has parent && BFS que is empty */
	while (data->end->parent == NULL && que != NULL)
	{
		link_array = (t_room **)que->room->links_vec->array;
		que->room->visited += 1;
		i = 0;
		/* Inspect all the links */
		while (i < que->room->links_vec->space_taken)
		{
			link = link_array[i];
			// link = que->room->links_vec->array[i];
			if (link->visited < 2
				&& que->room->flows[i] == false
				&& link != que->room->parent
				&& link->is_path == false)
			{
				/* Mark current room as parent of next room what we are inspecting */
				if (link->visited == 0) //? Inits sink rooms parent to sink. Can cause errors?
					link->parent = que->room;
				tail->next = (t_queue *)malloc(sizeof(t_queue));
				tail = tail->next;
				// tail->room = que->room->links_vec->array[i];
				tail->room = link;
				tail->next = NULL;
			}
			i++;
		}
		que = que->next;
	}
	if (!data->end->parent)
		return(0);
	recreate_path(data);
	return(1);
}

/*
current room
	for each room connected to the current
		can go to the next room if edge is not visited
		and if edge is not visited in the current BFS cycle
*/
