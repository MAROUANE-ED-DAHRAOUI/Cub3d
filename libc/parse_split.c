/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:56:16 by bbadda            #+#    #+#             */
/*   Updated: 2024/11/24 17:56:28 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	count_word(char *s, char set)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == set && s[i])
			i++;
		if (s[i] != set && s[i])
			count++;
		while (s[i] != set && s[i])
			i++;
	}
	return (count);
}

static int	len_word(char *s, char set, int start)
{
	int	i;

	i = 0;
	while (s[start] && s[start] != set)
	{
		start++;
		i++;
	}
	return (i);
}

static void	free_list(char **list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		free(list[i]);
		list[i] = NULL;
		i++;
	}
	free(list);
	list = NULL;
}

static char	**str_alloc(char const *s, char c, int fix_c, char **list)
{
	int	i;
	int	start;
	int	end;

	i = -1;
	start = 0;
	end = 0;
	while (++i < fix_c)
	{
		while (s[start] == c && s[start])
			start++;
		end = len_word((char *)s, c, start);
		list[i] = parse_substr(s, start, end);
		if (!list[i])
			return (free_list(list), NULL);
		start = start + end;
	}
	list[i] = NULL;
	return (list);
}

char	**parse_split(char const *s, char c)
{
	char	**list;
	int		fix_c;

	if (!s)
		return (NULL);
	fix_c = count_word((char *)s, c);
	list = (char **)malloc((fix_c + 1) * sizeof(char *));
	if (!list)
		return (NULL);
	list = str_alloc(s, c, fix_c, list);
	return (list);
}
