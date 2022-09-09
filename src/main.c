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
	exit (error_number);
}

void	init_struct(t_data *data)
{
	size_t	i;
	data->ants = 0;
	data->rooms_vec = (t_vec *)malloc(sizeof(t_vec));
	if (!data->rooms_vec)
		error(MALLOC_ERR);
	data->rooms_vec->rooms = (t_room **)malloc(sizeof(t_room *) * 10);
	if (!data->rooms_vec->rooms)
		error(MALLOC_ERR);
	i = 0;
	while (i < 10)
		data->rooms_vec->rooms[i++] = NULL;
	data->rooms_vec->length = 10;
	data->rooms_vec->space_left = 10;
	data->rooms_vec->space_taken = 0;
}

void	print_rooms(t_data data)
{
	size_t i;
	size_t counter;
	i = 0;
	t_room	*tmp;

	counter = 0;
	ft_printf("\nstart = %s\n", data.start);
	ft_printf("end = %s\n\n", data.end);
	
	while (i < data.rooms_vec->length)
	{
		if (data.rooms_vec->rooms[i])
		{
			tmp = data.rooms_vec->rooms[i];
			ft_printf("%4s", data.rooms_vec->rooms[i]->room_name);
			counter += 1;
			while(data.rooms_vec->rooms[i]->next)
			{
				data.rooms_vec->rooms[i] = data.rooms_vec->rooms[i]->next;
				ft_printf(" -> %4s", data.rooms_vec->rooms[i]->room_name);
				counter += 1;
			}
			data.rooms_vec->rooms[i] = tmp;
			ft_printf("\n");
		}
		i++;
	}
	ft_printf("Rooms amount %zu\n", counter);
	ft_printf("Vec total %zu\n", data.rooms_vec->length);
	ft_printf("Vec taken %zu\n", data.rooms_vec->space_taken);
	ft_printf("Vec left %zu\n", data.rooms_vec->space_left);
}

int main(void)
{
	t_data	data;

	init_struct(&data);
	read_ants(&data);
	read_rooms(&data);
	print_rooms(data); //! temp
	// printf("%s\n", data.rooms_vec->rooms[0]->room_name);
	// system("leaks lem-in");
	return (0);
	// exit (0);
}
