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

# define MALLOC_ERR -2
# define NULL_ERR -3
# define FORMAT_ERR -4
# define INPUT_ERR -5
# define NO_PATH -6
# define LINK_ERR -7
# define ANT_ERR -8

# define START 1
# define END 2
# define NORMAL 3

// const static bool start_found = false;

/* Linked list structure for BFS */
typedef struct s_queue
{
	struct s_room	*room;
	struct s_queue	*next;
}	t_queue;

/* Main structure which contains all the data */
typedef struct s_data
{
	unsigned long	ants;
	struct s_vec	*rooms_vec;
	struct s_room	*start;
	struct s_room	*end;
}	t_data;

/* General Dynamic Vector structure */
typedef struct s_vec
{
	void	 		**array;
	size_t			length;
	size_t			space_left;
	size_t			space_taken;
}	t_vec;

typedef struct s_room
{
	char			*room_name;
	struct s_coords	*coords;
	struct s_vec	*links_vec;
	struct s_room	*parent;//? change name to "no_flow_parent" or similar
	struct s_room	*flow_parent;
	struct s_room	*next;
	struct s_room	**flow; //? rename later to flows. need to be double pointer because start room will have multiple flows.
	struct s_room	*flow_from;
}	t_room;

typedef struct s_coords
{
	long x;
	long y;
} t_coords;

void	error(int error_number);

/*----------PARSING-----------*/
void	read_ants(t_data *data);
void	read_rooms(t_data *data);
void	read_room_info(t_data *data, char *line, int decider);
// void	read_room_name(t_data *data, char *line, int decider);
void	read_hashtag(t_data *data, char *line); //? Testing with void return value
void	read_command(t_data *data, char *line);
void	read_start(t_data *data, char *line);
void	read_end(t_data *data, char *line);
void	read_links(t_data *data, char *line);

/*----------VECTOR------------*/
void	vec_new_arr(t_vec *dst, size_t len);
void	vec_resize(t_vec *src);
// void	vec_insert(t_vec *dst, char *name);
void	vec_insert(t_vec *dst, char *name, t_coords *coordinates);
void	vec_allocate_element(t_vec *dst, size_t i);
void	vec_link_insert(t_room *room_1, t_room *room_2);
void	vec_resize_links(t_room *room);

/*----------HASH--------------*/
void			sort_hash_values(t_data *data);
unsigned long	hashing(t_data *data, char *name);

/*----------BFS--------------*/
int		bfs(t_data *data, t_queue **head);
void	bfs_driver(t_data *data);
int		positive_flow(t_room **flows, t_room *link);
void	allocate_flow_pointers(t_data *data);
void add_to_que(t_queue **tail, t_room *link);
void found_old_path(t_queue **tail, t_queue *que);
void visit_using_unused_edge(t_queue **tail, t_queue *que, t_room *link);
void can_go_everywhere(t_room *current, t_room *link, t_queue **tail);

/*------SETTING FLOWS--------*/
void set_flows(t_data *data);
void allocate_flow_pointer(t_data *data, t_room *current);

#endif
