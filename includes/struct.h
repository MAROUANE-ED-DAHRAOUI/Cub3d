/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:11:59 by bbadda            #+#    #+#             */
/*   Updated: 2025/01/19 12:45:44 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_cord
{
	int	x; // x coordinate
	int	y; // y coordinate
}t_cord;

typedef struct s_point {
    float x;  // x coordinate
    float y; // y coordinate
} t_point;

typedef struct s_pxl
{
	double	i_y;
	double	starty;
	double	endy;
}		t_pxl;

typedef struct s_ray 
{
	float h;
    double distance;          // Distance to the wall
    t_point wall_hit;        // Coordinates of the wall hit
    bool 	vertical;         // True if the wall hit was vertical
	double	ray_x;			// x coordinate of the ray
	double	ray_y;			// y coordinate of the ray
	int		looks[4];		// 0 = up, 1 = down, 2 = left, 3 = right
} t_ray;



typedef struct s_texture
{
    mlx_texture_t *no;
    mlx_texture_t *so;
    mlx_texture_t *we;
    mlx_texture_t *ea;
	mlx_texture_t *current_texture;
    u_int16_t flag;
} t_texture;


typedef struct s_map
{
	int				col;
	int				row;
	int				value;
	char			**map;
	mlx_texture_t	**texture;
	char			**textures;
	char			**colors;
	int				f_color;
	int				c_color;
}t_map;

typedef struct s_player
{
	float		x;
	float		y;
	double		position;
	float		alpha;
	
}t_player;

typedef struct s_img
{
	mlx_image_t	*img;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
}t_img;

typedef struct s_mlx
{
	mlx_t		*mlx;
	t_img		img;
	mlx_image_t	*mini_img;
	t_player	player;
	t_map		map;
	t_texture	*textures;
	t_ray		*rays;
	t_pxl		pxl;
	unsigned int *texture_pixels;
	double		plyDir;
	double		dprojection;
}t_mlx;

# endif
