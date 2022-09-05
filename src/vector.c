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
	size_t	i;

	i = 0;
	free((*array)->room_names);
	if (*array)
		free(*array);
}

void	vec_copy(t_vec **src, t_vec *dst)
{
	size_t	i;

	if (!*src || !dst)
		error(-3);
	i = 0;
	while (i < (*src)->length)
	{
		dst->room_names[i] = (*src)->room_names[i];
		i++;
	}
	dst->space_taken = i;
	dst->space_left = dst->length - dst->space_taken;
}

void	vec_resize(t_vec **src)
{
	t_vec *dst;

	if (!*src)
		error(-3);
	dst = (t_vec *)malloc(sizeof(t_vec));
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
	(*dst)->room_names[(*dst)->space_taken] = name;
	(*dst)->space_taken++;
	(*dst)->space_left--;
}

void	vec_new(t_vec *dst, size_t len)
{
	size_t	i;

	i = 0;
	if (!dst || len == 0)
		error(-3);
	dst->length = len;
	dst->space_taken = 0;
	dst->space_left = len;
	dst->room_names = (char **)malloc(sizeof(char *) * (len + 1));
	if (!dst->room_names)
		error(MALLOC_ERR);
	while (i < len + 1)
	{
		dst->room_names[i] = NULL;
		i++;
	}
}
