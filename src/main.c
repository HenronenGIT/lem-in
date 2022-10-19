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
	if (error_number == NO_PATH_ERR)
		ft_puterror("ERROR: No paths to end!\n");
	if (error_number == LINK_ERR)
		ft_puterror("ERROR: Invalid link input!\n");
	if (error_number == ANT_ERR)
		ft_puterror("ERROR: Invalid ant input!\n");
	if (error_number == FLAG_ERR)
		ft_puterror("ERROR: Invalid flag input!\n");
	if (error_number == COORD_ERR)
		ft_puterror("ERROR: Invalid coordinate input!\n");
	if (error_number == NO_LINK_TO_END)
		ft_puterror("ERROR: No links to end room!\n");
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
	data->start = NULL;
	data->end = NULL;
	data->flags = (t_lem_flags *)malloc(sizeof(t_lem_flags));
	data->rooms_vec = (t_vec *)malloc(sizeof(t_vec));
	data->input_vec = (t_vec *)malloc(sizeof(t_vec));
	if (!data->rooms_vec || !data->input_vec || !data->flags)
		error(MALLOC_ERR);
	vec_new_arr(data->rooms_vec, start_size);
	vec_new_arr(data->input_vec, start_size);
	data->flags->moves = false;
	data->flags->paths = false;
}

void	read_flags(t_data *data, int argc, char **argv)
{
	if (argc == 1)
		return ;
	if (argc > 2)
		error(FLAG_ERR);
	if (!ft_strcmp(argv[1], "-l"))
		data->flags->moves = true;
	else if (!ft_strcmp(argv[1], "-p"))
		data->flags->paths = true;
	else
		error(FLAG_ERR);
}

int	main(int argc, char **argv)
{
	t_data	data;

	init_data_struct(&data);
	read_flags(&data, argc, argv);
	read_ants(&data);
	read_rooms(&data);
	allocate_flow_pointers(&data);
	bfs_driver(&data);
	print_input(&data);
	print_result(&data);
	return (0);
}
