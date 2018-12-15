/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <lfabbro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 20:14:53 by lfabbro           #+#    #+#             */
/*   Updated: 2018/12/15 12:59:51 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64.h"
#include <sys/types.h>

const char b64[] =
			"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void	b64_encode(const uint8_t *data, uint32_t len, uint8_t *enc)
{
	uint32_t	i;
	uint32_t	j;

	//ft_printf("ENCODE\n");
	i = 0;
	j = 0;
	while (i < len)
	{
		enc[j] = (uint8_t)b64[data[i] >> 2];
		enc[++j] = (uint8_t)b64[((data[i] & 0x03) << 4) | ((data[i + 1] & 0xf0) >> 4)];
		enc[++j] = (uint8_t)(i + 1 < len) ?
				b64[((data[i + 1] & 0x0f) << 2) | ((data[i + 2] & 0xc0) >> 6)] : '=';
		enc[++j] = (uint8_t)(i + 2 < len) ? b64[data[i + 2] & 0x3f] : '=';
		enc[++j] = '\0';
		i += 3;
	}
}

void	b64_decode(const uint8_t *enc, uint32_t len, uint8_t *data)
{
	uint32_t	i;
	uint32_t	j;

	ft_printf("DECODE\n");
	i = 0;
	j = 0;
	while (i < len)
	{
		data[j] = ((enc[i] & 0x0f) << 2) | ((enc[i + 1] & 0x03) >> 4);
		data[++j] = ((enc[i + 1] & 0x03) << 4) | ((enc[i + 2] & 0x0f) >> 2);
		data[++j] = ((enc[i + 2] & 0x03) << 6) | ((enc[i + 3] & 0x0f) >> 0);
		data[++j] = '\0';
	/*
		data[j] =       enc[i] << 2 | enc[i + 1] >> 4;
		data[++j] = enc[i + 1] << 4 | enc[i + 2] >> 2;
		data[++j] = enc[i + 2] << 6 | enc[i + 3] >> 0;
		data[++j] = '\0';
	*/
		i += 3;
	}
}
