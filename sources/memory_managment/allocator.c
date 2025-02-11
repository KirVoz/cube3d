/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:25:51 by aaleksee          #+#    #+#             */
/*   Updated: 2025/02/06 13:18:36 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	*s_alloc(size_t count, size_t size)
{
	void	*allocated_memory;

	allocated_memory = calloc(count, size);
	if (!allocated_memory)
		exit_fail("Failed to allocate memory");
	return (allocated_memory);
}

void	*s_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*reallocated_memory;
	reallocated_memory = ft_realloc(ptr, old_size, new_size);
	if (!reallocated_memory)
		exit_fail("Failed to reallocate memory");
	return (reallocated_memory);
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	size;

	if (old_size < new_size && old_size != 0)
		size = old_size;
	else
		size = new_size;
	if (!ptr)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	ft_bzero(new_ptr, new_size);
	ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}