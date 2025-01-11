/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:44:58 by bbadda            #+#    #+#             */
/*   Updated: 2025/01/11 13:30:41 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void free_textures(t_mlx *mlx)
{
	if(mlx->map.textures[0] != NULL && mlx->map.textures[1] != NULL && 
		mlx->map.textures[2] != NULL && mlx->map.textures[3] != NULL)
		{
			free(mlx->map.textures[0]);
			free(mlx->map.textures[1]);
			free(mlx->map.textures[2]);
			free(mlx->map.textures[3]);
		}
}

void load_textures(t_mlx *mlx)
{
    mlx->map.textures[0] = mlx_load_png("/Users/med-dahr/Desktop/Cub3d/texture/north.png");
    mlx->map.textures[1] = mlx_load_png("/Users/med-dahr/Desktop/Cub3d/texture/south.png");
    mlx->map.textures[2] = mlx_load_png("/Users/med-dahr/Desktop/Cub3d/texture/east.png");
    mlx->map.textures[3] = mlx_load_png("/Users/med-dahr/Desktop/Cub3d/texture/west.png");

    if (!mlx->texture.north || !mlx->texture.south || 
        !mlx->texture.east || !mlx->texture.west)
    {
        printf("Error loading textures!\n");
        exit(1);
    }
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
		load_textures(&mlx);
		// print(&mlx);
		__create_window(&mlx);
		draw(&mlx);
		mlx_key_hook(mlx.mlx, player_move, &mlx);
    	mlx_loop(mlx.mlx);
		free_textures(&mlx);
	}
	else
		__error(0, 0);

	(void)map;
	(void)player;

	return (0);
}

// Main entry point for the game
// int main(int ac, char **av)
// {
//     t_data data;

//     check_requirements(ac, av, &data);
//     init_mlx_elements(&data);
//     init_textures(&data); // Initialize textures

//     mlx_loop_hook(data.mlx, ft_loop, &data);
//     mlx_loop(data.mlx);

//     free_textures(&data); // Free textures after game loop ends
//     clean_all(&data);
//     return 0;
// }