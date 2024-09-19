/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:41:06 by saroca-f          #+#    #+#             */
/*   Updated: 2024/09/19 10:51:27 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

void	image_init(t_data *data, mlx_image_t **image)
{
	*image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!*image)
	{
		print_error("Failed creating floor-ceiling image\n");
		exit(FAILURE);
	}
	if (mlx_image_to_window(data->mlx, *image, 0, 0) == -1)
	{
		print_error("Failed in mlx_image_to_window() for \
			floor-ceiling image\n");
		exit(FAILURE);
	}
}

/*void	door_open_close(char *door)
{
	if (*door == 'D')
		*door = 'C';
	else if (*door == 'C')
		*door = 'D';
}

bool	check_door(t_data *data)
{
	int check_x;
	int check_x2;
	int check_y;
	int check_y2;

	check_x = (int)floor((data->player.pos_x + 0.25));
	check_x2 = (int)floor((data->player.pos_x - 0.25));
	check_y = (int)floor((data->player.pos_y + 0.25));
	check_y2 = (int)floor((data->player.pos_y - 0.25));
	if (data->map.map[check_y][check_x] == 'C')
		return (false);
	if (data->map.map[check_y2][check_x] == 'C')
		return (false);
	if (data->map.map[check_y][check_x2] == 'C')
		return (false);
	if (data->map.map[check_y2][check_x2] == 'C')
		return (false);
	return (true);
}

void	door_manage(t_data *data)
{
	double		ver_x;
	double		ver_y;

	if (!check_door(data))
		return ;
	ver_x = data->player.pos_x - data->player.map_x - 0.5;
	ver_y = data->player.pos_y - data->player.map_y - 0.5;
	if (fabs(ver_y) > fabs(ver_x))
	{
		if (ver_y > 0)
			door_open_close(&data->map.map[data->player.map_y + 1][data->player.map_x]);
		else
			door_open_close(&data->map.map[data->player.map_y - 1][data->player.map_x]);
	}
	else
	{
		if (ver_x > 0)
			door_open_close(&data->map.map[data->player.map_y][data->player.map_x + 1]);
		else
			door_open_close(&data->map.map[data->player.map_y][data->player.map_x - 1]);
	}
}*/

void	ft_hook(void *param)
{
	t_data		*data;

	data = param;
	if (data->player.ray[0].delta_dist_y)
	{
		mlx_delete_image(data->mlx, data->walls);
		mlx_delete_image(data->mlx, data->bonus);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_F))
		door_manage(data);
	handle_player_movement(data);
	handle_player_rotation(data);
	image_init(data, &data->walls);
	image_init(data, &data->bonus);
	print_ray(data, &data->player);
	make_minimap(data);
}

void	game_init(t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);
	if (!data->mlx)
	{
		print_error("Failed to disable the mouse.\n");
		exit(1);
	}
	image_init(data, &data->background);
	image_init(data, &data->walls);
	image_init(data, &data->bonus);
	data->move = 4;
	find_player_position(data, data->map.map);
	data->prev_map_x = 0;
	data->prev_map_y = 0;
	paint_floor_ceiling(data);
}

void	mouse_move(double xpos, double ypos, void *param)
{
	t_data	*data;
	double	diff_mouse_x;

	data = (t_data *)param;
	(void)ypos;
	if (data->prev_mouse_x == -1)
		data->prev_mouse_x = xpos;
	diff_mouse_x = data->prev_mouse_x - xpos;
	data->prev_mouse_x = xpos;
	if (diff_mouse_x < 0)
	{
		data->player.angle = data->player.angle + 0.3;
		if (data->player.angle > 359)
			data->player.angle = 0;
	}
	else if (diff_mouse_x > 0)
	{
		data->player.angle = data->player.angle - 0.3;
		if (data->player.angle < 0)
			data->player.angle = 359;
	}
}

void	ft_game(t_data *data)
{
	game_init(data);
	mlx_loop_hook(data->mlx, ft_hook, data);
	mlx_cursor_hook(data->mlx, &mouse_move, data);
	mlx_loop(data->mlx);
}
