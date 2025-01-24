/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:44:58 by bbadda            #+#    #+#             */
/*   Updated: 2025/01/24 13:53:35 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	*ft_calloc(size_t count, size_t _size)
{
	char	*res;
	size_t	i;

	i = 0;
	res = (char *)malloc(count * _size);
	if (!res)
		return (NULL);
	while (i < count * _size)
	{
		res[i] = 0;
		i++;
	}
	return (res);
}

void free_textures(t_mlx *mlx)
{
    if (mlx->textures)
    {
        if (mlx->textures->no)
            mlx_delete_texture(mlx->textures->no);
        if (mlx->textures->so)
            mlx_delete_texture(mlx->textures->so);
        if (mlx->textures->we)
            mlx_delete_texture(mlx->textures->we);
        if (mlx->textures->ea)
            mlx_delete_texture(mlx->textures->ea);

        free(mlx->textures); // Free the allocated structure
        mlx->textures = NULL;
    }
}

unsigned int	*convert_tex_to_px(mlx_texture_t *texture)
{
	unsigned int				x;
	unsigned int				y;
	unsigned int				*pixels;

	x = 0;
	y = 0;
	pixels = ft_calloc(texture->width * texture->height, sizeof(unsigned int));
	while (x < (texture->width * texture->height))
	{
		pixels[x] = _rgba(texture->pixels[y], texture->pixels[y + 1],
				texture->pixels[y + 2], texture->pixels[y + 3]);
		y += 4;
		x++;
	}
	return (pixels);
}

void load_textures(t_mlx *mlx)
{
	mlx->map.textures[0] = mlx_load_png(mlx->map.path[0]);
	mlx->map.textures[1] = mlx_load_png(mlx->map.path[1]);
	mlx->map.textures[2] = mlx_load_png(mlx->map.path[2]);
	mlx->map.textures[3] = mlx_load_png(mlx->map.path[3]);
	
	free(mlx->map.path[0]);
	free(mlx->map.path[1]);
	free(mlx->map.path[2]);
	free(mlx->map.path[3]);
	if (mlx->map.textures[0] == NULL || mlx->map.textures[1] == NULL
		|| mlx->map.textures[2] == NULL || mlx->map.textures[3] == NULL)
	{
		printf("failed: the textures are not loaded\n");
		exit(EXIT_FAILURE);
	}
	mlx->texture_pixels = ft_calloc(4, sizeof(unsigned int *));
	mlx->texture_pixels = convert_tex_to_px(mlx->map.textures[0]);
}

double	normal_angl(double angle)
{
	if (angle < 0)
		angle += 360;
	if (angle >= 360)
		angle -= 360;
	return (angle);
}

static void	ft_move(t_mlx *mlx, double px, double py)
{
	double	Player_Position_x;
	double	Player_Position_y;

	Player_Position_x = (mlx->player.x * size) + (px * SPEED_PLY);
	Player_Position_y = (mlx->player.y * size) + (py * SPEED_PLY);
	if (mlx->map.map[(int)((Player_Position_y + WALL_PADDING) / size)][(int)
			(Player_Position_x / size)] == '1' || mlx->map.map[(int)(Player_Position_y / size)]
			[(int)((Player_Position_x + WALL_PADDING) / size)] == '1' || mlx->map.map[(int)
			((Player_Position_y - WALL_PADDING) / size)][(int)
			(Player_Position_x / size)] == '1' || mlx->map.map[(int)(Player_Position_y / size)]
			[(int)((Player_Position_x - WALL_PADDING) / size)] == '1')
		return ;
	mlx->player.x = ((mlx->player.x * size)
			+ (px * SPEED_PLY)) / size;
	mlx->player.y = ((mlx->player.y * size)
			+ (py * SPEED_PLY)) / size;
}

void	move_player(t_mlx *mlx)
{
	double	rangle;

	rangle = mlx->player.position;
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_W))
		ft_move(mlx, cos(computeDeg(rangle)), -sin(computeDeg(rangle)));
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_S))
		ft_move(mlx, -cos(computeDeg(rangle)), sin(computeDeg(rangle)));
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_A))
		ft_move(mlx, sin(computeDeg(rangle)), cos(computeDeg(rangle)));
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_D))
		ft_move(mlx, -sin(computeDeg(rangle)), -cos(computeDeg(rangle)));
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_ESCAPE))
		exit(EXIT_SUCCESS);
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_RIGHT))
		mlx->player.position =  normal_angl(mlx->player.position + SPEED_ROTATE);
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_LEFT))
		mlx->player.position =  normal_angl(mlx->player.position - SPEED_ROTATE);
}

int main(int ac, char **av)
{
	t_map		*map;
	t_mlx		mlx;
	t_player	*player;
	mlx.mlx = NULL;
	mlx.img.img = NULL;
	map = NULL;
	player = NULL;
    if (ac == 2)
	{
		check_file_type(av[1]);
		map = malloc(sizeof(t_map));
		if(map == NULL)
			printf("Cant allocate map struct, increase the program break");
		check_valid_map(av[1], &mlx);
		read_and_fill_map(av[1], &mlx);
		if(check_map(&mlx) == -1)
		{
			printf("something wrong in map\n");
			exit(EXIT_FAILURE);
		}
		if(PlayerCounter(&mlx) != 0)
		{
			fprintf(stderr, "There is a wrong in map\n");
			return -1;
		}
		load_textures(&mlx);
		__create_window(&mlx);
		mlx_loop_hook(mlx.mlx , draw, &mlx);
    	mlx_loop(mlx.mlx);
		free_textures(&mlx);
	}
	else
		__error(0, 0);
}
