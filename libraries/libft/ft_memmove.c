/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 04:08:13 by aaleksee          #+#    #+#             */
/*   Updated: 2025/02/13 03:43:46 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dst_temp;
	unsigned const char	*src_temp;

	if (!dst && !src)
		return (NULL);
	dst_temp = (unsigned char *)dst;
	src_temp = (unsigned const char *)src;
	if (dst <= src || dst >= src + len)
		while (len--)
			*dst_temp++ = *src_temp++;
	else
	{
		dst_temp += len - 1;
		src_temp += len - 1;
		while (len--)
			*dst_temp-- = *src_temp--;
	}
	return (dst);
}
