/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:27:10 by bbadda            #+#    #+#             */
/*   Updated: 2025/02/19 23:58:51 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	wall(t_mlx *mlx, float py, float px)
{
	int	x;
	int	y;

	x = px/ size;
	y = py/ size;
	if (mlx->map.map[x][y] == '1')
		return (true);
	return (false);
}

void	draw_square(t_mlx *mlx, int x0, int y0, int color)
{
	int	x_max;
	int	y_max;
	
	x_max = size + x0;
	y_max = size + y0;
	for (int i = x0; i < x_max; i++)
	{
		for (int j = y0; j < y_max; j++)
			mlx_put_pixel(mlx->img.img, i, j, color);		
	}
}

void	draw_map(t_mlx *mlx)
{
	int	x;
	int	y;

	x = 0;
	while (x < mlx->map.col)
	{
		y = 0;
		while (mlx->map.map[x][y])
		{
			if (mlx->map.map[x][y] == '1')
				draw_square(mlx, y * size, x * size, 0xFFFFFFFF);
			// else if (mlx->map.map[x][y] == 'N')
			// 	draw_player(mlx, mlx->player.x, mlx->player.y, 157945);
			y++;
		}
		x++;
    }
}

void	draw_player(t_mlx *mlx, int x0, int y0, int color)
{
	int	x_max;
	int	y_max;
	int	i;
	int	j;

	i = x0;
	x_max =x0;
	y_max =y0;
	while (i++ < x_max)
	{
		j = y0;
		while (j++ < y_max)
			mlx_put_pixel(mlx->img.img, i, j, color);
	}
}

/**
 * Draws rays from the player's position to the walls in the game world.
 * 
 * @param mlx The pointer to the mlx structure.
 * @param ray_angl The angle of the ray.
 * @param i_x The x-coordinate of the pixel to draw on.
 */



int	txt_x(t_mlx *game)
{
	(void)game;
	return (2);
	// int	texture_x;

	// if (game->player.side == HOREZONTAL)
	// 	texture_x = (int)game->player.x % size;
	// if (game->player.side == VERTECAL)
	// 	texture_x = (int)game->player.y % size;
	// return (texture_x);
}

int	find_color(t_mlx *game, int start, int end, int tex_x, int startsave)
{
	// (void)game;
	// (void)start;
	// (void)end;
	// (void)tex_x;
	// (void)startsave;
	// return (255);
	static t_color	clr;
	int	height = end - start + 1;
	clr.tx = game->txx;
	
	// scolor(&clr, game);
	clr.tex_y = start - startsave;
	// printf("*********** %d\n", height);
	clr.tex_y = (clr.tx->height * 
			((clr.tex_y * 100) / height)) / 100;
	tex_x = (clr.tx->width * ((tex_x * 100) / size)) / 100;
	clr.x1 = clr.tx->bytes_per_pixel * (clr.tx->width * clr.tex_y + tex_x);
	clr.y1 = clr.x1 + 1;
	clr.z1 = clr.x1 + 2;
	if (clr.x1 < 0 || clr.x1 > clr.tx->width * clr.tx->height * 4 || clr.y1 < 0 
		|| clr.y1 > clr.tx->width
		* clr.tx->height * 4 || clr.z1 < 0
		|| clr.z1 > clr.tx->width * clr.tx->height * 4)
		return (0);
	clr.x = clr.tx->pixels[clr.x1];
	clr.y = clr.tx->pixels[clr.y1];
	clr.z = clr.tx->pixels[clr.z1];
	clr.res = clr.x << 24 | clr.y << 16 | clr.z << 8 | 255;
	return (clr.res);
}




void draw_rays(t_mlx *mlx, float ray_angl, int i_x)
{
	float ray_x;
	float ray_y;
	float dist;
	float h;
	float tex_x = txt_x(mlx);
	
	ray_x = mlx->player.x;
	ray_y = mlx->player.y;
	
	// Draw rays until a wall is encountered
	while (!wall(mlx, ray_x, ray_y))
	{
		mlx_put_pixel(mlx->img.img, ray_x, ray_y, 0XFF0000FF);
		ray_x += cos(ray_angl);
		ray_y -= sin(ray_angl);
	}
	// printf("ray_x: %f, ray_y: %f\n", ray_x, ray_y);
	
	// Calculate the distance from the player to the wall
	dist = sqrt(pow(ray_x - mlx->player.x, 2) + pow(ray_y - mlx->player.y, 2));
	
	// Calculate the height of the wall on the screen
	h = (size / dist) * ((HEIGHT / 2) / tan(1.05 / 2));
	
	float start_d = (HEIGHT / 2) - (h / 2);
	if(start_d < 0)
		start_d = 0;
	
	float i_y = start_d;
	float end_d = (HEIGHT / 2) + (h / 2);
	if(end_d > HEIGHT)
		end_d = HEIGHT;
	
	float savestart = i_y;
	// Draw the wall on the screen
	while (i_y < end_d)
	{
		// mlx_put_pixel(mlx->img.img, i_x, i_y, 0XFF0000FF);
		mlx_put_pixel(mlx->img.img, i_x, i_y, find_color(mlx, i_y, end_d,tex_x, savestart));
		i_y++;
	}	
}

/**
 * Draws the game scene using raycasting technique.
 * 
 * @param mlx The pointer to the t_mlx structure.
 */
void draw(t_mlx *mlx)
{
	float ray_x;
	float ray_y;
	float ray_angl;
	int i;

	ray_x = mlx->player.x;
	ray_y = mlx->player.y;
	if (mlx->img.img)
		mlx_delete_image(mlx->mlx, mlx->img.img);
	mlx->img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	draw_map(mlx);
	float f = PI / 3 / WIDTH;
	ray_angl = mlx->player.alpha - PI / 6;
	i = WIDTH;
	while (i >= 0)
	{
		draw_rays(mlx, ray_angl, i);
		ray_angl += f;
		i--;
	}
	mlx_image_to_window(mlx->mlx, mlx->img.img, 0, 0);
}
