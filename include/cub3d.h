/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:26:26 by schamizo          #+#    #+#             */
/*   Updated: 2024/08/23 18:39:16 by schamizo         ###   ########.fr       */
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

typedef struct	s_texture
{
	mlx_texture_t	no_texture;
	mlx_texture_t	so_texture;
	mlx_texture_t	we_texture;
	mlx_texture_t	ea_texture;
	mlx_texture_t	c_texture;
	mlx_texture_t	f_texture;
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
	char			*c_color;
	char			*f_color;
}	t_texture;

typedef struct	s_data
{
	mlx_t		*mlx;
	t_texture	textures;
}	t_data;

//parser

int		parse_map(char *file, t_data *data);

//check_utils

char	*ft_remove_nl(char *str);

//errors

void	print_error(char *str);

#endif