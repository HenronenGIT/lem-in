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

int	read_rooms(t_data *data)
{
	char	*line;

	while (get_next_line(0, &line))
	{
		if (*line == '#')
		{
			if (read_comment(data, line))
				return (-1);
		}
	}
}

int main(void)
{
	t_data	data;

	read_rooms(&data);
	return (0);
}