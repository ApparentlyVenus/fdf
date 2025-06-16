/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:33:14 by odana             #+#    #+#             */
/*   Updated: 2025/06/15 17:02:52 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"
#include "../lib/inc/libft.h"
#include "../lib/inc/get_next_line.h"

int	count_cols(char *line)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (line[i])
	{
		while (line[i] && (line[i] == ' '))
			i++;
		if (line[i])
		{
			count++;
			while (line[i] && line[i] != ' ')
				i++;
		}
	}
	return (count);
}

int	count_rows(char *file)
{
	int		rows;
	int		fd;
	char	c;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		free_exit(fd, NULL, "error openning file");
	rows = 0;
	while (read(fd, &c, 1) == 1)
	{
		if (c == '\n')
			rows++;
	}
	if (rows == 0)
		free_exit(fd, NULL, "format error");
	close(fd);
	return (rows);
}
