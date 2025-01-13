/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:44:58 by bbadda            #+#    #+#             */
/*   Updated: 2025/01/13 11:43:49 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void free_textures(t_mlx *mlx)
{
	if (mlx->map.texture)
	{
		for (int i = 0; i < 4; i++)
			free(mlx->map.texture[i]);
		free(mlx->map.texture);
	}
}

void load_textures(t_mlx *mlx)
{
    mlx->map.texture = malloc(4 * sizeof(mlx_texture_t *));
    mlx->map.texture[0] = mlx_load_png("/Users/med-dahr/Cub3D/cub3d22/texture/north.png");
    mlx->map.texture[1] = mlx_load_png("/Users/med-dahr/Cub3D/cub3d22/texture/south.png");
    mlx->map.texture[2] = mlx_load_png("/Users/med-dahr/Cub3D/cub3d22/texture/east.png");
    mlx->map.texture[3] = mlx_load_png("/Users/med-dahr/Cub3D/cub3d22/texture/west.png");

    for (int i = 0; i < 4; i++)
    {
        if (!mlx->map.textures[i])
        {
            printf("Error loading texture %d!\n", i);
            exit(1);
        }
    }
}

float	normal_angl(double angle)
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
	}
	else
		__error(0, 0);
}
