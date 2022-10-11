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

void error(int error_number)
{
	if (error_number == INPUT_ERR)
		ft_puterror("Invalid ant input!\n");
	if (error_number == MALLOC_ERR)
		ft_puterror("Not enough space for malloc");
	if (error_number == FORMAT_ERR)
		ft_puterror("Invalid formatting!\n");
	if (error_number == NO_PATH)
		ft_puterror("No path found!\n");
	exit(error_number);
}

void init_struct(t_data *data)
{
	size_t i;

	data->ants = 0;
	data->rooms_vec = (t_vec *)malloc(sizeof(t_vec));
	if (!data->rooms_vec)
		error(MALLOC_ERR);
	data->rooms_vec->array = (void **)malloc(sizeof(t_room *) * 10);
	if (!data->rooms_vec->array)
		error(MALLOC_ERR);
	i = 0;
	while (i < 10)
		data->rooms_vec->array[i++] = NULL;
	data->rooms_vec->length = 10;
	data->rooms_vec->space_left = 10;
	data->rooms_vec->space_taken = 0;
	data->best_set = NULL;
	data->best_speed = 0;
}

// void allocate_flow_pointers(t_vec *vector)
void allocate_flow_pointers(t_data *data)
{
	size_t i;
	size_t j;
	t_vec *vector;
	size_t end_links;

	end_links = data->end->links_vec->space_taken;
	vector = data->rooms_vec;
	t_room *room_ptr;
	i = 0;
	while (i < vector->length)
	{
		if (vector->array[i])
		{
			room_ptr = vector->array[i];
			while (room_ptr)
			{
				//! Allocates that many flow indexes to start room as they are links in end room
				//? Can cause problems if end room links does not lead anywhere
				//? 	At the moment allocates 1 pointer for EVERY room. This may be unneccessary, because there is not flow from every room
				//?	Allocation can be moved to "set_flows() func."
				if (room_ptr == data->start) //* FOR START ROOM
				{
					room_ptr->flow = (t_room **)malloc(sizeof(t_room *) * (end_links + 1));
					if (!room_ptr)
						error(MALLOC_ERR);
					j = 0;
					while (j <= end_links) //! can cause issues
					{
						room_ptr->flow[j] = NULL;
						j += 1;
					}
				}
				//!
				else //* FOR ALL OTHER ROOM THAN START
				{

					room_ptr->flow = (t_room **)malloc(sizeof(t_room *) * 2);
					if (!room_ptr->flow)
						error(MALLOC_ERR);
					room_ptr->flow[0] = (t_room *)malloc(sizeof(t_room));
					room_ptr->flow[1] = (t_room *)malloc(sizeof(t_room));
					if (!room_ptr->flow[0] || !room_ptr->flow[1])
						error(MALLOC_ERR);
					room_ptr->flow[0] = NULL;
					room_ptr->flow[1] = NULL;
				}
				room_ptr = room_ptr->next;
			}
		}
		i++;
	}
}

// void	print_rooms(t_data data)
// {
// 	size_t i;
// 	size_t j;
// 	size_t counter;
// 	j = 0;
// 	i = 0;
// 	t_room	*tmp;
// 	t_room	**room_arr;

// 	counter = 0;
// 	ft_printf("\nstart = %s\n", data.start->room_name);
// 	ft_printf("end = %s\n\n", data.end->room_name);
// 	room_arr = (t_room **)data.rooms_vec->array;
// 	while (i < data.rooms_vec->length)
// 	{
// 		if (data.rooms_vec->array[i])
// 		{
// 			tmp = data.rooms_vec->array[i];
// 			ft_printf("|%5s f:", room_arr[i]->room_name);
// 			while (room_arr[i]->flows && room_arr[i]->links_vec && j < room_arr[i]->links_vec->space_taken)
// 				ft_printf("%d ", room_arr[i]->flows[j++]);
// 			ft_printf("|");
// 			j = 0;
// 			counter += 1;
// 			while(((t_room **)data.rooms_vec->array)[i]->next)
// 			{
// 				data.rooms_vec->array[i] = ((t_room **)data.rooms_vec->array)[i]->next;
// 				ft_printf(" -> |%5s f:", ((t_room **)data.rooms_vec->array)[i]->room_name);
// 				while (room_arr[i]->flows && room_arr[i]->links_vec && j < room_arr[i]->links_vec->space_taken)
// 					ft_printf("%d ", room_arr[i]->flows[j++]);
// 			ft_printf("|");
// 				j = 0;
// 				counter += 1;
// 			}
// 			data.rooms_vec->array[i] = tmp;
// 			ft_printf("\n");
// 		}
// 		i++;
// 	}
// 	ft_printf("Rooms amount %zu\n", counter);
// 	ft_printf("Vec total %zu\n", data.rooms_vec->length);
// 	ft_printf("Vec taken %zu\n", data.rooms_vec->space_taken);
// 	ft_printf("Vec left %zu\n", data.rooms_vec->space_left);
// }

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

int main(void)
{
	t_data data;

	init_struct(&data);
	read_ants(&data);
	read_rooms(&data);
	// allocate_flow_pointers(data.rooms_vec);
	allocate_flow_pointers(&data);
	bfs_driver(&data);
	print_result(&data);
	// print_rooms(data); //! temp
	// print_links(data); //! temp
	// printf("%s\n", data.rooms_vec->array[0]->room_name);
	// system("leaks lem-in");
	return (0);
	// exit (0);
}
