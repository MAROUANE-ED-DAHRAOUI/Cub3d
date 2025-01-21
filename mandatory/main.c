/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:44:58 by bbadda            #+#    #+#             */
/*   Updated: 2025/01/19 14:37:29 by med-dahr         ###   ########.fr       */
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


unsigned int	*convert_tex_to_px(mlx_texture_t *texture)
{
	unsigned int				x;
	unsigned int				y;
	unsigned int	*pixels;

	x = 0;
	y = 0;
	pixels = ft_calloc(texture->width * texture->height, sizeof(unsigned int));
	while (x < (texture->width * texture->height))
	{
		pixels[x] = create_rgba(texture->pixels[y], texture->pixels[y + 1],
				texture->pixels[y + 2], texture->pixels[y + 3]);
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
	if(mlx->texture_pixels == NULL)
	{
		fprintf(stderr, "Failed to allocate memory for texture pixels\n");
		free_textures(mlx);
		exit(EXIT_FAILURE);
	}
	mlx->texture_pixels[0] = *convert_tex_to_px(mlx->textures->no);
	mlx->texture_pixels[1] = *convert_tex_to_px(mlx->textures->ea);
	mlx->texture_pixels[2] = *convert_tex_to_px(mlx->textures->we);
	mlx->texture_pixels[3] = *convert_tex_to_px(mlx->textures->so);
}

double	normal_angl(double angle)
{
	angle = fmod(angle, PI * 2);
	if (angle < 0)
		angle += PI * 2;;
	return (angle);
}

static void	ft_move(t_mlx *mlx, double px, double py)
{
	double	ppx;
	double	ppy;

	ppx = (mlx->player.x * size) + (px * SPEED_PLY);
	ppy = (mlx->player.y * size) + (py * SPEED_PLY);
	if (mlx->map.map[(int)((ppy + WALL_PADDING) / size)][(int)
			(ppx / size)] == '1' || mlx->map.map[(int)(ppy / size)]
			[(int)((ppx + WALL_PADDING) / size)] == '1' || mlx->map.map[(int)
			((ppy - WALL_PADDING) / size)][(int)
			(ppx / size)] == '1' || mlx->map.map[(int)(ppy / size)]
			[(int)((ppx - WALL_PADDING) / size)] == '1')
		return ;
	mlx->player.x = ((mlx->player.x * size)
			+ (px * SPEED_PLY)) / size;
	mlx->player.y = ((mlx->player.y * size)
			+ (py * SPEED_PLY)) / size;
}

void	move_player(mlx_key_data_t data, void *param)
{
	double	rangle;
	t_mlx *mlx;

	rangle = mlx->player.position;
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_W))
		ft_move(mlx, cos(deg2rad(rangle)), -sin(deg2rad(rangle)));
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_S))
		ft_move(mlx, -cos(deg2rad(rangle)), sin(deg2rad(rangle)));
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_A))
		ft_move(mlx, sin(deg2rad(rangle)), cos(deg2rad(rangle)));
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_D))
		ft_move(mlx, -sin(deg2rad(rangle)), -cos(deg2rad(rangle)));
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_ESCAPE))
		exit(EXIT_SUCCESS);
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_RIGHT))
		mlx->player.position = normalize_angle(mlx->player.position + SPEED_ROTATE);
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_LEFT))
		mlx->player.position = normalize_angle(mlx->player.position - SPEED_ROTATE);
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
		// print(&mlx);
		if(PlayerCounter(&mlx) == 0)
		{
			fprintf(stderr, "There is a wrong in map\n");
			return -1;
		}
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
