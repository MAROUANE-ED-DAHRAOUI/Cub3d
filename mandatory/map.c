/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:51:12 by bbadda            #+#    #+#             */
/*   Updated: 2025/01/20 11:15:17 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*get_part(char *line, int part)
{
	char	**split;

	split = parse_split(line, ' ');
	if (part)
		return (split[0]);
	else
		return (split[1]);
}

void	*ft_calloc(size_t count, size_t Size)
{
	char	*res;
	size_t	i;

	i = 0;
	res = (char *)malloc(count * size);
	if (!res)
		return (NULL);
	while (i < count * size)
	{
		res[i] = 0;
		i++;
	}
	return (res);
}

static void	__allocate_for_me(t_mlx *mlx)
{
	mlx->map.map = ft_calloc(mlx->map.col, sizeof(char *));
	mlx->map.textures = (char **)malloc(4 * sizeof(char *));
	mlx->map.colors = (char **)malloc(2 * sizeof(char *));
}

static void	__colors(t_mlx *mlx, char *line, int *c)
{
	mlx->map.colors[*c] = get_part(line, 0);
	if (!cmp(get_part(line, 1), "F"))
		mlx->map.f_color = get_colors(mlx->map.colors[*c++]);
	else if (!cmp(get_part(line, 1), "C"))
		mlx->map.c_color = get_colors(mlx->map.colors[*c++]);
}

static void	__map(t_mlx *mlx, char *line, int *i)
{
	mlx->map.map[(*i)] = parse_strdup(line);
}

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)s;
	if ((char)c == '\0')
		return (str + ft_strlen(str));
	while (str[i])
	{
		if (str[i] == (char)c)
			return (str + i);
		i++;
	}
	return (NULL);
}

int	check_map_closed(t_mlx *mlx)
{
	int	i;
	int	idx;

	i = 0;
	while (i < mlx->map.col)
	{
		idx = 0;
		while (mlx->map.map[i][idx])
		{
			if (mlx->map.map[i][idx] == '0')
			{
				if (i == 0 || i == mlx->map.row - 1 || idx == 0
					|| idx == (int)ft_strlen(mlx->map.map[i]) - 1)
					return (printf("failed: map is not closed\n"), -1);
				if (mlx->map.map[i - 1][idx] == ' ' || mlx->map.map[i + 1][idx] == ' '
						|| mlx->map.map[i][idx - 1] == ' '
						|| mlx->map.map[i][idx + 1] == ' ')
					return (printf("failed: map is not closed\n"), -1);
			}
			idx++;
		}
		i++;
	}
	return (0);
}

/**
 * @brief Checks if the first and last lines of the map are properly closed.
 *
 * This function iterates through the first and last lines of the map to ensure
 * that they are only composed of '1' or ' ' characters. If any other character
 * is found, it prints an error message and returns -1.
 *
 * @param mlx A pointer to the t_mlx structure containing the map information.
 * @return int Returns 0 if the first and last lines are properly closed, 
 *         otherwise returns -1.
 */
static int	check_first_last_line(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (mlx->map.map[0][i])
	{
		if (!ft_strchr(" 1", mlx->map.map[0][i]))
			return (printf("failed: map is not closed\n"), -1);
		i++;
	}
	i = 0;
	while (mlx->map.map[mlx->map.col - 1][i])
	{
		if (!ft_strchr("1 ", mlx->map.map[mlx->map.col - 1][i]))
			return (printf("failed: map is not closed\n"), -1);
		i++;
	}
	return (0);
}

int check_map(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (i < mlx->map.row)
	{
		j = 0;
		while (mlx->map.map[i][j])
		{
			if (!ft_strchr(" 01NSEW", mlx->map.map[i][j]))
				return (printf("failed: map contains invalid character\n"), -1);
			j++;
		}
		i++;
	}
	if (check_map_closed(mlx) == -1)
		return (printf("there is aproblem in map\n"), -1);
	return (check_first_last_line(mlx));
}

void	read_and_fill_map(char *str, t_mlx *mlx)
{
	int		fd;
	char	*line;
	int		i;
	int		t;
	int		c;

	t = 0;
	c = 0;
	mlx->map.map = NULL;
	mlx->map.map = ft_calloc(mlx->map.col + 3, sizeof(char *));	
	fd = open(str, O_RDONLY);
	if(!fd)
		printf("can't open the map file");
	line = get_next_line(fd);
	i = -1;
	while (line)
	{
		if (!cmp(get_part(line, 0), "F") || !cmp(get_part(line, 1), "C"))
			__colors(mlx, line, &c);
		else if (line[0] == '1' && ++i < mlx->map.col)
			__map(mlx, line, &i);
		free(line);
		line = get_next_line(fd);
	}
	if(check_map(mlx) == 0)
	{
		printf("something is wrong in the map\n");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	check_valid_map(char *map, t_mlx *mlx)
{
	int		fd;
	char	*line;
	int		i;
	int		l;

	mlx->map.col = 0;
	l = 0;
	fd = open(map, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '1') 
		{
			i = 0;
			mlx->map.row = 0;
			while (line[i] && line[i] != '\n')
			{
				mlx->map.row++;
				i++;
			}
			mlx->map.col++;
		}
		l++;
		free(line);
		line = get_next_line(fd);
	}
	if (mlx->map.row < 3)
	{
		printf("failed: Map is too small\n");
		exit(EXIT_FAILURE);
	}
	close(fd);
}
