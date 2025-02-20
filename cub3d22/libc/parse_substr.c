/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_substr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:56:45 by bbadda            #+#    #+#             */
/*   Updated: 2024/11/24 17:56:56 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

size_t	parse_strlen(const char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}

char	*parse_strdup(const char *src)
{
	char	*dst;
	int		i;
	int		len; 

	i = -1;
	len = parse_strlen(src);
	dst = (char *)malloc(len + 1);
	if (dst == 0)
		return (NULL);
	while (++i < len)
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}

char	*parse_substr(char const *str, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (!str)
		return (NULL);
	if (start > parse_strlen(str))
		return (parse_strdup(""));
	if (len > parse_strlen(str) - start)
		len = parse_strlen(str) - start;
	sub = (char *)malloc(len + 1);
	if (sub == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = str[start];
		i++;
		start ++;
	}
	sub[i] = '\0';
	return ((char *)sub);
}
