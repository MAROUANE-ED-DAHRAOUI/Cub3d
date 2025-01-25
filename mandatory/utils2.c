/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:44:58 by bbadda            #+#    #+#             */
/*   Updated: 2025/01/25 21:16:57 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Checks if a space character is surrounded by '1' characters in the given position.
 *
 * @param mlx The pointer to the t_mlx structure.
 * @param i The row index of the space character.
 * @param j The column index of the space character.
 * @return -1 if the space is not surrounded by '1' characters, 0 otherwise.
 */
int space_surrounding(t_mlx *mlx, int i, int j)
{
	if (mlx->map.map[i][j] == ' ' && (i != 0 || i != mlx->map.col - 1))
	{
		if (!ft_strchr("1 \t", mlx->map.map[i][j]))
		{
			printf("space not surrounded by 1 in this position: %d %d\n", i, j);
			return (-1);
		}
	}
	return (0);
}

int PlayerPositionDirect(char direction)
{
    if (direction == 'N')
		return (270);
	else if (direction == 'S')
		return (90);
	else if (direction == 'E')
		return (0);
	else if (direction == 'W')
		return (180);
	return (-1);
}

void StoreDataPlayer(t_mlx *mlx, int i, int idx)
{
    mlx->player.x = idx + 0.5;
	mlx->player.y = i + 0.5;
	mlx->player.position = PlayerPositionDirect(mlx->map.map[i][idx]);
	mlx->map.map[i][idx] = '0';
}

int	PlayerCounter(t_mlx *mlx)
{
	int	i;
	int	idx;
	int	player;
	
	i = -1;
	player = 0;
	while (++i < mlx->map.col)
	{
		idx = -1;
		while (mlx->map.map[i][++idx])
		{
			if (space_surrounding(mlx, i, idx) == -1)
				return (-1);
	
			if(ft_strchr("NSEW", mlx->map.map[i][idx]))
			{
				if (player_position(mlx, i, idx) == -1)
					    return (printf("player position is a problem\n"), -1);
				StoreDataPlayer(mlx, i, idx);
				player++;
			}
		}
	}
	// printf("player = %d\n", player);
	if(player != 1)
        printf("Multiple players defined in the map\n");
	return (0);
}