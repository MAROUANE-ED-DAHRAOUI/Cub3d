/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 10:19:36 by med-dahr          #+#    #+#             */
/*   Updated: 2025/01/25 10:33:19 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


void	*ft_Copymem(void *dst, const void *src, size_t len)
{
	size_t			i;

	i = -1;
	if (dst == src)
		return (dst);
	if (dst < src)
		while (++i < len)
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
	else
		while (len-- > 0)
			((unsigned char *)dst)[len] = ((unsigned char *)src)[len];
	return (dst);
}
bool	check_inters(t_mlx *mlx, t_ray *ray)
{
	int	interSection_x;
	int	interSection_y;

	printf("ray->ray_x = %f\n", ray->ray_x);
	printf("ray->ray_y = %f\n", ray->ray_y);
	interSection_y = floor(ray->ray_y / size);
	interSection_x = floor(ray->ray_x / size);
	if (interSection_y < 0)
		interSection_y = 0;
	if (interSection_x < 0)
		interSection_x = 0;
	if (interSection_y > mlx->map.row - 1 || interSection_x > mlx->map.col - 1)
		return (true);
	if (mlx->map.map[interSection_y][interSection_x] == '1')
		return (true);
	return (false);
}

void	find_intersection(double x_step, double y_step, t_ray *player, t_mlx *mlx)
{
	printf("x_step = %f\n", x_step);
	printf("y_step = %f\n", y_step);
	while (check_inters(mlx, player) == false)
	{
		player->ray_x += x_step;
		player->ray_y += y_step;
	}
}

/**
 * Checks if the given ray intercepts with any obstacles in the map.
 *
 * @param mlx The mlx structure containing the map information.
 * @param ray The ray to be checked for interception.
 * @return True if the ray intercepts with an obstacle, false otherwise.
 */
bool CheckIntercept(t_mlx *mlx, t_ray *ray)
{
    // Calculate the grid coordinates of the ray's position
    int x = floor(ray->ray_x / size);
    int y = floor(ray->ray_y / size);

    // Handle out-of-bounds cases
    if (y < 0)
        y = 0;
    if (x < 0)
        x = 0;
    if (y > mlx->map.col - 1 || x > mlx->map.row - 1)
          return true;

    // Check if the grid cell contains an obstacle
    if (mlx->map.map[y][x] == '1')
        return true;
    return false;
}

/**
 * Sets the values of the ray's looks array based on the given angle.
 *
 * @param ray   The ray object.
 * @param mlx   The mlx object.
 * @param rangle The angle in degrees.
 */
static void where_look_ray(t_ray *ray, double rangle)
{
    ray->looks[1] = (rangle > 0.0 && rangle < 180.0);
    ray->looks[0] = !ray->looks[1];
    ray->looks[3] = (rangle > 90.0 && rangle < 270.0);
    ray->looks[2] = !ray->looks[3];
}

/**
 * @brief Normalizes the ray coordinates based on the map size.
 * 
 * This function ensures that the ray coordinates are within the bounds of the map.
 * If the ray's x-coordinate is greater than the maximum x-coordinate of the map, it is set to the maximum x-coordinate minus 1.
 * If the ray's x-coordinate is less than 0, it is set to 1.
 * If the ray's y-coordinate is greater than the maximum y-coordinate of the map, it is set to the maximum y-coordinate minus 1.
 * If the ray's y-coordinate is less than 0, it is set to 1.
 * 
 * @param ray Pointer to the ray structure.
 * @param mlx The mlx structure containing the map information.
 */
static void NormalizationProcessRay(t_ray *ray, t_mlx *mlx)
{
    if (ray->ray_x > ((mlx->map.col) * size))
		ray->ray_x = ((mlx->map.col) * size) - 1;
	else if (ray->ray_x < 0)
		ray->ray_x = 1;
	if (ray->ray_y > ((mlx->map.row) * size))
		ray->ray_y = ((mlx->map.row) * size) - 1;
	else if (ray->ray_y < 0)
		ray->ray_y = 1;
}

