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

# include <stdio.h>
// # include "../libftprintf/includes/ft_printf.h"
# include "../libft/includes/libft.h" // hmaronen library //? temp

# define MALLOC_ERR -2
# define FORMAT_ERR -4

# define START 1
# define END 2
# define NORMAL 3

typedef struct s_room
{
	char			*room_name;
	struct s_room	*next;
}	t_room;

typedef struct s_vec
{
	struct s_room	**rooms;
	size_t			length;
	size_t			space_left;
	size_t			space_taken;
}	t_vec;

typedef struct s_data
{
	unsigned long	ants;
	struct s_vec	*rooms;

	char			*start;
	char			*end;

	// struct s_room	*start;
	// struct s_room	*end;
	
	struct s_vec	*rooms_vec;
}	t_data;

void	error(int error_number);

/*----------PARSING-----------*/
void	read_ants(t_data *data);
void	read_rooms(t_data *data);
void	read_room_name(t_data *data, char *line, int decider);
int		read_hashtag(t_data *data, char *line);
void	read_command(t_data *data, char *line);
void	read_start(t_data *data, char *line);
void	read_end(t_data *data, char *line);
	

/*----------VECTOR------------*/
void	vec_new(t_vec *dst, size_t len);
void	vec_insert(t_vec **dst, char *name);


#endif
