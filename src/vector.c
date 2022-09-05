/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 11:09:31 by igaplich          #+#    #+#             */
/*   Updated: 2022/09/02 11:09:33 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	vec_free(t_vec **array)
{
	if (*array)
	{
		if (*array)
		{
			if ((*array)->rooms)
				free((*array)->rooms);
			free(*array);
		}
	}
}

void	vec_copy(t_vec **src, t_vec *dst)
{
	size_t	i;

	if (!*src || !dst)
		error(-3);
	i = 0;
	while (i < (*src)->length)
	{
		dst->rooms[i] = (*src)->rooms[i];
		i++;
	}
	dst->space_taken = i;
	dst->space_left = dst->length - dst->space_taken;
}

void	vec_resize(t_vec **src)
{
	t_vec	*dst;

	if (!*src)
		error(-3);
	dst = (t_vec *)malloc(sizeof(t_vec));
	if (!dst)
		error(MALLOC_ERR);
	vec_new(dst, ((*src)->length * 2) + 1);
	if ((*src)->length != 0)
		vec_copy(src, dst);
	vec_free(src);
	*src = dst;
}

void	vec_insert(t_vec **dst, char *name)
{
	if (!*dst || !name)
		error(-3);
	if ((*dst)->space_left == 0)
		vec_resize(dst);
	(*dst)->rooms[(*dst)->space_taken] = (t_room *)malloc(sizeof(t_room));
	if (!(*dst)->rooms[(*dst)->space_taken])
		error(MALLOC_ERR);
	(*dst)->rooms[(*dst)->space_taken]->room_name = name;
	(*dst)->rooms[(*dst)->space_taken]->next = NULL;
	(*dst)->space_taken++;
	(*dst)->space_left--;
}

void	vec_new(t_vec *dst, size_t len)
{
	size_t	i;

	if (!dst || len == 0)
		error(-3);
	dst->length = len;
	dst->space_taken = 0;
	dst->space_left = len;
	dst->rooms = (t_room **)malloc(sizeof(t_room *) * (len + 1));
	if (!dst->rooms)
		error(MALLOC_ERR);
	i = 0;
	while (i < len + 1)
		dst->rooms[i++] = NULL;
}
