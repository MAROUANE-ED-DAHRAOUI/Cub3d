/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_things.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:30:56 by bbadda            #+#    #+#             */
/*   Updated: 2025/01/18 12:53:20 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	__create_window(t_mlx *mlx)
{
	mlx->mlx = mlx_init(WIDTH, HEIGHT, "New Window", true);
	mlx->img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx->mlx, mlx->img.img, 0, 0);
	mlx_loop_hook(mlx->mlx, (void (*)(void *))draw, mlx);
}


/**
 * player_position - Checks the player's position on the map.
 * @mlx: Pointer to the t_mlx structure containing the map information.
 * @i: The row index of the player's position.
 * @j: The column index of the player's position.
 *
 * This function verifies if the player's position is valid by checking the
 * following conditions:
 * 1. The player's position is marked by one of the characters 'N', 'S', 'E', or 'W'.
 * 2. The player's position is not at the edge of the map.
 * 3. The player's position is surrounded by walls.
 *
 * If any of these conditions are not met, an error message is printed and the
 * function returns -1. Otherwise, the function returns 0.
 *
 * Return: 0 if the player's position is valid, -1 otherwise.
 */
int	player_position(t_mlx *mlx, int i, int j)
{
	if (ft_strchr("NSEW", mlx->map.map[i][j]))
	{
		if (space_surrounding(mlx, i, j) == -1)
			return (-1);
		if (i == 0 || i == mlx->map.row - 1 || j == 0 || j == mlx->map.col - 1)
			return (printf("failed: player is at the edge of the map\n"), -1);
		if (ft_strchr("NSEW", mlx->map.map[i - 1][j]) ||
				ft_strchr("NSEW", mlx->map.map[i + 1][j])
				|| ft_strchr("NSEW", mlx->map.map[i][j - 1])
				|| ft_strchr("NSEW", mlx->map.map[i][j + 1]))
			return (printf("failed: player is not surrounded by walls\n"), -1);
	}
	return (0);
}
