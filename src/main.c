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
#include <fcntl.h>

int main(void)
{
	t_data	data;
	char	*string;
	char	*found;

	data.file_desc = open("example.txt", O_RDONLY);
	get_next_line(data.file_desc, &string);
	ft_printf("%s\n", string);
	found = ft_strstr(string, "0");
	ft_printf("%s\n", found);
	return (0);
}