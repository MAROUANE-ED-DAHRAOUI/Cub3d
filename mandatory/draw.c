/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:27:10 by bbadda            #+#    #+#             */
/*   Updated: 2025/01/17 13:02:18 by med-dahr         ###   ########.fr       */
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

unsigned int get_rgba(uint8_t *color) 
{
    if (color == NULL || (color[0] == 0 && color[1] == 0 && color[2] == 0))
        return (0);
    return (color[0] << 24 | color[1] << 16 | color[2] << 8 | color[3]);
}

static void draw_vertical_line(t_mlx *mlx, int i_x, double *coords, unsigned int color)
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

static void	draw_rays(t_mlx *mlx, float ray_angl, int i_x)
{
    float ray_x = mlx->player.x;
    float ray_y = mlx->player.y;
    int x_texture = 0;
    int color = 0;
    double	coords[2];
    double    tstep;
    int     index = 0;

    // Cast the ray
    while (!wall(mlx, ray_x, ray_y))
    {
        ray_x += cos(ray_angl);
        ray_y -= sin(ray_angl);
    }

    // Determine if the ray hit a vertical or horizontal wall
    mlx->rays->vertical = fabs(ray_x - mlx->player.x) < fabs(ray_y - mlx->player.y);

    // Compute texture selection
    if(mlx->rays->vertical)
        mlx->textures->current_texture = mlx->textures->we;
    else
        mlx->textures->current_texture = mlx->textures->ea;

    if (cos(ray_angl) < 0)
        mlx->textures->current_texture = mlx->textures->no;
    else if (sin(ray_angl) > 0)
        mlx->textures->current_texture = mlx->textures->so;

    // Distance and scaling calculations
    mlx->rays->distance = sqrt(pow(ray_x - mlx->player.x, 2) + pow(ray_y - mlx->player.y, 2));
    mlx->rays->h = (size / mlx->rays->distance) * ((HEIGHT / 2) / tan(PI / 6));

    mlx->pxl.starty = (HEIGHT / 2) - (mlx->rays->h / 2);
    if (mlx->pxl.starty < 0)
        mlx->pxl.starty = 0;

    mlx->pxl.endy = (HEIGHT / 2) + (mlx->rays->h / 2);
    if (mlx->pxl.endy > HEIGHT)
        mlx->pxl.endy = HEIGHT;

    mlx->pxl.i_y = mlx->pxl.starty;
    tstep = (mlx->pxl.endy - mlx->pxl.starty) / size;
    
    // Calculate initial x_texture coordinate
	if (!mlx->rays->vertical) 
    	x_texture = (ray_x / size) - floor(ray_x / size) * mlx->textures->ea->width;
	else
    	x_texture = (ray_y /  mlx->textures->ea->height) - floor(ray_y / mlx->textures->ea->height) * mlx->textures->ea->width;

    while(index < size)
    {
        coords[0] = mlx->pxl.starty;
        coords[1] = mlx->pxl.starty + tstep;
        color = mlx->texture_pixels[size * index + x_texture];
        draw_vertical_line(mlx, i_x, coords, color);
        mlx->pxl.starty += tstep;
        index++;
    }
}

return (deg * (PI / 180));
void    draw(t_mlx *mlx)
{
    double	rangle;
	double	fov_step;
	double	line_height;
	int		index;
	t_pxl	pxl;
	float	ray_x;
	float	ray_y;
	float	ray_angl;
	int		i;

	ray_x = mlx->player.x;
	ray_y = mlx->player.y;
	if (mlx->img.img)
		mlx_delete_image(mlx->mlx, mlx->img.img);
	mlx->img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
    calculate_ray_and_fov(mlx, &rangle, &fov_step);
    index = 0;
    while(index < WIDTH)
    {
        normal_angl(&rangle);
        max = cast_ray(mlx, rangle);
        line_height = size / (mlx->rays->distance * cos(computeDeg(rangle - mlx->plyDir)) / tan(PI / 6));
        pxl.starty = (HEIGHT / 2) - (line_height / 2);
        draw_rays(mlx, rangle, index);
        rangle += fov_step;
    }
    draw_map(mlx);
	mlx_image_to_window(mlx->mlx, mlx->img.img, 0, 0);
}
