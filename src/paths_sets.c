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
Here we calculate how many paths there is in total after each bfs, based
on the amount of flows going from start node. Then we allocate paths_set
structure and allocate an array of arrays of room pointers. 
For example [[1, 2, 3], [4, 8, 12, 7], [6, 11]].
Also, we create an array called lengths, where lengths[0] is length of
paths[0]. And length of lengths array is the same as amount of paths.
If we use previous example, lengths array will be: 
[3, 4, 2].
But for now we don't know how long each path is, so we don't allocate those.
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
		paths_set->paths[i] = (t_room **)malloc(sizeof(t_room *)
				* paths_set->lengths[i]);
		if (!paths_set->paths[i])
			error(MALLOC_ERR);
		i++;
	}
}

/*
After everything has been allocated we recreate each path and
save it to array. Array just stores pointers to the room
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
		while (path_room != data->end)
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
So if we take previous example
[[1, 2, 3], [4, 8, 12, 7], [6, 11]],
we can see that paths have different lengths and they are not sorted.
We also have our second array,
where we have lengths saved. We use that array to compare lengths and sort array.
for example:
[3, 4, 2]
we know, that we need to swap 4 and 2, so we swap the numbers,
and using the same indexes we swap
arrays in the array of arrays
so it results in
lengths:	[3,			2,			4]
paths:		[[1, 2, 3],	[6, 11],	[4, 8, 12, 7]]
again we can swap 2 and 3, so process repeats until it's sorted
*/
void	sort_paths_short_to_long(t_set *paths_set, size_t i, size_t j)
{
	size_t	tmp_length;
	t_room	**tmp_node;

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
				i = 0;
				j = -1;
			}
			j++;
		}
		i++;
		j = 0;
	}
}
