/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:11:59 by bbadda            #+#    #+#             */
/*   Updated: 2025/02/19 23:13:22 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct f_color
{
	int				tex_y;
	int				res;
	int				x;
	int				y;
	int				z;
	unsigned int	x1;
	unsigned int	y1;
	unsigned int	z1;
	int				x_bin;
	int				y_bin;
	mlx_texture_t	*tx;
}				t_color;

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
	int			side;
}t_player;

typedef struct s_img
{
	mlx_image_t	*img;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
	mlx_image_t			*north;
	mlx_image_t			*south;
	mlx_image_t			*west;
	mlx_image_t			*east;
	int					**px_north;
	int					**px_south;
	int					**px_west;
	int					**px_east;
} t_img;

typedef struct s_direct
{
	char				*north;
	char				*south;
	char				*west;
	char				*east;
}						t_direct;

typedef struct s_mlx
{
	t_direct 	direct;
	mlx_t		*mlx;
	t_img		img;
	mlx_image_t	*mini_img;
	t_player	player;
	t_map		map;
	mlx_texture_t *txx;
} t_mlx;

# endif