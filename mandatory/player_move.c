/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:05:31 by bbadda            #+#    #+#             */
/*   Updated: 2024/12/04 12:07:51 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

float	normal_angl(double angle)
{
	angle = fmod(angle, M_PI * 2);
	if (angle < 0)
		angle = M_PI * 2 + angle;
	return (angle);
}

void	player_move(mlx_key_data_t data, void *param)
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
		if (!wall(mlx, mlx->player.x, mlx->player.y + cos(mlx->player.alpha) * move))
			mlx->player.y += cos(mlx->player.alpha) * move;
	}
	if (data.key == MLX_KEY_A)
	{
		if (!wall(mlx, mlx->player.x - sin(mlx->player.alpha) * move, mlx->player.y))
			mlx->player.x -= sin(mlx->player.alpha) * move;
		if (!wall(mlx, mlx->player.x, mlx->player.y - cos(mlx->player.alpha) * move))
			mlx->player.y -= cos(mlx->player.alpha) * move;
	}
	if (data.key == MLX_KEY_R_RIGHT)
		mlx->player.alpha += 0.1;
	if (data.key == MLX_KEY_R_LEFT)	
		mlx->player.alpha -= 0.1;
	mlx->player.alpha = normal_angl(mlx->player.alpha);
	draw(mlx);
}