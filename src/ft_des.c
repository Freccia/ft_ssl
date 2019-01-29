/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_des.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <>                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 15:12:44 by marvin            #+#    #+#             */
/*   Updated: 2019/01/29 16:35:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"
#include "libft/include/libft.h"
#include <inttypes.h>

int pc_1[] = {57, 49,  41, 33,  25,  17,  9,
			   1, 58,  50, 42,  34,  26, 18,
			  10,  2,  59, 51,  43,  35, 27,
			  19, 11,   3, 60,  52,  44, 36,
			  63, 55,  47, 39,  31,  23, 15,
			   7, 62,  54, 46,  38,  30, 22,
			  14,  6,  61, 53,  45,  37, 29,
			  21, 13,   5, 28,  20,  12,  4};

int ks_shift[] = {-1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

void		gen_subkeys(uint8_t *key, t_keyset *ks)
{
	int32_t		i;
	int32_t		j;
	int32_t		shift_size;
	uint8_t		shift_byte;
	uint8_t		shift_bits;

	ft_memset(ks[0].k, 0, sizeof(ks[0].k));

	i = 0;
	while (i < 8)
	{
		shift_size = pc_1[i] - 1;
		shift_byte = 0x80 >> (shift_size % 8);
		shift_byte &= key[shift_size / 8];
		shift_byte <<= shift_size % 8;
		ks[0].k[i / 8] |= (shift_byte >> (i % 8));
		++i;
	}

	i = 0;
	while (i < 3)
	{
		ks[0].c[i] = ks[0].k[i];
		++i;
	}
	ks[0].c[3] = ks[0].k[3] & 0xF0;

	j = 0;
	while (j < 3)
	{
		ks[0].d[j] = (ks[0].k[i] & 0x0F) << 4;
		ks[0].d[j] |= (ks[0].k[++i] & 0xF0) >> 4;
		++j;
	}
	ks[0].d[3] = (ks[0].k[6] & 0x0F) << 4;

	i = 1;
	while (i < 17)
	{
		j = 0;
		while (j < 4)
		{
			ks[i].c[j] = ks[i - 1].c[j];
			ks[i].d[j] = ks[i - 1].d[j];
		}

		shift_size = ks_shift[i];
		shift_byte = (shift_size == 1) ? 0x80 : 0xC0;
	}
}
