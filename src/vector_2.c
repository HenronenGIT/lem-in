/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:24:05 by hmaronen          #+#    #+#             */
/*   Updated: 2022/09/07 15:24:06 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	vec_allocate_rooms(t_vec *dst, size_t i)
{
	size_t	j;

	dst->rooms[i] = (t_room *)malloc(sizeof(t_room));
	if (!dst->rooms[i])
		error(MALLOC_ERR);
	dst->rooms[i]->next = NULL;
	dst->rooms[i]->links_vec = (t_links *)malloc(sizeof(t_links));
	if (!dst->rooms[i]->links_vec)
		error(MALLOC_ERR);
	dst->rooms[i]->links_vec->link_ptr = (t_room **)malloc(sizeof(t_room *) * 3);
	if (!dst->rooms[i]->links_vec->link_ptr)
		error(MALLOC_ERR);
	j = 0;
	while (j < 3)
	{
		dst->rooms[i]->links_vec->link_ptr[j] = NULL;
		j++;
	}
	dst->rooms[i]->links_vec->length = 3;
	dst->rooms[i]->links_vec->space_taken = 0;
	dst->rooms[i]->links_vec->space_left = 3;
}
