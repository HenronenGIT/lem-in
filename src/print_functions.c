/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:49:01 by hmaronen          #+#    #+#             */
/*   Updated: 2022/10/18 12:49:02 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	print_links_body(t_room *tmp_room)
{
	size_t	j;

	while (tmp_room)
	{
		j = 0;
		ft_printf("%5s: ", tmp_room->room_name);
		if (tmp_room->links_vec)
		{
			while (j < tmp_room->links_vec->space_taken)
			{
				ft_printf("-> %5s ",
					((t_room **)tmp_room->links_vec->array)[j]->room_name);
				j++;
			}
		}
		tmp_room = tmp_room->next;
		ft_printf("\n");
	}
}

void	print_links(t_data data)
{
	size_t	i;
	t_room	*tmp_room;

	i = 0;
	while (i < data.rooms_vec->length)
	{
		if (data.rooms_vec->array[i])
		{
			tmp_room = data.rooms_vec->array[i];
			print_links_body(tmp_room);
		}
		i++;
	}
}

void	print_paths(t_data *data)
{
	t_room	*iterator;
	size_t	i;
	size_t	path;

	path = 1;
	i = 0;
	ft_printf("\033[0;32mSet of all POSSIBLE paths, after all BFSs\033[0m\n");
	while (data->start->flow[i])
	{
		ft_printf("PATH [%zu] = ", path++);
		ft_printf("%s -> ", data->start->room_name);
		iterator = data->start->flow[i];
		while (iterator != data->end)
		{
			ft_printf("%s -> ", iterator->room_name);
			iterator = *iterator->flow;
		}
		ft_printf("%s\n", iterator->room_name);
		i += 1;
	}
	ft_printf("\n");
}

/*
Just a function to print sets of paths and length of each path
*/
void	print_paths_set(t_data *data, t_set *paths_set)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	ft_printf("\033[0;32mOur Algo chose paths: \033[0m\n");
	while (i < paths_set->paths_amount)
	{
		ft_printf("PATH [%zu] = %s -> ", i + 1, data->start->room_name);
		while (j < paths_set->lengths[i])
		{
			ft_printf("%s -> ", paths_set->paths[i][j]->room_name);
			j++;
		}
		ft_printf("%s", data->end->room_name);
		ft_printf(" length = %zu", paths_set->lengths[i]);
		ft_printf("\n");
		j = 0;
		i++;
	}
	ft_printf("\n");
}
