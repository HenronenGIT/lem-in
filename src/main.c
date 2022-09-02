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

void	build_room_arr(t_data *data, char *name)
{
	vec_insert(&(data->rooms), name);
}

void	read_room_name(t_data *data, char *line)
{
	int		i;
	char	*name;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	name = ft_strsub(line, 0, i);
	build_room_arr(data, name);
}

// int	read_comment(t_data *data, char *line)
// {
// 	if (ft_strncmp("##start", line, 7))
// 		read_start(data, line);
// 	else if (ft_strncmp("##end", line, 5))
// 		read_end(data, line);
// 	else
// 		return (1);
// }

void	read_rooms(t_data *data)
{
	char	*line;

	while (get_next_line(0, &line))
	{
		// if (line && *line == '#')
		// {
		// 	if (read_comment(data, line))
		// 		return (-1);
		// }
		// else
		read_room_name(data, line);
	}
}

void	error(int error_number)
{
	if (error_number == 1)
		ft_puterror("Invalid ant input!\n");
	if (error_number == MALLOC_ERR)
		ft_puterror("Not enough space for malloc");
	exit (error_number);
}

void	read_ants(t_data *data)
{
	char	*line;
	long	ant_count;

	line = NULL;
	ant_count = 0;
	get_next_line(0, &line);
	if (!ft_isnumber(line))
		error(1);
	if (!line)
		error(1);
	ant_count = ft_atoi(line); //! Change to "atou" - unsigned long.
	if (ant_count <= 0) //? Is 0 ant count error?
		error(1);
	data->ants = ant_count;
	free(line);
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
	// init_struct(&data);
	// read_ants();
	// read_rooms();
	// read_links();
	size_t i = 0;
	while (i < data.rooms->length)
	{
		printf("%s\n", data.rooms->room_names[i]);
		i++;
	}
	system("leaks lem-in");
	return (0);
}