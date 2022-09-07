/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:25:57 by igaplich          #+#    #+#             */
/*   Updated: 2022/09/06 11:25:59 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

size_t	room_compare(t_data *data, char **line)
{
	char	*compare;
	size_t	len;
	size_t	i;

	i = 0;
	compare = NULL;
	while (i < data->rooms_vec->space_taken)
	{
		len = ft_strlen(data->rooms_vec->rooms[i]->room_name);
		if (!ft_strncmp(*line, data->rooms_vec->rooms[i]->room_name, len))
			break;
		i++;
	}
	if (i == data->rooms_vec->space_taken)
		error(FORMAT_ERR);
	*line += len;
	return (i);
}

void	insert_link(t_data *data, size_t first_link, size_t second_link)
{
	// data->rooms_vec->rooms[first_link]->next = (t_room *)malloc(sizeof(t_room));
	// if (!data->rooms_vec->rooms[first_link]->next)
		// error(MALLOC_ERR);
	// data->rooms_vec->rooms[first_link]->next->head = data->rooms_vec->rooms[first_link]->head;
	// data->rooms_vec->rooms[first_link] = data->rooms_vec->rooms[first_link]->next;
	// data->rooms_vec->rooms[first_link]->next = NULL;
	// data->rooms_vec->rooms[first_link]->room_name = data->rooms_vec->rooms[second_link]->head->room_name;
}

void	read_links(t_data *data, char *line)
{
	size_t	first_link;
	size_t	second_link;

	first_link = room_compare(data, &line);
	if (*line != '-')
		error(FORMAT_ERR);
	line++;
	second_link = room_compare(data, &line);
	insert_link(data, first_link, second_link);
}