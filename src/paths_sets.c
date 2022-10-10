/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_sets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 22:18:11 by macbook           #+#    #+#             */
/*   Updated: 2022/10/10 22:18:14 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
Here we calculate how many paths there is in total after each bfs, based on the amount
of flows going from start node. Then we allocate paths_set structure and allocate
an array of arrays of room pointers. To clarify - each path is represented as an array
of pointers to rooms. And we create an array of arrays, so we can keep all paths in the same
unit. For example [[1, 2, 3], [4, 8, 12, 7], [6, 11]].
Also, we create an array called lengths, where lengths[0] is length of paths[0]. And length
of lengths array is the same as amount of paths. If we use previous example, lengths array will
be this: [3, 4, 2]. But for now we don't know how long each path is, so we don't allocate those.
We just know how many paths in total there is.
*/
void	build_paths_set_structure(t_data *data, t_set **paths_set)
{
	size_t	i;

	i = 0;
	*paths_set = (t_set *)malloc(sizeof(t_set));
	(*paths_set)->paths_amount = 0;
	while (data->start->flow[i])
	{
		(*paths_set)->paths_amount++;
		i++;
	}
	if ((*paths_set)->paths_amount != 0)
	{
		(*paths_set)->paths = (t_room ***)malloc(sizeof(t_room **) * i);
		(*paths_set)->lengths = (size_t *)malloc(sizeof(size_t) * i);
		if (!(*paths_set)->paths || !(*paths_set)->lengths)
			error(MALLOC_ERR);
		i = 0;
		while (i < (*paths_set)->paths_amount)
		{
			(*paths_set)->paths[i] = NULL;
			(*paths_set)->lengths[i++] = 0;
		}
	}
}

/*
Here we calculate length of each path and save length to appropriate index
in the lengths array
*/
void	calculate_paths_lengths(t_data *data, t_set *set)
{
	size_t	i;
	size_t	length;
	t_room	*iterator;

	i = 0;
	while (data->start->flow[i])
	{
		length = 1;
		iterator = data->start->flow[i];
		while (iterator->flow[0] != data->end)
		{
			iterator = iterator->flow[0];
			length++;
		}
		set->lengths[i] = length;
		i++;
	}
}


/*
Here we allocate array for each path, using the information
we have collected earlier (lengths)
*/
void	allocate_paths_arrays(t_set *paths_set)
{
	size_t	i;

	i = 0;
	while (i < paths_set->paths_amount)
	{
		paths_set->paths[i] = (t_room **)malloc(sizeof(t_room *) * paths_set->lengths[i]);
		if (!paths_set->paths[i])
			error(MALLOC_ERR);
		i++;
	}
}

/*
Just a function to print sets of paths and length of each path
*/
void	print_paths_set(t_data *data, t_set *paths_set, size_t times)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	printf("\033[0;32mBest set of path after %zu BFSs\033[0m\n", times);
	while (i < paths_set->paths_amount)
	{
		printf("PATH [%zu] = %s -> ", i + 1, data->start->room_name);
		while (j < paths_set->lengths[i])
		{
			printf("%s -> ", paths_set->paths[i][j]->room_name);
			j++;
		}
		printf("%s", data->end->room_name);
		printf("length = %zu", paths_set->lengths[i]);
		printf("\n");
		j = 0;
		i++;
	}
	printf("\n");
}


/*
After everything has been allocated we recreate each path and
save it to array. Array just stores pointers to the room,
so we just play with addresses here
*/
void	save_current_paths_set(t_data *data, t_set *paths_set)
{
	size_t	i;
	size_t	j;
	t_room	*path_room;

	i = 0;
	j = 0;
	while (data->start->flow[i])
	{
		path_room = data->start->flow[i];
		while(path_room != data->end)
		{
			paths_set->paths[i][j] = path_room;
			path_room = path_room->flow[0];
			j++;
		}
		j = 0;
		i++;
	}
}

