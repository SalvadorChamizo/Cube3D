/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:41:06 by saroca-f          #+#    #+#             */
/*   Updated: 2024/09/19 14:55:57 by saroca-f         ###   ########.fr       */
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

uint32_t get_plane_pixel_color(double x, double y, mlx_texture_t *texture)
{
    uint32_t index;
    uint8_t rgba[4];
    unsigned int i;

    i = 0;
    if (!texture || !texture->pixels || x >= texture->width || y >= texture->height)
        return 0;

    index = ((uint32_t)y * texture->width + (uint32_t)x) * texture->bytes_per_pixel;
    while (i < 4)
    {
        rgba[i] = texture->pixels[index + i];
        i++;
    }
    return pack_rgba(rgba);
}

/*uint32_t get_plane_pixel_color(double x, double y, mlx_texture_t *texture)
{
    uint32_t index;
    uint8_t rgba[4];
    unsigned int i;

    i = 0;
    if (!texture || !texture->pixels || x >= texture->width || y >= texture->height)
        return 0;

    index = ((uint32_t)y * texture->width + (uint32_t)x) * texture->bytes_per_pixel;
    while (i < 4)
    {
        rgba[i] = texture->pixels[index + i];
        i++;
    }
    return pack_rgba(rgba);
}*/

#define ANIMATION_WIDTH 750
#define ANIMATION_HEIGHT 500

void draw_animation(t_data *data, mlx_texture_t *texture)
{
    uint32_t color;
    int i, j;
    double scale_x, scale_y;
    int target_x, target_y;

    // Calculate the scaling factors
    scale_x = (double)texture->width / (ANIMATION_WIDTH);
    scale_y = (double)texture->height / (ANIMATION_HEIGHT);

    // Calculate the starting position for the animation (bottom center)
    target_x = (WIDTH - ANIMATION_WIDTH);
    target_y = HEIGHT - ANIMATION_HEIGHT; // 10 pixels from the bottom

    for (i = 0; i < ANIMATION_WIDTH; i++)
    {
        for (j = 0; j < ANIMATION_HEIGHT; j++)
        {
            color = get_plane_pixel_color(i * scale_x, j * scale_y, texture);
			if (color != 0)
           		mlx_put_pixel(data->walls, target_x + i, target_y + j, color);
        }
    }
}

/*void	draw_animation(t_data *data, mlx_texture_t *texture)
{
	uint32_t color;
	int	i;
	int	j;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			color = get_plane_pixel_color(i, j, texture);
			mlx_put_pixel(data->walls, i, j, color);
			j++;
		}
		i++;
	}
}*/

void	charge_animation_textures(t_data *data)
{
	data->animation.animation_1 = mlx_load_png("./textures/tile000.png");
	if (!data->animation.animation_1)
		printf("Falla aquí\n");
	data->animation.animation_2 = mlx_load_png("./textures/tile001.png");
	data->animation.animation_3 = mlx_load_png("./textures/tile002.png");
	data->animation.animation_4 = mlx_load_png("./textures/tile003.png");
	data->animation.animation_5 = mlx_load_png("./textures/tile004.png");
}

void	loop_animation_texture(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_SPACE) || mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		if (data->animation_loop == 0)
			draw_animation(data, data->animation.animation_1);
		if (data->animation_loop == 1)
			draw_animation(data, data->animation.animation_2);
		if (data->animation_loop == 2)
			draw_animation(data, data->animation.animation_3);
		if (data->animation_loop == 3)
			draw_animation(data, data->animation.animation_4);
		if (data->animation_loop == 4)
			draw_animation(data, data->animation.animation_5);
		data->animation_loop++;
		if (data->animation_loop == 5)
			data->animation_loop = 0;
	}
	else
		data->animation_loop = 0;
	if (data->animation_loop == 0)
		draw_animation(data, data->animation.animation_1);
	/*if (data->animation_loop == 5)
		data->animation_loop = 0;
	if (data->animation_loop == 1)
		draw_animation(data, data->animation.animation_2);
	if (data->animation_loop == 2)
		draw_animation(data, data->animation.animation_3);
	if (data->animation_loop == 3)
		draw_animation(data, data->animation.animation_4);
	if (data->animation_loop == 4)
		draw_animation(data, data->animation.animation_5);*/
}

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
	handle_player_movement(data);
	handle_player_rotation(data);
	image_init(data, &data->walls);
	image_init(data, &data->bonus);
	print_ray(data, &data->player);
	make_minimap(data);
	loop_animation_texture(data);
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

void	key_press(struct mlx_key_data key_data, void *param)
{
	t_data	*data;
	
	data = (t_data *)param;
	if (key_data.key == MLX_KEY_F && key_data.action == MLX_PRESS)
		door_manage(data);
}

void	ft_game(t_data *data)
{
	game_init(data);
	charge_animation_textures(data);
	data->animation_loop = 0;
	mlx_loop_hook(data->mlx, ft_hook, data);
	mlx_cursor_hook(data->mlx, &mouse_move, data);
	mlx_key_hook(data->mlx, key_press, data);
	mlx_loop(data->mlx);
}
