/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5_tool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 16:04:50 by lfabbro           #+#    #+#             */
/*   Updated: 2018/10/04 16:38:07 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

/*
** Decodes input (unsigned char) into output (uint32_t). Assumes len is
** a multiple of 4.
** Convert to big endian
*/

void		decode(uint32_t *output, const uint8_t *input, uint32_t len)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	j = 0;
	while (j < len)
	{
		output[i] = ((uint32_t)input[j])
					| (((uint32_t)input[j + 1]) << 8)
					| (((uint32_t)input[j + 2]) << 16)
					| (((uint32_t)input[j + 3]) << 24);
		++i;
		j += 4;
	}
}

/*
** Encodes input (uint32_t) into output (unsigned char). Assumes len is
** a multiple of 4.
** Convert to little endian
** Encodes input (UINT4) into output (unsigned char). Assumes len is
** a multiple of 4.
*/

void		encode(uint8_t *output, uint32_t *input, unsigned int len)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	j = 0;
	while (j < len)
	{
		output[j] = (uint8_t)(input[i] & 0xff);
		output[j + 1] = (uint8_t)((input[i] >> 8) & 0xff);
		output[j + 2] = (uint8_t)((input[i] >> 16) & 0xff);
		output[j + 3] = (uint8_t)((input[i] >> 24) & 0xff);
		j += 4;
		++i;
	}
}
