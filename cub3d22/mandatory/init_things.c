/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_things.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:30:56 by bbadda            #+#    #+#             */
/*   Updated: 2025/02/19 11:38:18 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Creates a window and initializes necessary components.
 * 
 * @param mlx The pointer to the t_mlx struct.
 */
void __create_window(t_mlx *mlx)
{
	player_position(mlx);
	mlx->mlx = mlx_init(WIDTH, HEIGHT, "New Window", true);
	mlx->img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->mini_img = mlx_new_image(mlx->mlx, 100, 100);
}

/**
 * Sets the player's angle based on their position.
 * 
 * @param mlx The pointer to the mlx structure.
 */
void get_position_angl(t_mlx *mlx)
{
	if (mlx->player.position == 'N')
		mlx->player.alpha = PI / 2;
	if (mlx->player.position == 'S')
		mlx->player.alpha = (3 * PI) / 2;
	if (mlx->player.position == 'E')
		mlx->player.alpha = 0;
	if (mlx->player.position == 'W')
		mlx->player.alpha = PI;
}

/**
 * Sets the player's position in the game.
 * 
 * @param mlx The pointer to the mlx structure.
 */
void player_position(t_mlx *mlx)
{   
	t_cord cord;

	get_cordinante(mlx, &cord);
	mlx->player.x = cord.x;
	mlx->player.y = cord.y;
	get_position_angl(mlx);
	printf("x = %f, y = %f,\n", mlx->player.x, mlx->player.y);
}

/**
 * Retrieves the coordinates of the player's starting position in the map.
 * 
 * @param mlx The pointer to the mlx structure.
 * @param cord The pointer to the cord structure to store the coordinates.
 */
void get_cordinante(t_mlx *mlx, t_cord *cord)
{
	int i;
	int j;
	int o = 0;
	int p = 0;
	
	i = 0;
	while (i < mlx->map.col)
	{
		j = 0;
		o = 0;
		while (mlx->map.map[i][j])
		{
			if (mlx->map.map[i][j] == 'N' || mlx->map.map[i][j] == 'W'
				|| mlx->map.map[i][j] == 'E' || mlx->map.map[i][j] == 'S')
			{
				mlx->player.position = mlx->map.map[i][j];
				cord->x = o;
				cord->y = p;
				return;
			}
			j++;
			o += 40;
		}
		p += 40;
		i++;
	}
}
