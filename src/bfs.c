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

// void allocate_flows(t_vec *vector)
// {
// 	size_t i;
// 	size_t j;
// 	t_room *tmp;

// 	i = 0;
// 	j = 0;
// 	while (i < vector->length)
// 	{
// 		if (vector->array[i])
// 		{
// 			tmp = vector->array[i];
// 			while (tmp)
// 			{
// 				tmp->flows = (bool *)malloc(sizeof(tmp->links_vec->space_taken));
// 				while (tmp->links_vec && j < tmp->links_vec->space_taken)
// 					tmp->flows[j++] = 0;
// 				tmp = tmp->next;
// 				j = 0;
// 			}
// 		}
// 		i++;
// 	}
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
		// tmp->room->path_number = 0;
		tmp->room->no_flow_visit = false;
		tmp->room->flow_visit = false;
		tmp->room->second_step = 0;
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

/*	Find path from sink to source.
	When we are jumping from one room to another, same time we mark the flows.
*/
// void set_flows(t_data *data)
void set_flows(t_room *end)
{
	t_room *current;
	t_room *parent;
	t_room *link;
	size_t i;
	size_t j;
	// size_t direction;
	// bool second_step;

	// second_step = false;
	// direction = 0;
	current = end;
	parent = current->parent;
	while (parent)
	{
		i = 0;
	parent->flow = (t_room *)malloc(sizeof(t_room));
	parent->flow = current;
	//! SET FLOWS, FLOW CHANGED TO ROOM POINTER.
	// 	i = 0;
	// 	j = 0;
	// 	// ft_printf("%s - ", current->room_name); //! TEMP
	// 	if (second_step == true)
	// 	{
	// 		while (parent->links_vec->array[i] != current) //? better way to find current room?
	// 			i += 1;

	// 		if (!parent->flows[i])
	// 			parent->flows[i] = true;
	// 		else
	// 			parent->flows[i] = false;
	// 		// current->flows[i] = 0; //? might be used to cut another flow from 3 - 4
	// 		current = current->parent;
	// 		parent = current->parent;
	// 		if (current->is_path == false)
	// 			second_step = false; //? if statement can be added if error occurs - "if (!is_path)"
	// 	}
	// 	else if (current->is_path) //? && operation 
	// 	{
	// 		while (i < current->links_vec->space_taken)//disconnect flows
	// 		{
	// 			link = current->links_vec->array[i];
	// 			if (current->flows[i] == true && link->flows[i] == true)
	// 			{
	// 				current->flows[i] = false;
	// 				direction = i;
	// 			}
	// 			i += 1;
	// 		}
	// 		current = current->links_vec->array[direction];
	// 		parent = current->parent;
	// 		second_step = true; //? might cause issues if next step is not a path... if that is even possible situtation

	// 	}
	// 	else
	// 	{
	// 		while (parent->links_vec->array[i] != current) //? better way to find current room?
	// 			i += 1;
	// 		parent->flows[i] = true;
	// 		if (current != data->end)
	// 			current->is_path = true;
	// 		current = current->parent;
	// 		parent = current->parent;
	// 	}
	// }
	// ft_printf("%s - ", current->room_name); //! TEMP
	// ft_printf("\n");						//! TEMP
	}
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
		// print_all_paths_flow(data); //* Print after every bfs
	}
}

void add_to_que(t_queue **tail, t_room *link, t_queue *current, int option)
{
	(*tail)->next = (t_queue *)malloc(sizeof(t_queue));
	if (!(*tail)->next)
		error(MALLOC_ERR);
	// if (option && link->second_step == false)
	// {
	// 	i = 0;
	// 	while (i < link->links_vec->space_taken)
	// 	{
	// 		if (link->links_vec->array[i] == current->room)
	// 			if (link->flows[i])
	// 				link->second_step = true;
	// 		i++;
	// 	}
	// }
	(*tail) = (*tail)->next;
	(*tail)->room = link;
	(*tail)->next = NULL;
	if (!link->parent && !link->visited)
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


// void not_old_path(t_queue *que, t_queue **tail, t_room **link_array)
// {
// 	t_room *link;
// 	size_t i;

// 	link = NULL;
// 	i = 0;

// 	while (i < que->room->links_vec->space_taken)
// 	{
// 		link = link_array[i];
// 		if (link->visited < 2 && que->room->flows[i] == false && link != que->room->parent)
// 		// if (link->visit && que->room->flows[i] == false && link != que->room->parent)
// 			add_to_que(tail, link, que, 0);
// 		i++;
// 	}
// }

void	visit_from_flow(t_queue **tail, t_queue *que, t_room *link)
{
	if (link->flow_visit == true)
		return ;
	if (link->parent == que->room)
		return ;
	add_to_que(tail, link, que, 1);
	link->flow_visit = true;
	// while (i < que->room->links_vec->space_taken)
	// {
	// 	j = 0;
	// 	link = que->room->links_vec->array[i];
	// 	if (link != data->start && link->visited < 2)
	// 	{
	// 		while (j < link->links_vec->space_taken)
	// 		{
	// 			if (link->links_vec->array[j] == que->room)			 //? can be optimized
	// 				if (valid_room(que->room, link, link->flows[j])) //? or "valid_edge"
	// 					add_to_que(tail, link, que, 1);
	// 			j += 1;
	// 		}
	// 	}
	// 	i += 1;
	// }
}

void	visit_from_no_flow(t_queue **tail, t_queue *que, t_room *link)
{
	//* Where we have visited from and is link parent of current room.
	if (link->no_flow_visit == true)
		return ;
	if (link == que->room->parent)
		return ;
	add_to_que(tail, link, que, 1);
	link->no_flow_visit = true;
	// while (i < que->room->links_vec->space_taken)
	// {
	// 	j = 0;
	// 	link = que->room->links_vec->array[i];
	// 	if (link != data->start && link->visited < 2)
	// 	{
	// 		while (j < link->links_vec->space_taken)
	// 		{
	// 			if (link->links_vec->array[j] == que->room)			 //? can be optimized
	// 				if (valid_room(que->room, link, link->flows[j])) //? or "valid_edge"
	// 					add_to_que(tail, link, que, 1);
	// 			j += 1;
	// 		}
	// 	}
	// 	i += 1;
	// }
}

void	iterate_links(t_queue **tail, t_queue *que)
{
	size_t	i;
	t_room	**link_array;

	link_array = (t_room **)que->room->links_vec->array;
	i = 0;
	while (link_array[i])
	{
		if (que->room->is_path == true)
			visit_from_flow(tail, que, link_array[i]);
		else if (que->room->is_path == false)
			visit_from_no_flow(tail, que, link_array[i]);
		i += 1;
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
		que->room->visited += 1;
		iterate_links(&tail, que);
		// print_queue(*head); //! temp
		que = que->next;
	}
	if (!data->end->parent)
		return (0);
	set_flows(data->end);
	return (1);
}
