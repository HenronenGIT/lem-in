/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 00:51:23 by macbook           #+#    #+#             */
/*   Updated: 2022/10/19 00:51:25 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	set_correct_flows(t_data *data)
{
	size_t	i;
	size_t	j;
	t_set	*set;

	i = 0;
	j = 0;
	set = data->best_set;
	while (i < set->paths_amount)
	{
		data->start->flow[i] = set->paths[i][0];
		while (j < set->lengths[i] - 1)
		{
			set->paths[i][j]->flow[0] = set->paths[i][j + 1];
			j++;
		}
		set->paths[i][j]->flow[0] = data->end;
		j = 0;
		i++;
	}
	while (data->start->flow[i])
	{
		data->start->flow[i] = NULL;
		i++;
	}
}

void	init_res_data_and_ants_arr(t_result *res, t_room ***ants, t_data *data)
{
	res->ant_num = 0;
	res->moves = 0;
	res->left = 0;
	res->finished = 0;
	res->first_print = true;
	*ants = (t_room **)malloc(sizeof(t_room) * data->ants);
	if (!*ants)
		error(MALLOC_ERR);
	while (res->ant_num < data->ants)
		(*ants)[res->ant_num++] = data->start;
}
