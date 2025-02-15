/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 03:29:18 by aaleksee          #+#    #+#             */
/*   Updated: 2025/02/15 19:31:31 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dst_data;
	unsigned char	*src_data;

	if (!dst && !src)
		return (dst);
	i = 0;
	dst_data = (unsigned char *)dst;
	src_data = (unsigned char *)src;
	while (i < n)
	{
		dst_data[i] = src_data[i];
		i++;
	}
	return (dst);
}
