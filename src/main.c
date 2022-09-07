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
	int	i;

	i = 0;
	data->ants = 0;
	data->rooms_vec = (t_vec *)malloc(sizeof(t_vec));
	if (!data->rooms_vec)
		error(MALLOC_ERR);
	while (i < 10)
	{
		data->rooms_vec->rooms[i] = (t_room *)malloc(sizeof(t_room));
		data->rooms_vec->rooms[i] = NULL;
		i++;
	}
	data->rooms_vec->length = 10;
	data->rooms_vec->space_left = 10;
	data->rooms_vec->space_taken = 0;
}

int main(void)
{
	t_data	data;

	init_struct(&data);
	read_ants(&data);
	read_rooms(&data);
	// read_links();

	//! temp
	printf("\nstart = %s\n", data.start);
	printf("end = %s\n\n", data.end);
	size_t i = 0;
	while (i < data.rooms_vec->space_taken)
	{
		data.rooms_vec->rooms[i] = data.rooms_vec->rooms[i]->head;
		printf("%s", data.rooms_vec->rooms[i]->room_name);
		data.rooms_vec->rooms[i] = data.rooms_vec->rooms[i]->next;
		while (data.rooms_vec->rooms[i] != NULL)
		{
			printf(" -> %s", data.rooms_vec->rooms[i]->room_name);
			data.rooms_vec->rooms[i] = data.rooms_vec->rooms[i]->next;
		}
		i++;
		printf("\n");
	}
	//! temp
	// system("leaks lem-in");
	// return (0);
	exit (0);
}