/*
So if we take previous example [[1, 2, 3], [4, 8, 12, 7], [6, 11]], we can see that
paths have different lengths and they are not sorted. We also have our second array, where we
have lengths saved. We use that array to compare lengths and sort array.
for example [3, 4, 2]
we know, that we need to swap 4 and 2, so we swap the numbers, and using the same indexes we swap
arrays in the array of arrays
so it results in
[3, 2, 4]
[[1, 2, 3], [6, 11], [4, 8, 12, 7]]
again we can swap 2 and 3, so process repeats until it's sorted
this is very raw function and it should be improved, but it works for now
*/
void	sort_paths_short_to_long(t_set *paths_set)
{
	size_t	i;
	size_t	j;
	size_t	tmp_length;
	t_room	**tmp_node;

	i = 0;
	j = 0;
	while (i < paths_set->paths_amount)
	{
		while (j + i < paths_set->paths_amount)
		{
			if (paths_set->lengths[i + j] < paths_set->lengths[i])
			{
				tmp_length = paths_set->lengths[i];
				paths_set->lengths[i] = paths_set->lengths[i + j];
				paths_set->lengths[i + j] = tmp_length;
				tmp_node = paths_set->paths[i];
				paths_set->paths[i] = paths_set->paths[i + j];
				paths_set->paths[i + j] = tmp_node;
				i = 0; //SHOULD BE IMPROVED
				j = -1;
			}
			j++;
		}
		i++;
		j = 0;
	}
}

/*
Okay it's very late and i don't have energy to explain three next functions, but
please check "Step X" here:
https://github.com/VBrazhnik/Lem_in/wiki/Algorithm
It is explained there, how the calculation is done. we can the discuss
later the implementation or i'll do another commit with explanation.
Next 3 functions are just doing that
*/
bool	can_send_this_path(t_set *paths_set, size_t i, size_t ants)
{
	int	j;
	int		sum;

	if (i == 0)
		return (true);
	j = i - 1;
	sum = 0;
	while (j >= 0)
	{
		if (paths_set->lengths[j] < paths_set->lengths[i])
			sum += paths_set->lengths[i] - paths_set->lengths[j];
		j--;
	}
	if (ants > sum)
		return (true);
	return (false);
}

void	check_longest_move(t_data *data, t_set *paths_set, size_t *ants_to_path)
{
	size_t	longest_move;
	size_t	i;

	longest_move = 0;
	i = 0;
	while (i < paths_set->paths_amount)
	{
		if (ants_to_path[i] + paths_set->lengths[i] > longest_move)
			longest_move = ants_to_path[i] + paths_set->lengths[i];
		i++;
	}
	if (longest_move < data->best_speed || !data->best_set)
	{
		data->best_set = paths_set;
		data->best_speed = longest_move;
	}
}

void	check_if_current_is_best(t_data *data, t_set *paths_set)
{
	size_t	ants;
	size_t	*ants_to_path;
	size_t	i;

	ants = data->ants;
	ants_to_path = (size_t *)malloc(sizeof(size_t) * paths_set->paths_amount);
	if (!ants_to_path)
		error(MALLOC_ERR);
	i = 0;
	while (i < paths_set->paths_amount)
		ants_to_path[i++] = 0;
	while (ants)
	{
		i = 0;
		while (i < paths_set->paths_amount)
		{
			if (can_send_this_path(paths_set, i, ants))
			{
				ants_to_path[i]++;
				ants--;
			}
			i++;
		}
	}
	check_longest_move(data, paths_set, ants_to_path);
}

/*
This is a driver function, see other functions for descriptions. Just follow the file
from top to bottom and read the description and it should make sense, because this
driver function is very straightforward :)
*/
void	best_paths_set_operations(t_data *data, size_t bfs_times)
{
	t_set	*paths_set;

	build_paths_set_structure(data, &paths_set);
	calculate_paths_lengths(data, paths_set);
	allocate_paths_arrays(paths_set);
	save_current_paths_set(data, paths_set);
	sort_paths_short_to_long(paths_set);
	check_if_current_is_best(data, paths_set);
	print_paths_set(data, data->best_set, bfs_times);
}
