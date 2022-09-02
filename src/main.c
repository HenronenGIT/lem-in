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

int	build_room_list(t_data *data, char *name)
{
	
}

int	read_room_name(t_data *data, char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	build_room_list(data, ft_strsub(line, 0, i));
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

int	read_rooms(t_data *data)
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
		// perror("Invalid ant input!");
	exit (1);
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

int	init_struct(t_data *data)
{
	
}

int main(void)
{
	t_data	data;
	t_vec	rooms_list;

	// init_struct(&data);
	read_ants(&data);
	read_rooms(&data);
	// init_struct(&data);
	// read_ants();
	// read_rooms();
	// read_links();
	return (0);
}