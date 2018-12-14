/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <lfabbro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 20:14:53 by lfabbro           #+#    #+#             */
/*   Updated: 2018/12/14 15:11:04 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64.h"
#include <sys/types.h>

const char b64[] =
			"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void	b64_encode(const uint8_t *data, uint32_t len, uint8_t *encoded)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	j = 0;
	while (i < len)
	{
		encoded[j] = (uint8_t)b64[data[i] >> 2];
		encoded[j + 1] = (uint8_t)b64[((data[i] & 0x03) << 4) | ((data[i + 1] & 0xf0) >> 4)];
		encoded[j + 2] = (uint8_t)(i + 1 < len) ?
				b64[((data[i + 1] & 0x0f) << 2) | ((data[i + 2] & 0xc0) >> 6)] : '=';
		encoded[j + 3] = (uint8_t)(i + 2 < len) ? b64[data[i + 2] & 0x3f] : '=';
		encoded[j + 4] = '\0';
		i += 3;
		j += 4;
	}
}
