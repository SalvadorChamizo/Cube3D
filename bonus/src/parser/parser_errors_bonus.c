/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:30:17 by schamizo          #+#    #+#             */
/*   Updated: 2024/09/16 11:04:58 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

void	print_error(char *str)
{
	ft_putstr_fd(RED"Error: "RESET, 2);
	ft_putstr_fd(str, 2);
}

void	error_invalid_char(char **map, int line, int pos)
{
	print_error("Invalid character \"");
	ft_putchar_fd(map[line][pos], 2);
	ft_putstr_fd("\" in map at line ", 2);
	ft_putnbr_fd(line + 1, 2);
	ft_putstr_fd(":", 2);
	ft_putnbr_fd(pos + 1, 2);
	ft_putstr_fd(".\n", 2);
}

void	print_border_error(int line, int flag)
{
	if (flag == 1)
	{
		print_error("The left side of the map is not close at line ");
		ft_putnbr_fd(line + 1, 2);
		ft_putstr_fd(".\n", 2);
	}
	if (flag == 2)
	{
		print_error("The right side of the map is not close at line ");
		ft_putnbr_fd(line + 1, 2);
		ft_putstr_fd(".\n", 2);
	}
}

void	print_invalid_space_error(int line, int pos)
{
	print_error("Detected invalid space in line ");
	ft_putnbr_fd(line + 1, 2);
	ft_putstr_fd(":", 2);
	ft_putnbr_fd(pos + 1, 2);
	ft_putstr_fd(".\n", 2);
}

void	rgb_error_not_number(char **color, int i, int j, int line)
{
	print_error("Invalid character \"");
	ft_putchar_fd(color[i][j], 2);
	ft_putstr_fd("\" in line ", 2);
	ft_putnbr_fd(line, 2);
	ft_putstr_fd(". \n", 2);
}
