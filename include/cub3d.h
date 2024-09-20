/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:26:26 by schamizo          #+#    #+#             */
/*   Updated: 2024/09/20 16:00:22 by schamizo         ###   ########.fr       */
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
# define WALL_SIZE 640

typedef struct s_texture
{
	mlx_texture_t	*no_texture;
	mlx_texture_t	*so_texture;
	mlx_texture_t	*we_texture;
	mlx_texture_t	*ea_texture;
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
	unsigned int	c_color;
	unsigned int	f_color;
	int				no_flag;
	int				so_flag;
	int				we_flag;
	int				ea_flag;
	int				c_flag;
	int				f_flag;
}	t_texture;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_line
{
	int	x; //the x coordinate of line relative to screen
	int	y; //the current pixel index of the line (along y axis)
	int	y0; //y start index of drawing texture
	int	y1; //y end index of drawing texture
	int	tex_x; //x coordinate of texture to draw
	int	tex_y; //y coordinate of texture to draw
}	t_line;

typedef struct s_ray
{
	double		angle;
	double		angle_ret;
	int			map_x;
	int			map_y;
	double		pos_x;
	double		pos_y;
	double		ray_dir_x;
	double		ray_dir_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		step_x;
	double		step_y;
	double		side_dist_x;
	double		side_dist_y;
	double		perp_wall_dist;
	double		pixel_width_impact;
	int			flag;
	double		hit;
	double		hyp_distance;
	double		ver_distance;
}	t_ray;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	int		map_x;
	int		map_y;
	double	angle;
	t_ray	ray[WIDTH];
}	t_player;

typedef struct s_map
{
	char	**map;
	int		map_size_x;
	int		map_size_y;
	int		map_line;
}	t_map;

typedef struct s_data
{
	char			*file;
	mlx_t			*mlx;
	mlx_image_t		*background;
	mlx_image_t		*walls;
	t_map			map;
	t_texture		textures;
	t_player		player;
	int				ray_number;
	int				move;
}	t_data;

/* --------------------------GAME------------------------------- */

//game

void		image_init(t_data *data, mlx_image_t **image);
void		ft_hook(void *param);
void		game_init(t_data *data);
void		ft_game(t_data *data);

//game_move

void		handle_player_movement(t_data *data);
void		handle_player_rotation(t_data *data);
void		move_player_by_angle(t_data *data, double angle);
void		adjust_angle(double *angle, double var);

//game_check_move

bool		check_move_is_valid(t_data *data, double move_x, double move_y);
bool		update_move(t_data *data, double move_x, double move_y);

//init_variables

void		init_texture_flags(t_data *data);
void		init_player_variables(t_data *data);
void		init_texture_variables(t_data *data);
int			init_data_variables(t_data *data);

/* --------------------------PARSER------------------------------- */

//parser

int			parse_map(char *file, t_data *data);
int			check_map_is_valid(t_data *data);

//parser_errors

void		print_error(char *str);
void		error_invalid_char(char **map, int line, int pos);
void		print_border_error(int line, int flag);
void		print_invalid_space_error(int line, int pos);
void		rgb_error_not_number(char **color, int i, int j, int line);

//get_texture

int			get_texture_data(t_data *data, int *error_flag, int *fd);
int			get_wall_textures(t_data *data, int *fd, int *error_flag);
int			get_line_and_split(char ***split_line, int fd);
int			check_texture(t_data *data, char **path, int *cont, int line);
void		check_missing_identifier(t_data *data, int *fd, int cont);

//get_texture_utils

int			count_missing_identifier(t_data *data);
void		set_new_fd(t_data *data, int cont, int *fd);

//get_map

int			get_map(t_data *data, int fd);
char		*get_map_loop(char *line, int fd);
int			get_map_error_and_split(t_data *data, char *map);
int			check_extra_line(char *map);

//get_map_utils

char		*ft_strjoin_safe(char *s1, char *s2);
char		*ft_strtrim_safe(char *s1, char *s2);
void		map_size(t_map *map);

//check_utils

char		*ft_remove_nl(char *str);
int			ft_split_size(char **str);
int			count_commas(char **color);
int			check_colors_format(char **path, int line);

//check_textures

int			check_texture_error(char **path, int line);
int			check_identifier_error(char **path, int line);
int			check_missing_path(char **path, int line);
int			check_extra_argument(char **path, int line);
int			check_texture_permission(char *name, char *texture, int line);

//check_textures_rgb

uint32_t	get_color_rgb(char **path);
uint32_t	get_color_rgb_two_args(char **path);
uint32_t	get_color_rgb_four_args(char **path);
void		error_rgb_value(char **path, int r, int g, int b);
int			check_rgb_are_numbers(char **color, int line);

//check_map

int			check_map_extension(char *file, int *error_flag);
int			check_first_last_line(t_data *data, char **map);
int			check_invalid_character(char c);
int			check_middle_lines(char **map);
int			check_map_is_closed(t_data *data);

//check_map_spaces

int			check_if_valid_spaces(char **map);
int			check_up_down_space(char **map, int i, int j, int flag);
int			check_left_right_space(char **map, int i, int j, int flag);

//check_map_player

int			count_players_in_map(char **map);
int			check_players_in_map(char **map);
void		find_player_position(t_data *data, char **map);

//check_map_borders

int			check_side_walls(char **map);
int			check_left_wall(char *line);
int			check_right_wall(char *line);
int			check_first_line(char **map);
int			check_last_line(char **map, int last_line);

/* --------------------------RAYCASTING--------------------------- */

//ray

void		set_player_angle(t_data *data, char c);
void		ray_init(t_data *data);

//angles_maker

void		calculate_side_distance(t_data *data, t_ray *ray);
void		calculate_vertical_distance(t_data *data, t_ray *ray);
void		dda_loop(t_data *data, t_ray *ray);
void		find_ray_hit_point(t_data *data, t_ray *ray);
void		print_ray(t_data *data, t_player *player);

//angles_maker_utils

void		ver_pixel_impact(t_ray *ray);
void		hor_pixel_impact(t_ray *ray);
void		init_ray_variables(t_data *data, t_ray *ray);
void		calculate_hypotenuse_distance(t_ray *ray);

/* ------------------------PRINT_AND_TEXTURES------------------------ */

//textures

void		add_path_to_texture(t_data *data, char **path);
void		add_path_to_texture_2(t_data *data, char **path);
void		ft_load_textures(t_data *data);
void		free_textures_memory(t_data *data);
void		ft_delete_textures(t_data *data);

//print_wall

uint32_t	get_pixel_color(double ratio_x, double wall_size, \
	mlx_texture_t *texture);
uint32_t	get_wall_color(t_data *data, t_ray *ray, double wall_size);
void		print_wall_column(t_data *data, t_ray *ray, int x);

//print_wall_utils

double		get_wall_size(t_ray *ray);
uint32_t	pack_rgba(uint8_t pixels[4]);

//print_floor_ceiling

int			paint_floor_ceiling(t_data *data);

//printer
void		print_one_ray(t_data *data, t_ray *ray);
void		print_wall(t_data *data, t_ray *ray, int x);
double		get_wall_size(t_ray *ray);
uint32_t	vert_wall(t_data *data, t_ray *ray, double wall_size);
uint32_t	get_pixel_color(double ratio_x, \
				double wall_size, mlx_texture_t *texture);

#endif