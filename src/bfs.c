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


void	bfs(t_data *data)
{
	t_queue	*head;
	t_queue	*insert;
	t_queue	*cur;
	size_t	depth;
	size_t	i;

	if (!data->start || !data->end || !data->start->links_vec
		|| !data->end->links_vec || data->start == data->end)
		error(FORMAT_ERR);
	head = (t_queue *)malloc(sizeof(t_queue));
	head->room = data->start;
	if (!head)
		error(MALLOC_ERR);
	printf("head = %s\n", head->room->room_name);
	insert = head;
	i = 0;
	data->start->depth = 0;
	cur = head;
	depth = 1;
	while (insert->room != data->end)
	{
		while (i < head->room->links_vec->space_taken && insert->room != data->end)
		{
			cur->room->visited = 1;
			if (!((t_room **)cur->room->links_vec->array)[i]->visited)
			{
				((t_room **)cur->room->links_vec->array)[i]->depth = cur->room->depth + 1;
				insert->next = (t_queue *)malloc(sizeof(t_queue));
				insert->next->room = cur->room->links_vec->array[i];
				if (!insert->next)
					error(MALLOC_ERR);
				insert = insert->next;
				insert->next = NULL;
			}
			i++;
		}
		i = 0;
		cur = cur->next;
	}
}