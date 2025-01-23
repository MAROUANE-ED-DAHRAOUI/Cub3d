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

static int	my_strlen(char *str)
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
		return (str + my_strlen(str));
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
					|| idx == (int)my_strlen(mlx->map.map[i]) - 1)
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

int		ExtractAssetsRows(int fd, char **map)
{
	int		i;
	int		line;
	char	*tmp[2];

	i = 0;
	line = 0;
	tmp[0] = get_next_line(fd);
	while (tmp[0])
	{
		tmp[1] = ft_strtrim(tmp[0], " \n\t\v\f\r");
		if (my_strlen(tmp[1]))
			map[i++] = ft_strtrim(tmp[0], " \n");
		if (line < my_strlen(map[i - 1]))
			 line = my_strlen(map[i - 1]);
		free(tmp[0]);
		free(tmp[1]);
		tmp[0] = get_next_line(fd);
	}
	return (line);
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
	fd = open(str, O_RDONLY);
	if(fd != -1)
		printf("can't open the map file\n");
	i = -1;
	while (++i < mlx->map.skip)
		free(get_next_line(fd));
	mlx->map.map = ft_calloc(mlx->map.col + 7, sizeof(char *));	
	mlx->map.row = ExtractAssetsRows(fd, mlx->map.map);
	close(fd);
}

void	ParseLineExtractAssets(char *line, t_mlx *mlx)
{
	if (n_cmp(line, "NO", 2) == 0)
		mlx->map.path[0] = ExtractPathNorthTex(line);
	if (n_cmp(line, "SO", 2) == 0)
		mlx->map.path[1] = ExtractPathSouthTex(line);
	if (n_cmp(line, "WE", 2) == 0)
		mlx->map.path[2] = ExtractPathWestTex(line);
	if (n_cmp(line, "EA", 2) == 0)
		mlx->map.path[3] = ExtractPathEastTex(line);
	if (n_cmp(line, "F", 1) == 0)
		mlx->map.f_color = F_color(line);
	if (n_cmp(line, "C", 1) == 0)
		mlx->map.c_color = C_color(line);
}

int 	ExtractsAssetsFromFile(char *map, t_mlx *mlx)
{
	char	*line;
	int		fd;
	int		i;

	fd = open(map, O_RDONLY);
	line = get_next_line(fd);
	i = 0;
	if(fd != -1 || *line != '\0')
		printf("cant open FILE\n");
	while (line && ft_strchr("\t 10", line[0]) == NULL)
	{
		line[my_strlen(line) - 1] = '\0';
		ParseLineExtractAssets(line, mlx);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free(line);
	return (i);
}

void	check_valid_map(char *map, t_mlx *mlx)
{
	int		fd;
	char	*line;
	int		i;
	int		l;
	int		col;
	char	*tmp;
	char	*tmp1;

	mlx->map.col = 0;
	l = 0;

	mlx->map.skip = ExtractsAssetsFromFile(map, mlx);
	fd = open(map, O_RDONLY);
	tmp = get_next_line(fd);
	while (1)
	{
		tmp1 = ft_strtrim(tmp, " \n\t\v\f\r");
		if (my_strlen(tmp1))
			col++;
		free(tmp);
		free(tmp1);
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
	}
	close(fd);
	mlx->map.col = col;
	if (mlx->map.col < 3)
	{
		printf("failed: Map is too small\n");
		exit(EXIT_FAILURE);
	}
	close(fd);
}
