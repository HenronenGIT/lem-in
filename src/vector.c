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

int	vec_new(t_vec *dst, size_t len)
{
	if (!dst || len == 0)
		return (-1);
	dst->length = len;
	dst->space_taken = 1;
	dst->space_left = len - dst->space_taken;
	dst->room_names = (char **)malloc(sizeof(char *) * (len + 1));

}