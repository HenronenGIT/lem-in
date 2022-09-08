/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_hashing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 13:32:56 by igaplich          #+#    #+#             */
/*   Updated: 2022/09/08 13:33:01 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

unsigned long	hashing(t_data *data, char *name)
{
	size_t			i;
	unsigned long	hash;

	if (!name)
		error(-3);
	hash = 5381;
	i = 0;
	while (name[i])
	{
		hash = ((hash << 5) + hash) + name[i];
		i++;
	}
	return (hash % data->rooms_vec->length);
}

void	handle_collision(t_room *list_room, t_room *insert_room)
{
	t_room	*tmp_room;

	tmp_room = list_room;
	while (tmp_room->next)
	{
		tmp_room = tmp_room->next;
		printf("ENTERED");
	}
	tmp_room->next = insert_room;
}

void	move_and_clear_array(t_data *data, t_room **tmp_arr)
{
	size_t	i;

	i = 0;
	while (i < data->rooms_vec->space_taken)
	{
		tmp_arr[i] = data->rooms_vec->rooms[i];
		data->rooms_vec->rooms[i] = NULL;
		i++;
	}
}

void	hash_and_move_array(t_data *data, t_room **tmp_arr)
{
	size_t i;
	unsigned long	hash;

	i = 0;
	while (i < data->rooms_vec->space_taken)
	{
		hash = hashing(data, tmp_arr[i]->room_name);
		if (!data->rooms_vec->rooms[hash])
			data->rooms_vec->rooms[hash] = tmp_arr[i];
		else
			handle_collision(data->rooms_vec->rooms[hash], tmp_arr[i]);
		i++;
	}
}

void	sort_hash_values(t_data *data)
{
	t_room	**tmp_arr;

	tmp_arr = (t_room **)malloc(sizeof(t_room) * data->rooms_vec->space_taken);
	if (!tmp_arr)
		error(MALLOC_ERR);
	move_and_clear_array(data, tmp_arr);
	hash_and_move_array(data, tmp_arr);
}