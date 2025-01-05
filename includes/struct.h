/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:11:59 by bbadda            #+#    #+#             */
/*   Updated: 2024/12/01 15:37:33 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_cord
{
	int	x;
	int	y;
}t_cord;

typedef struct s_map
{
	int		col;
	int		row;
	int		value;
	char	**map;
	char	**textures;
	char	**colors;
	int		f_color;
	int		c_color;
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

typedef struct s_texture
{
    mlx_texture_t *north;
    mlx_texture_t *south;
    mlx_texture_t *east;
    mlx_texture_t *west;
} t_texture;

typedef struct s_mlx
{
	mlx_t		*mlx;
	t_img		img;
	mlx_image_t	*mini_img;
	t_player	player;
	t_map		map;
	t_texture       texture;  // Add this line for textures
}t_mlx;



# endif