/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:49:40 by bbadda            #+#    #+#             */
/*   Updated: 2024/11/24 17:49:50 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	__num(char c)
{
	int	r;

	r = 0;
	if (__isalnum(c))
	{
		if (__isdigit(c))
			r = c - 48;
		else
		{
			if (c >= 97 && c <= 122)
				r = c - 97 + 10;
			if (c >= 65 && c <= 90)
				r = c - 65 + 10;
		}
	}
	return (r);
}

int	get_colors(char *str)
{
	int		i;
	int		j;
	long	r;

	r = 0;
	j = 0;
	i = parse_strlen(str) - 1;
	if (i < 1)
		return (16777215);
	while (i >= 2)
	{
		r += __num(str[i]) * pow(16, j);
		i--;
		j++;
	}
	return (r);
}