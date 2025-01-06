/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:51:12 by bbadda            #+#    #+#             */
/*   Updated: 2025/01/06 10:35:00 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*get_part(char *line, int part)
{
	char	**split;

	split = parse_split(line, ' ');
	if (part)
		return (split[0]);
	else
		return (split[1]);
}

static void	__allocate_for_me(t_mlx *mlx)
{
	mlx->map.map = (char **)malloc(mlx->map.col * sizeof(char *));
	mlx->map.textures = (mlx_texture_t **)malloc(4 * sizeof(mlx_texture_t *));
	mlx->map.colors = (char **)malloc(2 * sizeof(char *));
}

static void	__textures(t_mlx *mlx, char *line, int *t)
{
	mlx->map.textures[(*t)++] = (mlx_texture_t *)get_part(line, 0);
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
	__allocate_for_me(mlx);
	fd = open(str, O_RDONLY);
	line = get_next_line(fd);
	i = -1;
	while (line)
	{
		if (!cmp(get_part(line, 1), "NO") || !cmp(get_part(line, 1), "SO")
			|| !cmp(get_part(line, 1), "WE") || !cmp(get_part(line, 1), "EA"))
			__textures(mlx, line, &t);
		else if (!cmp(get_part(line, 1), "F") || !cmp(get_part(line, 1), "C"))
			__colors(mlx, line, &c);
		else if (line[0] == '1' && ++i < mlx->map.col)
			__map(mlx, line, &i);
		free(line);
		line = get_next_line(fd);
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
	close(fd);
}
