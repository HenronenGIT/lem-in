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
Next 3 functions are connected, so here's the order how to read the
manual:
check_if_current_is best
can_send_this_path
check_longest_move
*/


void	free_paths_set(t_set *paths_set)
{
	size_t	i;

	i = 0;
	while (i < paths_set->paths_amount)
		free(paths_set->paths[i++]);
	free(paths_set->paths);
	free(paths_set->lengths);
	free(paths_set);
}

/*
here we take a path, and check how long it will take to send all ants down the path.
i came up with formula, that it will take (length_of_path + amount_of_ants) moves
to transport all ants from start to finish. We check, what is the largest result
we check it for each path and we choose the longest one.
if the longest one is shorter, than the one we have saved previously, then it means
that we can send all ants faster using this set of paths.
*/
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
		if (data->best_set)
			free_paths_set(data->best_set);
		data->best_set = paths_set;
		data->best_speed = longest_move;
	}
	else
		free_paths_set(paths_set);
}

/*
This function is like a decider, which checks, if we want to send an ant down the path.
We receive a number of the path i, amount of ants and paths_set.
Go thorugh Step X here:
https://github.com/VBrazhnik/Lem_in/wiki/Algorithm
to understand, what is going on.
Basically, we take a path[2].
we check if path[1] is shorter than path[2], than we do
length of path[2] - length of path[1] and save it into "sum"
if path[0] is shorter than path[2] then we do
length of path[2] - length of path[0] and add that to the previous "sum"
then we check, if amount of ants is larger than the sum, then we can send and down
the path. there's no need to check if path[3] is shorter than path[2], because
paths are sorted and only paths on the left are potentially shorter.
*/
bool	can_send_this_path(t_set *paths_set, size_t i, size_t ants)
{
	int		j;
	size_t	sum;

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

/*
This function checks if current set of paths (the one we have just saved and sorted)
is better, than the one we have saved in data->best_set.
To do so, here we create and array, as long as there are paths.
Let's base this example on the previsous one.
So we have 3 paths [0, 0, 0], where 0 is the amount of ants we are
going to send down the path[0], path[1] and path[2].
if can_send_this_path returns true, we send one ant down the path
for instance [1, 0, 0] and we make amount of ants 1 smaller.
first we check if we want to send ant down the first path, then the second,
then the third. We keep looping like this as long as we have ants.
we always check starting from first path, because we have sorted the paths
based on the length of them and we always want to send an ant down the shortest path.
then second shortest and then we check the longest path.
we might end up with something like this
if amount of ants is 15
[8, 5, 2]
so we send 8 ants down the first path, 5 ants down the second path
2 ants down the third path
after we have "sent" all ants, we check, if this solution is better
than previous in check_longest_move
*/

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
	free(ants_to_path);
	check_longest_move(data, paths_set, ants_to_path);
}

/*
This is a driver function, see other functions for descriptions. Just follow the file
from top to bottom and read the description and it should make sense, because this
driver function is very straightforward :)

NOTE:
!!!Solution is not yet perfect and it's leaking!!!
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
	// print_paths_set(data, data->best_set, bfs_times);
}
