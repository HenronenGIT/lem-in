/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:37:29 by igaplich          #+#    #+#             */
/*   Updated: 2022/08/22 15:37:31 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void print_links(t_data data)
{
	size_t i;
	size_t j;
	t_room *tmp_room;

	i = 0;
	j = 0;
	while (i < data.rooms_vec->length)
	{
		if (data.rooms_vec->array[i])
		{
			tmp_room = data.rooms_vec->array[i];
			while (tmp_room)
			{
				ft_printf("%5s: ", tmp_room->room_name);
				if (tmp_room->links_vec)
				{
					while (j < tmp_room->links_vec->space_taken)
					{
						ft_printf("-> %5s ", ((t_room **)tmp_room->links_vec->array)[j]->room_name);
						// ft_printf("-> %s ", ((t_vec **)tmp_room->links_vec->array)[j]->room_name););
						j++;
					}
				}
				tmp_room = tmp_room->next;
				j = 0;
				ft_printf("\n");
			}
		}
		i++;
	}
}

void error(int error_number)
{
	if (error_number == INPUT_ERR)
		ft_puterror("ERROR: Invalid ant input!\n");
	if (error_number == MALLOC_ERR)
		ft_puterror("ERROR: Not enough space for malloc");
	if (error_number == FORMAT_ERR)
		ft_puterror("ERROR: Invalid formatting!\n");
	if (error_number == NO_PATH)
		ft_puterror("ERROR: No path found!\n");
	if (error_number == LINK_ERR)
		ft_puterror("ERROR: Invalid link input!\n");
	exit(error_number);
}

void allocate_other_flows(t_room *room_ptr)
{
	room_ptr->flow = (t_room **)malloc(sizeof(t_room *) * 2);

	if (!room_ptr->flow)
		error(MALLOC_ERR);
	room_ptr->flow[0] = NULL;
	room_ptr->flow[1] = NULL;
}

void allocate_start_flows(t_data *data, t_room *room_ptr)
{
	size_t end_links;
	size_t i;

	i = 0;
	end_links = data->end->links_vec->space_taken;
	room_ptr->flow = (t_room **)malloc(sizeof(t_room *) * (end_links + 1));
	if (!room_ptr->flow)
		error(MALLOC_ERR);
	while (i <= end_links)
		room_ptr->flow[i++] = NULL;
}

void allocate_flow_pointers(t_data *data)
{
	size_t i;
	t_room *room_ptr;

	i = 0;
	while (i < data->rooms_vec->length)
	{
		if (data->rooms_vec->array[i])
		{
			room_ptr = data->rooms_vec->array[i];
			while (room_ptr)
			{
				if (room_ptr == data->start)
					allocate_start_flows(data, room_ptr);
				else
					allocate_other_flows(room_ptr);
				room_ptr = room_ptr->next;
			}
		}
		i++;
	}
}

void init_vector(t_vec *vector, size_t start_size)
{
	size_t i;

	i = 0;
	while (i < start_size)
		vector->array[i++] = NULL;
	vector->length = start_size;
	vector->space_left = start_size;
	vector->space_taken = 0;
}

static void allocate_vectors(t_data *data, size_t start_size)
{
	data->rooms_vec = (t_vec *)malloc(sizeof(t_vec));
	if (!data->rooms_vec)
		error(MALLOC_ERR);
	data->rooms_vec->array = (void **)malloc(sizeof(t_room *) * start_size);
	if (!data->rooms_vec->array)
		error(MALLOC_ERR);
}

void init_data_struct(t_data *data)
{
	size_t start_size;

	start_size = 10;
	data->ants = 0;
	allocate_vectors(data, start_size);
	init_vector(data->rooms_vec, start_size);
}

int main(void)
{
	t_data data;

	init_data_struct(&data);
	read_ants(&data);
	read_rooms(&data);
	allocate_flow_pointers(&data);
	bfs_driver(&data);
	// print_rooms(data); //! temp
	// print_links(data); //! temp
	// printf("%s\n", data.rooms_vec->array[0]->room_name);
	// system("leaks lem-in");
	return (0);
	// exit (0);
}
