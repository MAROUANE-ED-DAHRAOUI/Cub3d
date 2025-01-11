/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:45:25 by bbadda            #+#    #+#             */
/*   Updated: 2025/01/11 14:46:01 by med-dahr         ###   ########.fr       */
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

# define PI 3.1415926535897
# define size 40
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

int			get_colors(char *str);
size_t		my_strlen(const char *str);
int			cmp(const char *s1, const char *s2);
int			n_cmp(const char *s1, const char *s2, size_t n);
void		check_file_type(const char *s);
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
void        draw(t_mlx *mlx);
bool        wall(t_mlx *mlx, float px, float py);
//------------------------init_functions-----------------------------------//
void        __create_window(t_mlx *mlx);
void        player_position(t_mlx *mlx);
void		get_cordinante(t_mlx *mlx, t_cord *cord);
//--------------------player_move_functions-------------------------------//
void        player_move(mlx_key_data_t data, void *param);

void    print(t_mlx *mlx);

# define TILE_SIZE 32
# define WIDTH 1600
# define HEIGHT 1000
# define FOV 1.0471975512 // 60 degrees
# define RAD 0.0174532925 // Radians per degree
# define SPEED 2

typedef struct s_coor {
    double x;
    double y;
} t_coor;

typedef struct s_player {
    t_coor coor;
    double angle;
} t_player;

typedef struct s_map {
    char **grid;
    int width;
    int height;
} t_map;

typedef struct s_rgb {
    int r;
    int g;
    int b;
} t_rgb;

typedef struct s_color {
    t_rgb floor;
    t_rgb ceiling;
    uint16_t flags;
} t_color;

typedef struct s_texture {
    char *north;
    char *south;
    char *east;
    char *west;
    uint16_t flags;
} t_texture;

typedef struct s_data {
    t_map map;
    t_player player;
    t_texture textures;
    t_color colors;
    mlx_t *mlx;
    mlx_image_t *frame;
    mlx_texture_t *tex_north;
    mlx_texture_t *tex_south;
    mlx_texture_t *tex_east;
    mlx_texture_t *tex_west;
} t_data;

// Function prototypes
void init_mlx(t_data *data);
void load_textures(t_data *data);
void render_frame(t_data *data);
void handle_input(t_data *data);
void cleanup(t_data *data);
#endif


// #ifndef CUB3D_H
// # define CUB3D_H

// # include <unistd.h>
// # include <stdio.h>
// # include <fcntl.h>
// # include <math.h>
// # include "../utils/MLX42/include/MLX42/MLX42.h"
// # include "../utils/libft/libft.h"


// #endif // CUB3D_H