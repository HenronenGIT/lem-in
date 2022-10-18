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
	if (error_number == MALLOC_ERR)
		ft_puterror("ERROR: Not enough space for malloc");
	if (error_number == FORMAT_ERR)
		ft_puterror("ERROR: Invalid formatting!\n");
	if (error_number == NO_PATH)
		ft_puterror("ERROR: No path found!\n");
	if (error_number == LINK_ERR)
		ft_puterror("ERROR: Invalid link input!\n");
	if (error_number == ANT_ERR)
		ft_puterror("ERROR: Invalid ant input!\n");
	exit(error_number);
}

static void	print_input(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->input_vec->space_taken)
	{
		ft_printf("%s\n", ((char **)data->input_vec->array)[i]);
		i += 1;
	}
	ft_printf("\n");
}

static void	init_data_struct(t_data *data)
{
	size_t	start_size;

	start_size = 10;
	data->ants = 0;
	data->rooms_vec = (t_vec *)malloc(sizeof(t_vec));
	data->input_vec = (t_vec *)malloc(sizeof(t_vec));
	if (!data->rooms_vec || !data->input_vec)
		error(MALLOC_ERR);
	vec_new_arr(data->rooms_vec, start_size);
	vec_new_arr(data->input_vec, start_size);
}

int	main(int argc, char **argv)
{
	t_data	data;

	init_data_struct(&data);
	read_ants(&data);
	read_rooms(&data);
	allocate_flow_pointers(&data);
	bfs_driver(&data);
	print_input(&data);
	print_result(&data);
	return (0);
}
