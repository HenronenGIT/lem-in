/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:18:53 by hmaronen          #+#    #+#             */
/*   Updated: 2022/10/28 10:18:55 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int	is_comment(char *str)
{
	if (str[0] == '#' && str[1] != '#')
		return (1);
	return (0);
}

int	is_unknown_command(char *line)
{
	if (line[0] != '#' && line[1] != '#')
		return (0);
	if (is_comment(line))
		return (0);
	if (!ft_strcmp(line, "##start"))
		return (0);
	if (!ft_strcmp(line, "##end"))
		return (0);
	return (1);
}

void	skip_comments(t_data *data, char **line)
{
	get_next_line(0, line);
	while (is_comment(*line))
	{
		vec_insert(data->input_vec, *line);
		get_next_line(0, line);
	}
}

void	skip_unknown_commads(t_data *data, char **line)
{
	if (!line)
		get_next_line(0, line);
	while (is_unknown_command(*line))
	{
		vec_insert(data->input_vec, *line);
		get_next_line(0, line);
	}
}
