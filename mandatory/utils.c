/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:54:38 by bbadda            #+#    #+#             */
/*   Updated: 2024/11/24 17:51:49 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		j;
	int		k;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = my_strlen((char *)s1) - 1;
	k = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (j >= 0 && ft_strchr(set, s1[j]))
		j--;
	if (j < i)
		return (ft_strdup(""));
	str = (char *)malloc(sizeof(char) * (j - i + 2));
	if (!str)
		return (NULL);
	while (i <= j)
		str[k++] = s1[i++];
	str[k] = '\0';
	return (str);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	nbr;

	i = 0;
	sign = 1;
	nbr = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	return (nbr * sign);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	int		i;
	char	*str;

	if (!s)
		return (NULL);
	else if ((size_t) my_strlen((char *)s + start) < len)
		str = malloc(sizeof(char) * (my_strlen((char *)s + start + 1)));
	else
		str = malloc(sizeof(char) * ((int)len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[start] && i < (int)len && (unsigned int)
		my_strlen((char *)s) >= start)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}

size_t  my_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}

char	*ft_strdup(const char *s1)
{
	int		indx;
	int		len;
	char	*str;

	indx = 0;
	len = my_strlen((char *)s1);
	str = ((char *)malloc(sizeof(char) * (len +1)));
	if (str == NULL)
		return (NULL);
	while (indx < len)
	{
		str[indx] = s1[indx];
		indx++;
	}
	str[indx] = '\0';
	return (str);
}

int	n_cmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	unsigned char	*s1c;
	unsigned char	*s2c;

	s1c = (unsigned char *)s1;
	s2c = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	if (s1c == NULL || s2c == NULL)
		return (0);
	while (s1c[i] == s2c[i] && s1c[i] && s2c[i] && i < n - 1)
		i++;
	return (s1c[i] - s2c[i]);
}

int	cmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	check_file_type(const char *s)
{
	size_t	len;

	len = my_strlen(s);
	if (len < 5 || n_cmp(s + (len - 4), ".cub", len - 4) != 0)
		__error2(7);
}

void	__error(int index, int fd)
{
	if (index == 0)
	{
		write(1, ERR_ARGS, 46);
		exit(0);
	}
	if (index == 1)
	{
		write(1, ERR_EMPTY, 50);
		exit(0);
	}
	if (index == 2)
	{
		write(1, ERR_OPEN, 27);
		close(fd);
		exit(0);
	}
}

void	__error2(int index)
{
	if (index == 4)
	{
		write(1, ERR_MAP, 14);
		exit(0);
	}
	if (index == 5)
	{
		write(1, ERR_SPLIT, 29);
		exit(0);
	}
	if (index == 6)
	{
		write(1, ERR_MEM, 17);
		exit(0);
	}
	if (index == 7)
	{
		write(1, ERR_FILE, 21);
		exit(0);
	}
}
