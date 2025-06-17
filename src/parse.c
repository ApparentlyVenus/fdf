/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:54:02 by odana             #+#    #+#             */
/*   Updated: 2025/06/17 08:42:44 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"
#include "../lib/inc/libft.h"
#include "../lib/inc/get_next_line.h"

static void	cleanup_line(char *line)
{
	int	i;
	int	len;

	if (!line)
		return ;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			line[i] = ' ';
		i++;
	}
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

void	free_lines(char **lines)
{
	int	i;

	if (!lines)
		return ;
	i = 0;
	while (lines[i])
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

void	free_exit(int fd, char **lines, char *msg)
{
	perror(msg);
	free_lines(lines);
	close(fd);
	exit(EXIT_FAILURE);
}

static void	cleanup(int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		else
			free(line);
	}
}

char	**extract_lines(char *file)
{
	int		fd;
	char	**lines;
	int		i;
	int		rows;

	rows = count_rows(file);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		free_exit(fd, NULL, "error opening file");
	i = 0;
	lines = (char **)malloc(sizeof(char *) * (rows + 1));
	if (!lines)
		free_exit(fd, NULL, "malloc error");
	while (i < rows)
	{
		lines[i] = get_next_line(fd);
		if (!lines[i])
			break ;
		cleanup_line(lines[i]);
		i++;
	}
	lines[i] = NULL;
	cleanup(fd);
	close(fd);
	return (lines);
}