t_ray ver_intercept(t_mlx *mlx, double rangle, t_ray ray_p)
{
    t_ray ray;
    int xstep;

    if(CheckIntercept(mlx, &ray_p) == true)
    {
        ft_Copymem(&ray, &ray_p, sizeof(t_ray));
        return (ray);
    }
    where_look_ray(&ray, rangle);
    xstep = mlx->map.row * mlx->map.col;
    if (ray.looks[3])
	{
		ray.ray_x = floor(ray_p.ray_x / size) * size - 0.001;
		ray.ray_y = mlx->player.y + fabs(ray.ray_x - ray_p.ray_x) * tan(rangle * (M_PI / 180));
	}
	else
	{
		ray.ray_x = floor((ray_p.ray_x + size) / size) * size;
		ray.ray_y = ray_p.ray_y + fabs(ray.ray_x - ray_p.ray_x) * -tan(rangle * (M_PI / 180));
	}
	NormalizationProcessRay(&ray, mlx);
	return (ray);
}

static void	where_ray_looks(t_ray *ray, double rangle)
{
	ray->looks[1] = (rangle > 0.0 && rangle < 180.0);
	ray->looks[0] = !ray->looks[1];
	ray->looks[3] = (rangle > 90.0 && rangle < 270.0);
	ray->looks[2] = !ray->looks[3];
}

t_ray	hor_intercept(t_mlx *mlx, double rangle, t_ray ray_p)
{
	int		ystep;
	t_ray	ray;

	if (check_inters(mlx, &ray_p) == true)
	{
		ft_Copymem(&ray, &ray_p, sizeof(t_ray));
		return (ray);
	}
	where_ray_looks(&ray_p, rangle);
	ystep = mlx->map.row;
	if (ray.looks[1])
	{
		ray.ray_y = floor(ray_p.ray_y / size) * size - 0.001;
		ray.ray_x = ray_p.ray_x + fabs(
				ray.ray_y - ray_p.ray_y) / tan(rangle * (M_PI / 180));
	}
	else
	{
		ray.ray_y = floor(
				(ray_p.ray_y + size) / size) * size;
		ray.ray_x = ray_p.ray_x + fabs(
				ray.ray_y - ray_p.ray_y) / -tan(rangle * (M_PI / 180));
	}
	NormalizationProcessRay(&ray, mlx);
	return (ray);
}

t_ray cast_ray(t_mlx *mlx, double rangle)
{
    t_ray ray_h;
    t_ray ray_p;
    t_ray step_hor;
    t_ray step_ver;


    ray_h.ray_x = mlx->player.x * size;
    ray_h.ray_y = mlx->player.y * size;
    ft_Copymem(&ray_p, &ray_h, sizeof(t_ray));
    ray_p = ver_intercept(mlx, rangle, ray_p);
    ray_h = hor_intercept(mlx, rangle, ray_h);
    step_ver = ver_intercept(mlx, rangle, ray_p);
    step_hor = hor_intercept(mlx, rangle, ray_h);

	printf("->ray_p.ray_x = %f\n", ray_p.ray_x);
	printf("->ray_p.ray_y = %f\n", ray_p.ray_y);
	printf("->step_ver.ray_x = %f\n", step_ver.ray_x);
	printf("->step_ver.ray_y = %f\n", step_ver.ray_y);
	printf("->step_ver.ray_x - ray_p.ray_x = %f\n", step_ver.ray_x - ray_p.ray_x);
	printf("->step_ver.ray_y - ray_p.ray_y = %f\n", step_ver.ray_y - ray_p.ray_y);
    find_intersection(step_ver.ray_x - ray_p.ray_x, step_ver.ray_y - ray_p.ray_y,
		&step_ver, mlx);
	find_intersection(step_hor.ray_x - ray_h.ray_x, step_hor.ray_y - ray_h.ray_y,
		&step_hor, mlx);
	step_ver.distance = sqrt(pow(step_ver.ray_x - mlx->player.x * size, 2)
			+ pow(step_ver.ray_y - mlx->player.y * size, 2));
	step_hor.distance = sqrt(pow(step_hor.ray_x - mlx->player.x * size, 2)
			+ pow(step_hor.ray_y - mlx->player.y * size, 2));
	if ((step_hor.distance < step_ver.distance))
		return (step_hor.vertical = false, step_hor);
	return (step_ver);
}
