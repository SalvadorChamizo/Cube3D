/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:45:13 by schamizo          #+#    #+#             */
/*   Updated: 2024/08/22 16:53:22 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*ft_remove_nl(char *str)
{
	char	*new;

	new = ft_realloc(str, ft_strlen(str));
	if (!new)
		return (NULL);
	return (new);
}