/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:03:11 by schamizo          #+#    #+#             */
/*   Updated: 2024/08/26 17:59:03 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static char	*copy_realloc(char *new_ptr, char *ptr, int size)
{
	int	ptr_len;

	ptr_len = ft_strlen(ptr);
	if (ptr_len > size - 1)
		ptr_len = size - 1;
	ft_memcpy(new_ptr, ptr, ptr_len);
	new_ptr[ptr_len] = '\0';
	free(ptr);
	return (new_ptr);
}

char	*ft_realloc(char *ptr, int size)
{
	char	*new_ptr;

	new_ptr = NULL;
	if (size <= 0)
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
	{
		new_ptr = malloc(sizeof(char) * size);
		return (new_ptr);
	}
	new_ptr = malloc(sizeof(char) * size + 1);
	if (!new_ptr)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = copy_realloc(new_ptr, ptr, size);
	return (new_ptr);
}
