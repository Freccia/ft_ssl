/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <lfabbro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 20:14:53 by lfabbro           #+#    #+#             */
/*   Updated: 2018/12/15 23:13:59 by lfabbro          ###   ########.fr       */
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

static uint8_t	b64_decode_unit(uint8_t e)
{
	if (e >= 'A' && e <= 'Z')
		return (e - 'A');
	else if (e >= 'a' && e <= 'z')
		return (e - 'a' + 26);
	else if (e >= '0' && e <= '9')
		return (e - '0' + 52);
	else if (e == '+')
		return (62);
	else if (e == '/')
		return (63);
	return ('\0');
}

void			b64_decode(const uint8_t *enc, uint32_t len, uint8_t *data)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	k;
	uint8_t		valid;
	uint8_t		blk[4] = {0};

	i = 0;
	j = 0;
	valid = 1;
	while (i < len)
	{
		k = 0;
		valid = 1;
		while (k < 4)
		{
			if (enc[i + k] == '\n')
				++i;
			if (i + k < len && valid)
			{
				blk[k] = b64_decode_unit(enc[i + k]);
			}
			else
			{
				blk[k] = '\0';
				valid = 0;
			}
			++k;
		}
		data[j] = ((blk[0] & 0x3f) << 2) | ((blk[1] & 0x30) >> 4);
		data[++j] = ((blk[1] & 0x0f) << 4) | ((blk[2] & 0x3c) >> 2);
		data[++j] = ((blk[2] & 0x03) << 6) | ((blk[3] & 0x3f) >> 0);
		data[++j] = '\0';
		i += 4;
	}
}
