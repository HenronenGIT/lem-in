/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:43:02 by macbook           #+#    #+#             */
/*   Updated: 2022/10/11 17:43:06 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	check_if_move_end(t_data *data, t_room **ants, size_t *ant_num, size_t *finished)
{
	if (ants[*ant_num] != data->end)
		ants[*ant_num]->occupied = true;
	else
	{
		*finished += 1;
		return ;
	}
	ft_printf("L%lu-%s ", *ant_num + 1, ants[*ant_num]->room_name);
}

void	send_from_start(t_data *data, t_room **ants, size_t *ant_num, size_t *finished)
{
	size_t	i;

	i = 0;
	while (i < data->best_set->paths_amount)
	{
		if (!data->start->flow[i]->occupied && can_send_this_path(data->best_set, i, data->ants - *finished))
		{
			ants[*ant_num] = data->start->flow[i];
			check_if_move_end(data, ants, ant_num, finished);
			return ;
		}
		i++;
	}
}

void	print_result(t_data *data)
{
	t_room	**ants;
	size_t	finished;
	size_t	ant_num;

	ant_num = 0;
	ants = (t_room **)malloc(sizeof(t_room) * data->ants);
	if (!ants)
		error(MALLOC_ERR);
	finished = 0;
	while (ant_num < data->ants)
		ants[ant_num++] = data->start;
	while (finished != data->ants)
	{
		ant_num = 0;
		while (ant_num < data->ants)
		{
			if (ants[ant_num] == data->start)
				send_from_start(data, ants, &ant_num, &finished);
			else if (ants[ant_num] != data->end)
			{
				ants[ant_num]->occupied = false;
				ants[ant_num] = ants[ant_num]->flow[0];
				check_if_move_end(data, ants, &ant_num, &finished);
			}
			ant_num++;
		}
		printf("\n");
	}
}