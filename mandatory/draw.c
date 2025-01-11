/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:27:10 by bbadda            #+#    #+#             */
/*   Updated: 2025/01/11 10:58:32 by med-dahr         ###   ########.fr       */
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
			y++;
		}
		x++;
    }
	draw_player(mlx, mlx->player.x, mlx->player.y, 0xFFFF00FF);
}

void draw_player(t_mlx *mlx, int x0, int y0, int color)
{
    int	x;
	int	y;
    int r;

	r = 5;
	y = y0 - r;
    while (y++ <= y0 + r) 
    {
		x = x0 - r;
        while (x++ <= x0 + r) 
        {
            if ((x - x0) * (x - x0) + (y - y0) * (y - y0) <= r * r) 
                mlx_put_pixel(mlx->img.img, x, y, color);
        }
    }
}

int mlx_get_pixel(mlx_texture_t *texture, int x, int y) {
    if (x < 0 || y < 0 || x >= (int)texture->width || y >= (int)texture->height)
        return 0; // Out of bounds, return black or transparent

    int index = (y * texture->width + x) * 4; // Assuming RGBA, 4 bytes per pixel
    int r = texture->pixels[index];
    int g = texture->pixels[index + 1];
    int b = texture->pixels[index + 2];
    int a = texture->pixels[index + 3];

    return (r << 24 | g << 16 | b << 8 | a); // Pack into int format
}


void draw_texture_slice(t_mlx *mlx, int x, float wall_height, int texture_x, int texture_index)
{
    int start = (HEIGHT / 2) - (wall_height / 2);
    int end = (HEIGHT / 2) + (wall_height / 2);
    float step = (float)mlx->map.textures[texture_index]->height / wall_height;
    float texture_y = 0;
    int y = start;

    while (y < end)
    {
        if (y >= 0 && y < HEIGHT)
        {
            int color = mlx_get_pixel(mlx->map.textures[texture_index], texture_x, (int)texture_y);
            mlx_put_pixel(mlx->img.img, x, y, color);
        }
        texture_y += step;
        y++;
    }
}

#define MAX_DIST 1000  // Prevent infinite ray loop

void draw_rays(t_mlx *mlx, float ray_angl, int i_x)
{
    float ray_x = mlx->player.x;
    float ray_y = mlx->player.y;
    float dist = 0;
    float texture_x;
    float wall_height;
    int texture_index = 0;
    float step_size = 0.05; // Step size for ray increment

    // Ray loop to find wall hit
    while (!wall(mlx, ray_y, ray_x) && dist < MAX_DIST)
    {
        ray_x += cos(ray_angl) * step_size;
        ray_y -= sin(ray_angl) * step_size;
        dist += step_size;
    }

    if (dist >= MAX_DIST) return; // No wall hit within max distance

    // Calculate wall height based on distance
    dist = sqrt(pow(ray_x - mlx->player.x, 2) + pow(ray_y - mlx->player.y, 2));
    wall_height = (size / dist) * ((HEIGHT / 2) / tan(PI / 6));

    // Determine wall hit direction (North/South or East/West)
    if (fmod(ray_y, size) < step_size) {
        texture_index = (sin(ray_angl) < 0) ? 0 : 1; // 0 = North, 1 = South
    } else {
        texture_index = (cos(ray_angl) > 0) ? 3 : 2; // 3 = East, 2 = West
    }

    // Calculate texture X-coordinate
    if (texture_index == 0 || texture_index == 1) // North/South walls
        texture_x = fmod(ray_x, size);
    else // East/West walls
        texture_x = fmod(ray_y, size);

    texture_x = (texture_x / size) * mlx->map.textures[texture_index]->width;

    // Flip texture for South/East walls
    if (texture_index == 1 || texture_index == 3)
        texture_x = mlx->map.textures[texture_index]->width - texture_x - 1;

    if (texture_x < 0) texture_x = 0; // Clamp to valid range
    if (texture_x >= mlx->map.textures[texture_index]->width)
        texture_x = mlx->map.textures[texture_index]->width - 1;

    // Draw the texture slice
    draw_texture_slice(mlx, i_x, wall_height, texture_x, texture_index);
}

    

void	draw_narrow(t_mlx *mlx, float ray_x, float ray_y, float ray_angl)
{
	int i;

	i = 0;
	while (i++ < 20 && !wall(mlx, ray_x, ray_y))
	{
		mlx_put_pixel(mlx->img.img, ray_x, ray_y, 0xFFFF00FF);
		ray_x += cos(ray_angl);
		ray_y -= sin(ray_angl);
	}
}

void draw(t_mlx *mlx) 
{
    float ray_angle = mlx->player.alpha - (PI / 6);
    int i = WIDTH;

    if (mlx->img.img)
        mlx_delete_image(mlx->mlx, mlx->img.img);
    mlx->img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);

    float step = PI / 3 / WIDTH;
    while (i >= 0)
    {
        // printf("Drawing ray %d\n", i);
        draw_rays(mlx, ray_angle, i);
        ray_angle += step;
        i--;
    }
    mlx_image_to_window(mlx->mlx, mlx->img.img, 0, 0);
}
