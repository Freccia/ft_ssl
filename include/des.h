/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <>                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 18:38:47 by marvin            #+#    #+#             */
/*   Updated: 2019/02/06 16:00:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DES_H
# define DES_H

# define ENCRYPTION_MODE 0
# define DECRYPTION_MODE 1

typedef struct		s_des_ctx {
	uint32_t		regs[4];
	uint8_t			buff[MD5_BUFFER_SIZE];
}					t_md5;

typedef struct		s_des_keyset {
	uint8_t			k[8];
	uint8_t			c[4];
	uint8_t			d[4];
}					t_keyset;

#endif
