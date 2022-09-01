/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:40:56 by igaplich          #+#    #+#             */
/*   Updated: 2022/08/22 15:43:11 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libftprintf/includes/ft_printf.h"

typedef struct s_rooms
{
	char			*name;
	struct s_rooms	*next;
}	t_rooms;

typedef struct s_data
{
	unsigned long	ants;
	struct s_rooms	*head;
	struct s_rooms	*tail;
	struct s_rooms	*start;
	struct s_rooms	*end;
}					t_data;

#endif
