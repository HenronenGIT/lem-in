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
	if (error_number == 1)
		ft_puterror("Invalid ant input!\n");
	if (error_number == MALLOC_ERR)
		ft_puterror("Not enough space for malloc");
	if (error_number == FORMAT_ERR)
		ft_puterror("Invalid formatting!\n");
	exit (error_number);
}

void	init_struct(t_data *data)
{
	data->ants = 0;
	data->rooms = (t_vec *)malloc(sizeof(t_vec));
	data->rooms->room_names = NULL;
	data->rooms->length = 0;
	data->rooms->space_left = 0;
	data->rooms->space_taken = 0;
}

int main(void)
{
	t_data	data;

	init_struct(&data);
	read_ants(&data);
	read_rooms(&data);
	// read_links();

	//! temp
	size_t i = 0;
	while (i < data.rooms->length)
	{
		printf("%s\n", data.rooms->room_names[i]);
		i++;
	}
	//! temp
	// system("leaks lem-in");
	// return (0);
	exit (0);
}