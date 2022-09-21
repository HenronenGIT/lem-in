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

// void	backtrace_path(t_data *data)
// {
// 	t_room	*tmp;
// 	t_room	*lowest_depth;
// 	size_t	i;

// 	i = 0;
// 	tmp = data->end;
// 	while (tmp != data->start)
// 	{
// 		lowest_depth = tmp->links_vec->array[0];
// 		while (i < tmp->links_vec->space_taken)
// 		{
// 			if (((t_room **)tmp->links_vec->array)[i]->depth < lowest_depth->depth)
// 				lowest_depth = tmp->links_vec->array[i];
// 			i++;
// 		}
// 		printf("%s\n", tmp->room_name);
// 		i = 0;
// 		tmp = lowest_depth;
// 	}
// 	printf("%s\n", tmp->room_name);

// }

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

void	bfs_init(t_data *data, t_queue **head, t_queue **tail, t_queue **cur)
{
	if (!data->start || !data->end || !data->start->links_vec ||
		!data->end->links_vec || data->start == data->end)
		error(FORMAT_ERR);
	*head = (t_queue *)malloc(sizeof(t_queue));
	if (!head)
		error(MALLOC_ERR);
	(*head)->room = data->start;
	(*head)->next = NULL;
	*tail = *head;
	*cur = *head;
}

void	recreate_path(t_data *data)
{
	t_room	*tmp;
	t_room	*parent;
	size_t	i;

	i = 0;
	tmp = data->end;
	parent = tmp->parent;
	while (parent)
	{
		while (((t_room **)parent->links_vec->array)[i] != tmp)
			i++;
		parent->flows[i] = 1;
		i = 0;
		parent = parent->parent;
		tmp = tmp->parent;
	}
}

void	bfs(t_data *data)
{
	t_queue	*head;
	t_queue	*cur;
	t_queue	*tail;
	t_room	**room_arr;
	size_t	i;

	head = NULL;
	cur = NULL;
	tail = NULL;
	bfs_init(data, &head, &tail, &cur);
	while (data->end->parent == NULL && cur != NULL)
	{
		cur->room->visited += 1;
		i = 0;
		while (i < cur->room->links_vec->space_taken)
		{
			room_arr = (t_room **)cur->room->links_vec->array;
			if (room_arr[i]->visited < 2 && !cur->room->flows[i]
				&& room_arr[i] != cur->room->parent)
			{
				if (room_arr[i]->visited == 0)
					room_arr[i]->parent = cur->room;
				tail->next = (t_queue *)malloc(sizeof(t_queue));
				tail = tail->next;
				tail->room = cur->room->links_vec->array[i];
				tail->next = NULL;
			}
			i++;
		}
		cur = cur->next;
	}
	if (!data->end->parent)
		error(NO_PATH);
	recreate_path(data);
	// print_queue(head);
}

/*
current room
	for each room connected to the current
		can go to the next room if edge is not visited
		and if edge is not visited in the current BFS cycle
*/