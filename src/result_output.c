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

void	check_if_move_end(t_data *data, t_result *res, t_room **ants)
{
	if (ants[res->ant_num] != data->end)
		ants[res->ant_num]->occupied = true;
	else
		res->finished += 1;
	if (res->first_print)
	{
		ft_printf("L%lu-%s", res->ant_num + 1, ants[res->ant_num]->room_name);
		res->first_print = false;
	}
	else
		ft_printf(" L%lu-%s", res->ant_num + 1, ants[res->ant_num]->room_name);
}

void	send_from_start(t_data *data, t_result *res, t_room **ants)
{
	size_t	i;

	i = 0;
	while (i < data->best_set->paths_amount)
	{
		if (!data->start->flow[i]->occupied
			&& can_send_this_path(data->best_set, i, data->ants - res->left))
		{
			res->left += 1;
			ants[res->ant_num] = data->start->flow[i];
			check_if_move_end(data, res, ants);
			return ;
		}
		i++;
	}
}

void	print_moves(t_data *data, t_result *res, t_room **ants)
{
	while (res->finished != data->ants)
	{
		res->ant_num = 0;
		while (res->ant_num < data->ants)
		{
			if (ants[res->ant_num] == data->start)
				send_from_start(data, res, ants);
			else if (ants[res->ant_num] != data->end)
			{
				ants[res->ant_num]->occupied = false;
				ants[res->ant_num] = ants[res->ant_num]->flow[0];
				check_if_move_end(data, res, ants);
			}
			res->ant_num++;
		}
		ft_printf("\n");
		res->first_print = true;
		res->moves++;
	}
}

void	print_result(t_data *data)
{
	t_room		**ants;
	t_result	res;

	set_correct_flows(data);
	init_res_data_and_ants_arr(&res, &ants, data);
	print_moves(data, &res, ants);
	free(ants);
	if (data->flags->moves == true)
		ft_printf("\033[0;32mMove count:\n\033[0m%zu\n", res.moves);
}
