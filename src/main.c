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

void	error(int error_number)
{
	if (error_number == INPUT_ERR)
		ft_puterror("Invalid ant input!\n");
	if (error_number == MALLOC_ERR)
		ft_puterror("Not enough space for malloc");
	if (error_number == FORMAT_ERR)
		ft_puterror("Invalid formatting!\n");
	if (error_number == NO_PATH)
		ft_puterror("No path found!\n");
	exit (error_number);
}

void	init_struct(t_data *data)
{
	size_t	i;

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
}

void	print_rooms(t_data data)
{
	size_t i;
	size_t j;
	size_t counter;
	j = 0;
	i = 0;
	t_room	*tmp;
	t_room	**room_arr;

	counter = 0;
	ft_printf("\nstart = %s\n", data.start->room_name);
	ft_printf("end = %s\n\n", data.end->room_name);
	room_arr = (t_room **)data.rooms_vec->array;
	while (i < data.rooms_vec->length)
	{
		if (data.rooms_vec->array[i])
		{
			tmp = data.rooms_vec->array[i];
			ft_printf("|%5s f:", room_arr[i]->room_name);
			while (room_arr[i]->flows && room_arr[i]->links_vec && j < room_arr[i]->links_vec->space_taken)
				ft_printf("%d ", room_arr[i]->flows[j++]);
			ft_printf("|");
			j = 0;
			counter += 1;
			while(((t_room **)data.rooms_vec->array)[i]->next)
			{
				data.rooms_vec->array[i] = ((t_room **)data.rooms_vec->array)[i]->next;
				ft_printf(" -> |%5s f:", ((t_room **)data.rooms_vec->array)[i]->room_name);
				while (room_arr[i]->flows && room_arr[i]->links_vec && j < room_arr[i]->links_vec->space_taken)
					ft_printf("%d ", room_arr[i]->flows[j++]);
			ft_printf("|");
				j = 0;
				counter += 1;
			}
			data.rooms_vec->array[i] = tmp;
			ft_printf("\n");
		}
		i++;
	}
	ft_printf("Rooms amount %zu\n", counter);
	ft_printf("Vec total %zu\n", data.rooms_vec->length);
	ft_printf("Vec taken %zu\n", data.rooms_vec->space_taken);
	ft_printf("Vec left %zu\n", data.rooms_vec->space_left);
}

void	print_links(t_data data)
{
	size_t	i;
	size_t	j;
	t_room	*tmp_room;

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
	t_data	data;

	init_struct(&data);
	read_ants(&data);
	read_rooms(&data);
	allocate_flows(data.rooms_vec);
	bfs_driver(&data);
	print_rooms(data); //! temp
	print_links(data); //! temp
	// printf("%s\n", data.rooms_vec->array[0]->room_name);
	// system("leaks lem-in");
	return (0);
	// exit (0);
}
