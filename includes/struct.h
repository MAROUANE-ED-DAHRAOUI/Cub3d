/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:11:59 by bbadda            #+#    #+#             */
/*   Updated: 2025/01/14 14:38:54 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_cord
{
	int	x;
	int	y;
}t_cord;

typedef struct s_point {
    float x;
    float y;
} t_point;

typedef struct s_ray {
    float distance;          // Distance to the wall
    t_point wall_hit;        // Coordinates of the wall hit
    bool vertical;           // True if the wall hit was vertical
} t_ray;



typedef struct s_texture
{
    mlx_texture_t *no;
    mlx_texture_t *so;
    mlx_texture_t *we;
    mlx_texture_t *ea;
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
	float		position;
	float	alpha;
	
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
}t_mlx;

# endif