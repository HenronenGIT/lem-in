/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   best_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 23:41:10 by macbook           #+#    #+#             */
/*   Updated: 2022/10/18 23:41:14 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

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
here we take a path, and check how long it will take to send all
ants down the path. It will take (length_of_path + amount_of_ants) moves
to transport all ants from start to finish. We check,
what is the largest result we check it for each path and we choose
the longest one. If the longest one is shorter, than the one we
have saved previously, then it means
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
This function is like a decider, which checks,
if we want to send an ant down the path.
We receive a number of the path i, amount of ants and paths_set.
Basically, we take a path[2].
we check if path[1] is shorter than path[2], than we do
length of path[2] - length of path[1] and save it into "sum"
if path[0] is shorter than path[2] then we do
length of path[2] - length of path[0] and add that to the previous "sum"
then we check, if amount of ants is larger than the sum,
then we can send and down
the path. there's no need to check if path[3] is shorter
than path[2], because
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
This function checks if current set of paths
(the one we have just saved and sorted)
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
based on the length of them and we always
want to send an ant down the shortest path.
then second shortest and then we check the longest path.
we might end up with something like this
if amount of ants is 15
[8, 5, 2]
so we send 8 ants down the first path, 5 ants down the second path
2 ants down the third path
after we have "sent" all ants, we check, if this solution is better
than previous in check_longest_move
*/

void	check_if_current_is_best(t_data *data, t_set *paths_set, size_t i)
{
	size_t	ants;
	size_t	*ants_to_path;

	ants = data->ants;
	ants_to_path = (size_t *)malloc(sizeof(size_t) * paths_set->paths_amount);
	if (!ants_to_path)
		error(MALLOC_ERR);
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
	free(ants_to_path);
}

void	best_paths_set_operations(t_data *data)
{
	t_set	*paths_set;

	build_paths_set_structure(data, &paths_set);
	calculate_paths_lengths(data, paths_set);
	allocate_paths_arrays(paths_set);
	save_current_paths_set(data, paths_set);
	sort_paths_short_to_long(paths_set, 0, 0);
	check_if_current_is_best(data, paths_set, 0);
}
