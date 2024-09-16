/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:48:15 by schamizo          #+#    #+#             */
/*   Updated: 2024/09/16 12:01:08 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*ft_strjoin_safe(char *s1, char *s2)
{
	char	*new;

	new = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (new);
}

char	*ft_strtrim_safe(char *s1, char *s2)
{
	char	*new;

	new = ft_strtrim(s1, s2);
	if (s1)
		free(s1);
	return (new);
}

void	map_size(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!map->map)
		return ;
	while (map->map[i])
	{
		if ((int)ft_strlen(map->map[i]) > j)
			j = ft_strlen(map->map[i]);
		i++;
	}
	map->map_size_x = j;
	map->map_size_y = i;
}
