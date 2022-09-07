/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:45:31 by hmaronen          #+#    #+#             */
/*   Updated: 2022/09/05 16:45:32 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	read_ants(t_data *data)
{
	char	*line;
	long	ant_count;

	line = NULL;
	ant_count = 0;
	get_next_line(0, &line);
	if (!ft_isnumber(line))
		error(INPUT_ERR);
	if (!line)
		error(INPUT_ERR);
	ant_count = ft_atoi(line); //! Change to "atou" - unsigned long.
	if (ant_count <= 0) //? Is 0 ant count error?
		error(INPUT_ERR);
	data->ants = ant_count;
	free(line);
}

void	read_rooms(t_data *data)
{
	char	*line;

	while (get_next_line(0, &line) && !ft_strchr(line,'-'))
	{
		if (line && *line == '#')
			read_hashtag(data, line);
		else if ((line && *line == 'L'))
			error(FORMAT_ERR);
		else
			read_room_name(data, line, NORMAL);
		free(line);
	}
	if (ft_strchr(line, '-'))
	{
		read_links(data, line);
		free(line);
	}
	while (get_next_line(0, &line))
	{
		if (*line != '#')
		{
			if (ft_strchr(line, '-'))
				read_links(data, line);
		}
		free(line);
	}
}

// int	read_hashtag(t_data *data, char *line)
void	read_hashtag(t_data *data, char *line) //? Testing with void return value
{
	char *test;

	test = NULL;
	if (!ft_strcmp("##start", line))
	{
		get_next_line(0, &test);
		read_room_name(data, test, START);
	}
	else if (!ft_strcmp("##end", line))
	{
		get_next_line(0, &test);
		read_room_name(data, test, END);
	}
	else if (*line == '#' && line[1] != '#')
		return ;
	else
		error(FORMAT_ERR);
		//? One more else if() might need to be added for checking if hashtag was comment.
		//? In that case just return.
}

void	read_room_name(t_data *data, char *line, int decider)
{
	int		i;
	char	*name;
	int		hash;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	name = ft_strsub(line, 0, i);
	vec_insert(&(data->rooms_vec), name);
	if (decider == START)
		data->start = name;
	if (decider == END)
		data->end = name;
}
