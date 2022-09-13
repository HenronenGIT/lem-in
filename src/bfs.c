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

void	backtrace_path(t_data *data)
{
	t_room	*tmp;
	t_room	*lowest_depth;
	size_t	i;

	i = 0;
	tmp = data->end;
	while (tmp != data->start)
	{
		lowest_depth = tmp->links_vec->array[0];
		while (i < tmp->links_vec->space_taken)
		{
			if (((t_room **)tmp->links_vec->array)[i]->depth < lowest_depth->depth)
				lowest_depth = tmp->links_vec->array[i];
			i++;
		}
		printf("%s\n", tmp->room_name);
		i = 0;
		tmp = lowest_depth;
	}
	printf("%s\n", tmp->room_name);

}

void bfs(t_data *data)
{
	t_queue *head;
	t_queue *tmp;
	t_queue *tail;
	size_t i;
	size_t j;

	if (!data->start || !data->end || !data->start->links_vec || !data->end->links_vec || data->start == data->end)
		error(FORMAT_ERR);
	head = (t_queue *)malloc(sizeof(t_queue));
	head->room = data->start;
	if (!head)
		error(MALLOC_ERR);
	printf("head = %s\n", head->room->room_name);
	tail = head;
	i = 0;
	data->start->depth = 0;
	j = 0;
	while (head)
	{
		if (!head->room->visited)
		{
			head->room->visited = 1;
			while (i < head->room->links_vec->space_taken)
			{
				if (!((t_room **)head->room->links_vec->array)[i]->visited)
				{
					if (((t_room **)head->room->links_vec->array)[i]->depth == 0) //?
						((t_room **)head->room->links_vec->array)[i]->depth = head->room->depth + 1;
					tail->next = (t_queue *)malloc(sizeof(t_queue));
					tail->next->room = head->room->links_vec->array[i];
					if (!tail->next)
						error(MALLOC_ERR);
					tail = tail->next;
					tail->next = NULL;
				}
				i++;
			}
			j++;
		}
		i = 0;
		tmp = head;
		head = head->next;

	}
	printf("Amount of rooms visited = %zu\n", j);
	backtrace_path(data);
}

