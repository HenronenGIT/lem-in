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
	if (!data->head)
	{
		data->head = (t_rooms *)malloc(sizeof(t_rooms));
		data->tail = data->head;
		data->head->next = NULL;
	}
	else
	{
		data->tail->next = (t_rooms *)malloc(sizeof(t_rooms));
		data->tail = data->tail->next;
		data->tail->next = NULL;
	}
	data->tail = name;
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

int main(void)
{
	t_data	data;

	read_rooms(&data);
	// init_struct(&data);
	// read_ants();
	// read_rooms();
	// read_links();

	return (0);
}