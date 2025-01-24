/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:51:12 by bbadda            #+#    #+#             */
/*   Updated: 2025/01/23 21:55:12 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ExtractPathNorthTex(char *line)
{
	int		i;
	char	*path;

	i = 0;
	if (n_cmp(line, "NO ", 3) == 0)
	{
		i += 3;
		while (ft_strchr(" \t", line[i]))
			i++;
		path = ft_strdup(&line[i]);
		return (path);
	}
	return (NULL);
}

char	*ExtractPathSouthTex(char *line)
{
	int		i;
	char	*path;

	i = 0;
	if (n_cmp(line, "SO ", 3) == 0)
	{
		i += 3;
		while (ft_strchr(" \t", line[i]))
			i++;
		path = ft_strdup(&line[i]);
		return (path);
	}
	return (NULL);
}


char	*ExtractPathEastTex(char *line)
{
	int		i;
	char	*path;

	i = 0;
	if (n_cmp(line, "EA ", 3) == 0)
	{
		i += 3;
		while (ft_strchr(" \t", line[i]))
			i++;
		path = ft_strdup(&line[i]);
		return (path);
	}
	return (NULL);
}

char	*ExtractPathWestTex(char *line)
{
	int		i;
	char	*path;

	i = 0;
	if (n_cmp(line, "WE ", 3) == 0)
	{
		i += 3;
		while (ft_strchr(" \t", line[i]))
			i++;
		path = ft_strdup(&line[i]);
		return (path);
	}
	return (NULL);
}

/**
 * count_tokens - Counts the number of tokens in a string separated by a given delimiter.
 * @s: The input string to be parsed.
 * @c: The delimiter character used to separate tokens.
 *
 * Return: The number of tokens in the input string.
 *
 * This function iterates through the input string, skipping over any occurrences
 * of the delimiter character. When it encounters a non-delimiter character, it
 * counts it as the start of a new token and continues until it finds another
 * delimiter or the end of the string.
 */
size_t	count_tokens(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}


char	**Split_string(char const *src, char sep)
{
	char	**split;
	size_t	start;
	size_t	end;
	size_t	i;

	split = (char **)ft_calloc((count_tokens(src, sep) + 1), (sizeof(char *)));
	if (!split)
		return (NULL);
	start = 0;
	end = 0;
	i = 0;
	while (i < count_tokens(src, sep))
	{
		while (src[start] == sep)
			start++;
		end = start;
		while (src[end] != sep && src[end])
			end++;
		split[i] = ft_substr(src, start, (end - start));
		start = end;
		i++;
	}
	split[i] = 0;
	return (split);
}


/**
 * @brief Creates an RGBA color value from individual red, green, blue, and alpha components.
 *
 * This function takes four integer values representing the red, green, blue, and alpha
 * components of a color, and combines them into a single unsigned integer representing
 * the RGBA color value.
 *
 * @param r The red component of the color (0-255).
 * @param g The green component of the color (0-255).
 * @param b The blue component of the color (0-255).
 * @param a The alpha component of the color (0-255).
 * @return The combined RGBA color value as an unsigned integer.
 *
 * @note If any of the red, green, or blue components are outside the range 0-255,
 *       the function will print an error message and terminate the program.
 */
unsigned int	_rgba(int r, int g, int b, int a)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		printf("[failed: invalid color]\n");
		exit(EXIT_FAILURE);
	}
	return (r << 24 | g << 16 | b << 8 | a);
}

unsigned int	F_color(char *line)
{
	int					i;
	unsigned int		color;
	char				**rgb;

	i = 0;
	if (n_cmp(line, "F ", 2) != 0)
		return (-1);
	i += 2;
	while (ft_strchr(" \t", line[i]))
		i++;
	rgb = Split_string(&line[i], ',');
	color = (unsigned int)_rgba(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]), 0);
	ft_free(rgb);
	return (color);
}

unsigned int	C_color(char *line)
{
	int		i;
	unsigned int		color;
	char	**rgb;

	i = 0;
	if (n_cmp(line, "C ", 2) != 0)
		return (-1);
	i += 2;
	while (ft_strchr(" \t", line[i]))
		i++;
	rgb = Split_string(&line[i], ',');
	color = (unsigned int)_rgba(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]), 0);
	ft_free(rgb);
	return (color);
}
