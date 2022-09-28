/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:33:00 by hmaronen          #+#    #+#             */
/*   Updated: 2022/09/07 15:33:01 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	vec_insert(t_vec *dst, char *name)
{
	if (!dst || !name)
		error(NULL_ERR);
	if (dst->space_left == 0)
		vec_resize(dst);
	vec_allocate_element(dst, dst->space_taken);
	if (!dst->array[dst->space_taken])
		error(MALLOC_ERR);
	((t_room **)(dst->array))[dst->space_taken]->room_name = name;
	dst->space_taken++;
	dst->space_left--;
}

void	vec_allocate_element(t_vec *dst, size_t i)
{
	((t_room **)dst->array)[i] = (void *)malloc(sizeof(t_room));
	if (!dst->array[i])
		error(MALLOC_ERR);
	((t_room **)dst->array)[i]->next = NULL;
	((t_room **)dst->array)[i]->links_vec = NULL;
	((t_room **)dst->array)[i]->flows = NULL;
	((t_room **)dst->array)[i]->visited = 0;
	((t_room **)dst->array)[i]->parent = NULL;
	((t_room **)dst->array)[i]->path_number = 0;
	((t_room **)dst->array)[i]->second_step = 0;
}

static void	vec_free(t_vec *vector)
{
	if (vector)
	{
		if (vector->array)
			free(vector->array);
	}
}

void	vec_copy(t_vec *src, t_vec *dst)
{
	size_t	i;

	if (!src || !dst)
		error(NULL_ERR);
	i = 0;
	while (i < src->length)
	{
		dst->array[i] = src->array[i];
		i++;
	}
	dst->space_taken = i;
	dst->space_left = dst->length - dst->space_taken;
}

void	vec_resize(t_vec *src)
{
	t_vec	dst;

	if (!src)
		error(NULL_ERR);
	vec_new_arr(&dst, (src->length * 2));
	vec_copy(src, &dst);
	vec_free(src);
	*src = dst;
}

void	vec_new_arr(t_vec *dst, size_t len)
{
	size_t	i;

	i = 0;
	if (!dst || len == 0)
		error(NULL_ERR);
	dst->length = len;
	dst->space_taken = 0;
	dst->space_left = len;
	dst->array = (void **)malloc(sizeof(void *) * len);
	if (!dst->array)
		error(MALLOC_ERR);
	while (i < len)
		dst->array[i++] = NULL;
}
