/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 07:34:31 by odana             #+#    #+#             */
/*   Updated: 2025/06/17 09:57:33 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"
#include "../lib/inc/libft.h"

static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[0] == '-' || str[0] == '+')
		i = 1;
	if (!str[i])
		return (0);
	while (str[i] && str[i] != ',')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	count_split(char **split)
{
	int	count;

	count = 0;
	if (!split)
		return (0);
	while (split[count])
		count++;
	return (count);
}

static int	validate_first_row(char **lines, int *expected_width)
{
	char	**split;
	int		j;

	if (!lines || !lines[0])
		return (0);
	split = ft_split(lines[0], ' ');
	if (!split)
		return (0);
	*expected_width = count_split(split);
	if (*expected_width <= 0)
	{
		free_split(split);
		return (0);
	}
	j = 0;
	while (split[j])
	{
		if (!is_valid_number(split[j++]))
		{
			free_split(split);
			return (0);
		}
	}
	free_split(split);
	return (1);
}

static int	validate_row_elements(char *line, int expected_width)
{
	char	**split;
	int		j;
	int		current_width;

	split = ft_split(line, ' ');
	if (!split)
		return (0);
	current_width = count_split(split);
	if (current_width != expected_width)
	{
		free_split(split);
		return (0);
	}
	j = 0;
	while (split[j])
	{
		if (!is_valid_number(split[j]))
		{
			free_split(split);
			return (0);
		}
		j++;
	}
	free_split(split);
	return (1);
}

int	validate_fdf_map(char **lines)
{
	int		i;
	int		expected_width;

	if (!validate_first_row(lines, &expected_width))
		return (0);
	i = 1;
	while (lines[i])
	{
		if (!validate_row_elements(lines[i], expected_width))
			return (0);
		i++;
	}
	return (1);
}
