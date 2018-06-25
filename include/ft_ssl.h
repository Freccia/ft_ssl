/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 18:45:40 by lfabbro           #+#    #+#             */
/*   Updated: 2018/06/25 16:31:08 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft.h"
# include "getopt.h"
# include <stdint.h>

# define N_CYPHERS		1

typedef struct			s_ssl_cypher
{
	char				name[32];
	int					(*ft_cypher)(int, char **);
}						t_ssl_cypher;

typedef struct			s_ssl_ctx
{
	int64_t				opt;
	t_ssl_cypher		cypher[N_CYPHERS];
}						t_ssl_ctx;

/*
** FT_SSL TOOL FUNCTIONS
*/
char					*ft_ssl_readline(int fd);
uint64_t				ft_ssl_strlen(char *msg);

/*
** FT_SSL CYPHERS FUNCTIONS
*/
int						ft_ssl_md5(int ac, char **av);
int						ft_ssl_md5_getopt(int ac, char **av, int64_t *opt);

#endif
