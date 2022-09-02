/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:37:29 by igaplich          #+#    #+#             */
/*   Updated: 2022/08/22 15:37:31 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	error(int error_number)
{
	if (error_number == 1)
		ft_puterror("Invalid ant input!\n");
		// perror("Invalid ant input!");
	exit (1);
}

void	read_ants(t_data *data)
{
	char	*line;

	line = NULL;
	get_next_line(0, &line);
	if (!ft_isnumber(line))
		error(1);
	if (!line)
		error(1);
	data->ants = ft_atoi(line); //! Change to "atou" - unsigned long.
	free(line);
}

int main(void)
{
	t_data	data;

	// init_struct(&data);
	read_ants(&data);
	// read_rooms();asdas
	// read_links();

	return (0);
}