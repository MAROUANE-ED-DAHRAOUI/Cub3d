/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:44:58 by bbadda            #+#    #+#             */
/*   Updated: 2025/01/19 11:38:16 by med-dahr         ###   ########.fr       */
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

unsigned int	create_rgba(int r, int g, int b, int a)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		printf("[failed: invalid color]\n");
		exit(EXIT_FAILURE);
	}
	return (r << 24 | g << 16 | b << 8 | a);
}

unsigned int	*convert_tex_to_px(mlx_texture_t *tex)
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	*pixels;

	x = 0;
	y = 0;
	pixels = ft_calloc(tex->width * tex->height, sizeof(unsigned int));
	while (x < (tex->width * tex->height))
	{
		pixels[x] = create_rgba(tex->pixels[y], tex->pixels[y + 1],
				tex->pixels[y + 2], tex->pixels[y + 3]);
		y += 4;
		x++;
	}
	return (pixels);
}

void load_textures(t_mlx *mlx)
{
    // Allocate memory for textures
    mlx->textures = malloc(sizeof(t_texture));
    if (!mlx->textures)
    {
        fprintf(stderr, "Failed to allocate memory for textures\n");
        exit(EXIT_FAILURE);
    }

    // Load texture files
    mlx->textures->no = mlx_load_png("/Users/med-dahr/Cub3d/texture/north.png");
    mlx->textures->so = mlx_load_png("/Users/med-dahr/Cub3d/texture/south.png");
    mlx->textures->we = mlx_load_png("/Users/med-dahr/Cub3d/texture/west.png");
    mlx->textures->ea = mlx_load_png("/Users/med-dahr/Cub3d/texture/east.png");

    // Check if all textures loaded successfully
    if (!mlx->textures->no || !mlx->textures->so || !mlx->textures->we || !mlx->textures->ea)
    {
        fprintf(stderr, "Failed to load textures\n");
        free_textures(mlx); // Free any successfully loaded textures
        exit(EXIT_FAILURE);
    }
	mlx->texture_pixels = ft_calloc(4, sizeof(unsigned int *));
	mlx->texture_pixels = convert_tex_to_px(mlx->textures->no);
	mlx->texture_pixels = convert_tex_to_px(mlx->textures->ea);
	mlx->texture_pixels = convert_tex_to_px(mlx->textures->we);
	mlx->texture_pixels = convert_tex_to_px(mlx->textures->so);
}

double	normal_angl(double angle)
{
	angle = fmod(angle, M_PI * 2);
	if (angle < 0)
		angle = M_PI * 2 + angle;
	return (angle);
}

void	move_player(mlx_key_data_t data, void *param)
{
	t_mlx		*mlx;
	int			move;

	move = 10;
	mlx = (t_mlx *)param;
	if (data.key == MLX_KEY_ESC)
		mlx_close_window(mlx->mlx);
	if (data.key == MLX_KEY_W)
	{
		if (!wall(mlx, mlx->player.x + cos(mlx->player.alpha) * move, mlx->player.y))
			mlx->player.x += cos(mlx->player.alpha) * move;
		if (!wall(mlx, mlx->player.x, mlx->player.y - sin(mlx->player.alpha) * move))
			mlx->player.y -= sin(mlx->player.alpha) * move;
	}
	if (data.key == MLX_KEY_S)
	{
		if (!wall(mlx, mlx->player.x - cos(mlx->player.alpha) * move, mlx->player.y))
			mlx->player.x -= cos(mlx->player.alpha) * move;
		if (!wall(mlx, mlx->player.x, mlx->player.y + sin(mlx->player.alpha) * move))
			mlx->player.y += sin(mlx->player.alpha) * move;
	}
	if (data.key == MLX_KEY_D)
	{
		if (!wall(mlx, mlx->player.x + sin(mlx->player.alpha) * move, mlx->player.y))
			mlx->player.x += sin(mlx->player.alpha) * move;
		if (!wall(mlx, mlx->player.x, mlx->player.y - cos(mlx->player.alpha) * move))
			mlx->player.y += cos(mlx->player.alpha) * move;
	}
	if (data.key == MLX_KEY_A)
	{
		if (!wall(mlx, mlx->player.x - sin(mlx->player.alpha) * move, mlx->player.y))
			mlx->player.x -= sin(mlx->player.alpha) * move;
		if (!wall(mlx, mlx->player.x, mlx->player.y + cos(mlx->player.alpha) * move))
			mlx->player.y -= cos(mlx->player.alpha) * move;
	}
	if (data.key == MLX_KEY_R_RIGHT)
		mlx->player.alpha += 0.1;
	if (data.key == MLX_KEY_R_LEFT)	
		mlx->player.alpha -= 0.1;
	mlx->player.alpha = normal_angl(mlx->player.alpha);
	draw(mlx);
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
		map = malloc(sizeof(t_map));
		check_file_type(av[1]);
		check_valid_map(av[1], &mlx);
		read_and_fill_map(av[1], &mlx);
		// print(&mlx);
		load_textures(&mlx);
		__create_window(&mlx);
		draw(&mlx);
		mlx_key_hook(mlx.mlx, move_player, &mlx);
    	mlx_loop(mlx.mlx);
		free_textures(&mlx);

	}
	else
		__error(0, 0);
}
