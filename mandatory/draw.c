/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:27:10 by bbadda            #+#    #+#             */
/*   Updated: 2025/01/20 20:26:54 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// bool	wall(t_mlx *mlx, float py, float px)
// {
// 	int	x;
// 	int	y;

// 	x = px / size;
// 	y = py / size;
// 	if (mlx->map.map[x][y] == '1')
// 		return (true);
// 	return (false);
// }

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

unsigned int get_rgba(uint8_t *color) 
{
    if (color == NULL || (color[0] == 0 && color[1] == 0 && color[2] == 0))
        return (0);
    return (color[0] << 24 | color[1] << 16 | color[2] << 8 | color[3]);
}

void draw_vertical_line(t_mlx *mlx, int i_x, double *coords, unsigned int color)
{
	double	y;

	y = coords[0];
	while (y < coords[1])
	{
		if (y > 0 && y < HEIGHT)
			mlx_put_pixel(mlx->img.img, i_x, y, color);
		y++;
	}
}

void	draw_rays(t_mlx *mlx, int i_x)
{
    mlx->rays->ray_x = mlx->player.x;
    mlx->rays->ray_y = mlx->player.y;
    int          x_texture = 0;
    int             color = 0;
    double	        coords[2];
    double          tstep;
    int             index = 0;

    // Calculate the distance to the wall
    tstep = (mlx->pxl.endy - mlx->pxl.starty) / size;
    
    // Calculate initial x_texture coordinate
	if (mlx->rays->vertical == false) 
    	x_texture = (int)mlx->rays->ray_x % size;
	else
    	x_texture = (int)mlx->rays->ray_y % size;

if (x_texture < 0 || x_texture >= size) {
    printf("Error: Invalid texture index x_texture = %d\n", x_texture);
    return;
}

    
    while(index < size)
    {
        coords[0] = mlx->pxl.starty;
        coords[1] = mlx->pxl.starty + tstep;
        printf("coords[0] = %f, coords[1] = %f\n, x_texture=%d\n", coords[0], coords[1], x_texture);
        color = mlx->texture_pixels[size * index + x_texture];
        draw_vertical_line(mlx, i_x, coords, color);
        mlx->pxl.starty += tstep;
        index++;
    }
}

void      calculate_ray_and_fov(t_mlx *mlx, double *rangle, double *fov_step)
{
    *rangle = mlx->player.position - 0;
    *fov_step = FOV / (double)WIDTH;
}

double computeDeg(double rad)
{
    return (rad * (PI / 180));
}

t_ray initialRay()
{
    t_ray ray;

    ray.distance = 0;
    ray.ray_x = 0;
    ray.ray_y = 0;
    ray.vertical = false;
    ray.looks[0] = 0;
	ray.looks[1] = 0;
	ray.looks[2] = 0;
	ray.looks[3] = 0;
    return (ray);
}

void draw(t_mlx *mlx) 
{
    double rangle;
    double fov_step;
    double line_height;
    int index;
    t_pxl pxl;
    float ray_x;
    float ray_y;
    t_ray ray;
    
    ray = initialRay();
    line_height = 0;
    ray_x = mlx->player.x;
    ray_y = mlx->player.y;
    mlx->dprojection = ((double)WIDTH / 2) / tan(computeDeg(FOV / 2));


    if (mlx->img.img)
        mlx_delete_image(mlx->mlx, mlx->img.img);
    mlx->img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);

    calculate_ray_and_fov(mlx, &rangle, &fov_step);
    index = 0;

    while (index < WIDTH) {
        normal_angl(rangle);
        ray = cast_ray(mlx, rangle);

        if (mlx->rays->distance == 0) {
            printf("Error: Distance is zero at index %d\n", index);
            return;
        }

        line_height = (double)size / (mlx->rays->distance * cos(computeDeg(rangle - mlx->player.position)) * mlx->dprojection);
        if (isnan(line_height) || isinf(line_height)) {
            printf("line_height computation failed: size = %d, distance = %f, cos = %f\n",
            size, mlx->rays->distance, cos(computeDeg(rangle - mlx->player.position)));
            return;
        }

        pxl.starty = (HEIGHT / 2) - (line_height / 2);
        pxl.endy = (HEIGHT / 2) + (line_height / 2);

        if (isnan(pxl.starty) || isinf(pxl.starty) || isnan(pxl.endy) || isinf(pxl.endy)) {
            printf("Error: Invalid pixel coordinates \nat index %d, line_height: %f\n", index, line_height);
            return;
        }

        printf("line_height = %f,\n pxl.starty = %f,\n pxl.endy = %f\n, index = %d\n, dprojection = %f\n",
               line_height, pxl.starty, pxl.endy, index, mlx->dprojection);

        draw_rays(mlx, index);
        rangle += fov_step;
        index++;
    }
    draw_map(mlx);
    mlx_image_to_window(mlx->mlx, mlx->img.img, 0, 0);
}
