/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 18:45:40 by lfabbro           #+#    #+#             */
/*   Updated: 2018/09/08 18:29:23 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft.h"
# include "getopt.h"
# include "error.h"
# include <stdint.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define N_CYPHERS		2

/*
** SSL Cypher Options
*/
# define SSL_OPTIONS	"hpqrs:"
# define SSL_OPT_P		1
# define SSL_OPT_Q		2
# define SSL_OPT_R		4
# define SSL_OPT_S		8
# define SSL_OPT_END	16


typedef struct			s_ssl_cypher
{
	char				name[8];
	char				cy_name[8];
	uint32_t			digest_size;
	int					(*ft_file)(const char *filename, uint32_t *dig);
	void				(*ft_data)(const uint8_t *msg, uint32_t len, uint32_t *dig);
}						t_ssl_cypher;

typedef struct			s_ssl_ctx
{
	int64_t				opt;
	t_ssl_cypher		cypher[N_CYPHERS];
}						t_ssl_ctx;

/*
** FT_SSL TOOL FUNCTIONS
*/
char					*ft_ssl_readin(int fd);
uint64_t				ft_ssl_strlen(char *msg);

/*
** FT_SSL CYPHERS FUNCTIONS
*/
int						ft_ssl(int ac, char **av, t_ssl_cypher *chyphr);

#endif
