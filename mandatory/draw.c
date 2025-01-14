/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:27:10 by bbadda            #+#    #+#             */
/*   Updated: 2025/01/14 18:16:33 by med-dahr         ###   ########.fr       */
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

// void	draw_square(t_mlx *mlx, int x0, int y0, int color)
// {
// 	int	x_max;
// 	int	y_max;
	
// 	x_max = SIZE + x0;
// 	y_max = SIZE + y0;
// 	for (int i = x0; i < x_max; i++)
// 	{
// 		for (int j = y0; j < y_max; j++)
// 			mlx_put_pixel(mlx->img.img, i, j, color);	
// 	}
// }

void draw_square_scaled(t_mlx *mlx, int x0, int y0, int color)
{
    int x_max = x0 + (size * MINI_MAP_SCALE);
    int y_max = y0 + (size * MINI_MAP_SCALE);
    for (int i = x0; i < x_max; i++)
    {
        for (int j = y0; j < y_max; j++)
        {
            mlx_put_pixel(mlx->img.img, i, j, color);
        }
    }
}

void draw_player_scaled(t_mlx *mlx, int x0, int y0, int color)
{
    int r = 3 * MINI_MAP_SCALE;
    for (int y = y0 - r; y <= y0 + r; y++)
    {
        for (int x = x0 - r; x <= x0 + r; x++)
        {
            if ((x - x0) * (x - x0) + (y - y0) * (y - y0) <= r * r)
                mlx_put_pixel(mlx->img.img, x, y, color);
        }
    }
}

void draw_map(t_mlx *mlx)
{
    int x, y;

    x = 0;
    while (x < mlx->map.col)
    {
        y = 0;
        while (mlx->map.map[x][y] != '\0')
        {
            if (mlx->map.map[x][y] == '1')
                draw_square_scaled(mlx, y * size * MINI_MAP_SCALE, x * size * MINI_MAP_SCALE, 0xFFFFFFFF);
            y++;
        }
        x++;
    }
    draw_player_scaled(mlx, mlx->player.x * MINI_MAP_SCALE, mlx->player.y * MINI_MAP_SCALE, 0xFFFF00FF);
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

int	get_rgba(uint8_t *color)
{
	return (color[0] << 24 | color[1] << 16 | color[2] << 8 | color[3]);
}

void	draw_rays(t_mlx *mlx, float ray_angl, int i_x)
{
	float	ray_x;
	float	ray_y;
	float	dist;
	float	h;
	double x_texture = 0.0;
	double y_texture = 0.0;
	double color = 0.0;
	ray_x = mlx->player.x;
	ray_y = mlx->player.y;
	while (!wall(mlx, ray_x, ray_y))
	{
		// mlx_put_pixel(mlx->img.img, ray_x, ray_y, 0XFF0000FF);
		ray_x += cos(ray_angl);
		ray_y -= sin(ray_angl);
	}
	dist = sqrt(pow(ray_x - mlx->player.x, 2) + pow(ray_y - mlx->player.y, 2));
	h = (size / dist) * ((HEIGHT / 2) / tan(1.05 / 2));
	float start_d = (HEIGHT / 2) - (h / 2);
	if(start_d < 0)
		start_d = 0;
	float i_y = start_d;
	float end_d = (HEIGHT / 2) + (h / 2);
	if(end_d > HEIGHT)
		end_d = HEIGHT;
	//Horizontal x_texture = (ray_x / size) - floor(ray_x / size) * mlx->textures->ea->width;
	// vertical ? x_texture = (y_projection / wall_height) - floor(y_projection / wall_height) * wisth_image;
	while (i_y < end_d)
	{
		y_texture = i_y - start_d / (end_d - start_d) * mlx->textures->ea->height;
		if (i_y >= 0 && i_y < HEIGHT)
		{
			if ((int)ray_y * mlx->textures->ea->width + (int)ray_x <= mlx->textures->ea->width * mlx->textures->ea->height)//bax mayfoutx pixels dyal image
				color = get_rgba(&mlx->textures->ea->pixels[(int)y_texture * mlx->textures->ea->width + (int)x_texture * 4]);// bax yjib pixel == 4 byte
			mlx_put_pixel(mlx->img.img,i_x,i_y,color);
		}
		i_y++;
	}
}



void    draw(t_mlx *mlx)
{
	float	ray_x;
	float	ray_y;
	float	ray_angl;
	int		i;

	ray_x = mlx->player.x;
	ray_y = mlx->player.y;
	if (mlx->img.img)
		mlx_delete_image(mlx->mlx, mlx->img.img);
	mlx->img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
    draw_map(mlx);
	float f = PI / 3 / WIDTH;
	ray_angl = mlx->player.alpha - PI / 6;
	i = WIDTH;
	while (i >=0)
	{
		draw_rays(mlx, ray_angl, i);
		ray_angl += f;
		i--;
	}
	mlx_image_to_window(mlx->mlx, mlx->img.img, 0, 0);
}
