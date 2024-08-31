/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:26:26 by schamizo          #+#    #+#             */
/*   Updated: 2024/08/31 18:55:31 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <errno.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/include/libft.h"

# define FAILURE	1
# define SUCCESS	0

# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define WHITE		"\033[37m"
# define GREYM		"\x1B[38;5;245m"
# define GREYM2		"\x1B[38;5;250m"
# define BOLD		"\033[1m"
# define RESET		"\x1b[0m"
# define CLEAR		"\033[2J"

# define WIDTH 1920
# define HEIGHT 1280
# define FOV 60

typedef struct s_texture
{
	mlx_texture_t	*no_texture;
	mlx_texture_t	*so_texture;
	mlx_texture_t	*we_texture;
	mlx_texture_t	*ea_texture;
	mlx_texture_t	*c_texture;
	mlx_texture_t	*f_texture;
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
	char			*c_color;
	char			*f_color;
	int				no_flag;
	int				so_flag;
	int				we_flag;
	int				ea_flag;
	int				c_flag;
	int				f_flag;
}	t_texture;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	int		map_x;
	int		map_y;
	double	fov;
}	t_player;


typedef struct s_map
{
	char	**map;
	int		map_size_x;
	int		map_size_y;
	int		map_line;
}	t_map;

typedef struct s_minimap
{
	mlx_texture_t	*wall_texture;
	mlx_texture_t	*floor_texture;
	mlx_texture_t	*minipoint_texture;
	mlx_image_t		*wall;
	mlx_image_t		*floor;
	mlx_image_t		*minipoint;
}	t_minimap;

typedef struct s_data
{
	mlx_t		*mlx;
	t_map		map;
	t_minimap	mini;
	t_texture	textures;
	t_player	player;
}	t_data;

//parser

int		parse_map(char *file, t_data *data);

//get_map

int		get_map(t_data *data, int fd);
char	*get_map_loop(char *line, int fd);
int		get_map_error_and_split(t_data *data, char *map);
int		check_extra_line(char *map);
int		check_invalid_character(char c);

//get_map_utils

char	*ft_strjoin_safe(char *s1, char *s2);
char	*ft_strtrim_safe(char *s1, char *s2);

//get_texture

int		get_texture_data(t_data *data, int *error_flag, int fd);
int		get_wall_textures(t_data *data, int fd, int *error_flag);
int		get_line_and_split(char ***split_line, int fd);
int		check_texture(t_data *data, char **path, int *cont, int line);
void	check_missing_identifier(t_data *data);

//check_map_borders

int		check_side_walls(char **map);
int		check_left_wall(char *line);
int		check_right_wall(char *line);
int		check_first_line(char **map);
int		check_last_line(char **map, int last_line);

int		check_map_is_valid(t_data *data);
int		check_map_is_closed(t_data *data);
int		check_middle_lines(char **map);
int		check_invalid_character(char c);
int		check_first_last_line(t_data *data, char **map);

//check_utils

char	*ft_remove_nl(char *str);
int		ft_split_size(char **str);

//check_textures

int		check_texture_error(char **path, int line);
int		check_identifier_error(char **path, int line);
int		check_missing_path(char **path, int line);
int		check_extra_argument(char **path, int line);
int		check_texture_permission(char *name, char *texture, int line);

//textures

void	add_path_to_texture(t_data *data, char **path);
void	add_path_to_texture_2(t_data *data, char **path);
void	ft_load_textures(t_data *data);
void	free_textures_memory(t_data *data);

//errors

void	print_error(char *str);

//game

void	ft_game(t_data *data);
void	error_invalid_char(char **map, int line, int pos);
void	print_border_error(int line, int flag);

#endif