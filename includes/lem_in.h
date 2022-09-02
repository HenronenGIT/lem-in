w/* ************************************************************************** */
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

# include <stdio.h>
// # include "../libftprintf/includes/ft_printf.h"
# include "../libft/includes/libft.h" // hmaronen library //? temp

typedef struct	s_vector
{
	char	**rooms;
	
}				t_vector

typedef struct s_data
{
	unsigned long	ants;

}					t_data;

void	read_ants(t_data *data);


#endif
