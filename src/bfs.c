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

void print_paths(t_data *data)
{
	t_room *iterator;
	size_t i;
	size_t path;

	path = 1;
	i = 0;
	ft_printf("\033[0;32mSet of all POSSIBLE paths, after all BFSs\033[0m\n");
	while (data->start->flow[i])
	{
		ft_printf("PATH [%zu] = ", path++);
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

void iterate_links(t_queue **tail, t_queue *que)
{
	size_t i;
	t_room **link_array;

	link_array = (t_room **)que->room->links_vec->array;
	i = 0;
	while (i < que->room->links_vec->space_taken)
	{
		if (positive_flow(que->room->flow, link_array[i]))
		{
			i++;
			continue;
		}
		else if (que->room->flow_from && !que->room->flow_parent) //? handle first step
		{
			found_old_path(tail, que); //? handle first step better name ?.
			return;
		}
		else if (que->room->flow_from && que->room->flow_parent) //? handle second step
			can_go_everywhere(que->room, link_array[i], tail);
		else if (link_array[i]->parent == NULL && link_array[i]->parent != que->room)
			visit_using_unused_edge(tail, que, link_array[i]);
		i++;
	}
}

void bfs_init(t_data *data, t_queue **head, t_queue **tail, t_queue **cur)
{
	if (!data->start || !data->end || !data->start->links_vec || !data->end->links_vec || data->start == data->end)
		error(FORMAT_ERR);
	*head = (t_queue *)malloc(sizeof(t_queue));
	if (!*head)
		error(MALLOC_ERR);
	(*head)->room = data->start;
	(*head)->next = NULL;
	*tail = *head;
	*cur = *head;
}

int	bfs(t_data *data, t_queue **head)
{
	t_queue *que;
	t_queue *tail;

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

void	bfs_driver(t_data *data)
{
	t_queue *head;
	size_t i;

	i = 0;
	head = NULL;
	while (bfs(data, &head))
	{
		if (head)
			reset_graph_values(head);
		best_paths_set_operations(data, i);
		i++;
	}
	ft_printf("\033[0;32mOur algo chose \033[0m\n");
	print_paths_set(data, data->best_set, 100000);
	print_result(data);
}
