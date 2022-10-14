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
# include <stdbool.h>
# include "../libft/includes/libft.h"

/* Error message code */
# define MALLOC_ERR -2
# define NULL_ERR -3
# define FORMAT_ERR -4
# define NO_PATH -5
# define LINK_ERR -6
# define ANT_ERR -7

/* Main structure which contains all the data */
typedef struct s_data
{
	long			ants;
	struct s_vec	*rooms_vec;
	struct s_vec	*input_vec;
	struct s_room	*start;
	struct s_room	*end;
	struct s_set	*best_set;
	size_t			best_speed;
}	t_data;

/* General Dynamic Vector structure */
typedef struct s_vec
{
	void			**array;
	size_t			length;
	size_t			space_left;
	size_t			space_taken;
}	t_vec;

typedef struct s_set
{
	struct s_room	***paths;
	size_t			*lengths;
	size_t			paths_amount;
}	t_set;

typedef struct s_room
{
	char			*room_name;
	struct s_coords	*coords;
	struct s_vec	*links_vec;
	struct s_room	*parent;
	struct s_room	*flow_parent;
	struct s_room	*next;
	struct s_room	**flow;
	struct s_room	*flow_from;
	bool			occupied;
}	t_room;
/* Linked list structure for BFS */
typedef struct s_queue
 {
	struct s_room	*room;
	struct s_queue	*next;
}	t_queue;

typedef struct s_coords
{
	long	x;
	long	y;
}		t_coords;

void	error(int error_number);

/*----------PARSING-----------*/
void	read_ants(t_data *data);
void	read_rooms(t_data *data);
void	read_links(t_data *data, char *line);
t_room	*allocate_new_room(char *room_name, t_coords *coords);

/*----------VECTOR------------*/
void	vec_new_arr(t_vec *dst, size_t len);
void	vec_resize(t_vec *src);
void	vec_insert(t_vec *dst_vec, void *element);

/*----------HASH--------------*/
void	sort_hash_values(t_data *data);
unsigned long	hashing(t_data *data, char *name);

/*----------BFS--------------*/
void	bfs_driver(t_data *data);
int		positive_flow(t_room **flows, t_room *link);
void	allocate_flow_pointers(t_data *data);
void	add_to_que(t_queue **tail, t_room *link);
void	found_old_path(t_queue **tail, t_queue *que);
void	visit_using_unused_edge(t_queue **tail, t_queue *que, t_room *link);
void	can_go_everywhere(t_room *current, t_room *link, t_queue **tail);

/*------SETTING FLOWS--------*/
void	set_flows(t_data *data);
void	allocate_flow_pointer(t_data *data, t_room *current);

/*------SEARCHING BEST PATHS SET--------*/
void	best_paths_set_operations(t_data *data);
bool	can_send_this_path(t_set *paths_set, size_t i, size_t ants);

/*------RESULT OUTPUT-------------*/
void	print_result(t_data *data);
void	print_paths(t_data *data);
void	set_correct_flows(t_data *data);
void	print_paths_set(t_data *data, t_set *paths_set, size_t times);

/*------PRINTING-------------*/
void	print_paths(t_data *data);

#endif
