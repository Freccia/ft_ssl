/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <lfabbro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 20:14:53 by lfabbro           #+#    #+#             */
/*   Updated: 2018/12/13 20:22:26 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64.h"
#include <sys/types.h>

void	b64_encode(const uint8_t *data, uint32_t len, uint8_t **encoded)
{
	int			i;
	int			j;
	uint8_t		blk[3] = {0};

	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < 3)
		{
			blk[j] = data[i + j];
			if (data[i+ j])
			{
				++j;
				++i;
			}
		}
		b64_encode_block(blk);
	}
}
