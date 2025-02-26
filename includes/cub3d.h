/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:45:25 by bbadda            #+#    #+#             */
/*   Updated: 2025/01/25 21:16:30 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX/include/MLX42/MLX42.h"
# include "errors.h"
# include "struct.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <math.h>
#include <float.h>

#define  FOV 60
# define PI 3.1415926535897
#define  WALL_PADDING 10 
# define size 32
# define BUFFER_SIZE 42
# define WIDTH 1900
# define HEIGHT 1000
# define MLX_KEY_ESC 256
# define MLX_KEY_W 87
# define MLX_KEY_S 83
# define MLX_KEY_D 68
# define MLX_KEY_A 65
# define MLX_KEY_R_RIGHT 263
# define MLX_KEY_R_LEFT 262
#define MINI_MAP_SCALE 0.2 // Mini-map is 20% of the actual size
#define SPEED_ROTATE 0.1
#define SPEED_PLY 0.1

int			get_colors(char *str);
int			cmp(const char *s1, const char *s2);
int			n_cmp(const char *s1, const char *s2, size_t n);
void		check_file_type(char *s);
void		__error(int index, int fd);
void		__error2(int index);
//-------------------------get_next_line------------------------------------//
size_t		__lenline(char *stow);
char		*get_next_line(int fd);
char		*__linechr(char *str, int c);
char		*__dupline(char *stow);
char		*__joinline(char *stow, char *buffer);
char		*__subline(char *stow, unsigned int start, size_t len);
char		*__linesub(char *stow, unsigned int start, size_t len);
//------------------------libc_functions------------------------------------//
char		**parse_split(char const *s, char c);
char		*parse_substr(char const *str, unsigned int start, size_t len);
char		*parse_strdup(const char *src);
size_t		parse_strlen(const char *str);
int			__isdigit(int nb);
int			__isalnum(int k);
//---------------------parsing_map_functions--------------------------------//
void		read_and_fill_map(char *str, t_mlx *mlx);
void		check_valid_map(char *map, t_mlx *mlx);
// -----------------------draw_functions------------------------------------//
void        draw_map(t_mlx *mlx);
void        draw_mini_map(t_mlx *mlx);
void		draw_player(t_mlx *mlx, int x0, int y0, int color);
void        draw(void *frr);

bool        wall(t_mlx *mlx, float px, float py);
//------------------------init_functions-----------------------------------//
void        __create_window(t_mlx *mlx);
int	        player_position(t_mlx *mlx, int i, int j);
void		get_cordinante(t_mlx *mlx, t_cord *cord);

void    print(t_mlx *mlx);
double 	normal_angl(double angle);
void    free_textures(t_mlx *mlx);
t_ray   cast_ray(t_mlx *mlx, double rangle);
int	     PlayerCounter(t_mlx *mlx);
char	*ft_strchr(const char *s, int c);
int	    space_surrounding(t_mlx *mlx, int i, int j);
double  computeDeg(double angle);
void	move_player(t_mlx *mlx);
char	*ExtractPathNorthTex(char *line);
char	*ExtractPathSouthTex(char *line);
char	*ExtractPathWestTex(char *line);
char	*ExtractPathEastTex(char *line);
void	ParseLineExtractAssets(char *line, t_mlx *mlx);
char	*ft_strdup(const char *s1);
void	*ft_calloc(size_t count, size_t _size);
char	*ft_substr(const char *s, unsigned int start, size_t len);
int	    ft_atoi(const char *str);
void	ft_free(char **str);
unsigned int	    F_color(char *line);
unsigned int	    C_color(char *line);
unsigned int	_rgba(int r, int g, int b, int a);
int	    ExtractsAssetsFromFile(char *map, t_mlx *mlx);
int	    ExtractAssetsRows(int fd, char **map);
char	*ft_strtrim(char const *s1, char const *set);
int     check_map(t_mlx *mlx);
void	find_intersection(double x_step, double y_step, t_ray *player, t_mlx *mlx);
void	ParseLineExtractAssets(char *line, t_mlx *mlx);
int  my_strlen(char *str);


#endif