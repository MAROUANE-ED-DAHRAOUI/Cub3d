/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:44:58 by bbadda            #+#    #+#             */
/*   Updated: 2024/12/04 12:08:24 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
		print(&mlx);
		__create_window(&mlx);
		draw(&mlx);
		mlx_key_hook(mlx.mlx, player_move, &mlx);
    	mlx_loop(mlx.mlx);
	}
	else
		__error(0, 0);

	(void)map;
	(void)player;

	return (0);
}
