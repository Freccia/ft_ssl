/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_base64.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 15:42:31 by lfabbro           #+#    #+#             */
/*   Updated: 2018/12/15 13:07:28 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64.h"
#include "error.h"
#include "ft_ssl.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static const char	*g_base64_longerr =
{
	"base64: Error: message too long.\n"\
	"	Limit fixed to 34,35 GB (34359738360 bytes)\n"
};

void	base64_data(const uint8_t *data, uint32_t len, uint8_t **enc, int opt)
{
	uint64_t	b64len;

	//b64len = ((len * 8) / 6) + ((len * 8) % 6) + 1;
	b64len = (len * 3) + 1;
	if ((*enc = (uint8_t*)malloc(b64len)) == NULL)
		ft_exit(EXIT_FAILURE, FAIL_MALLOC);
	bzero(*enc, b64len);
	if (opt & SSL_OPT_ENC)
		b64_encode(data, len, *enc);
	else if (opt & SSL_OPT_DEC)
		b64_decode(data, len, *enc);
}

/*
** (void)quiet for compatibility with hashes
*/
void	base64_filter(int opt)
{
	int64_t		len;
	int64_t		tmplen;
	uint8_t		*encoded;
	uint8_t		*msg;
	uint8_t		*tmp;
	uint8_t		buffer[BASE64_BUFSIZE];

	len = 0;
	msg = NULL;
	encoded = NULL;
	while ((tmplen = read(STDIN_FILENO, buffer, sizeof(BASE64_BUFSIZE))))
	{
		buffer[tmplen] = '\0';
		tmp = (uint8_t*)ft_strjoin((char*)msg, (char*)buffer);
		free(msg);
		msg = tmp;
		len += tmplen;
	}
	base64_data(msg, len, &encoded, opt);
	//ft_printf("%s\n", encoded);
	len = ft_strlen((char*)encoded);
	// TODO: clean this hack
	for (int64_t i=0; i < len; i += 76)
	{
		tmplen = ft_strlen((char*)&encoded[i]);
		write(1, &encoded[i], (tmplen < 76) ? tmplen : 76);
		write(1, "\n", 1);
	}
	ft_memset(encoded, 0, len);
}

void	base64_string(const char *msg, int opt)
{
	int64_t		len;
	uint8_t		*encoded;

	encoded = NULL;
	if ((len = ft_ssl_strlen(msg)) > UINT32_MAX)
		ft_exit(EXIT_FAILURE, g_base64_longerr);
	base64_data((uint8_t*)msg, (uint32_t)len, &encoded, opt);
	if (opt & SSL_OPT_Q)
		ft_printf("%s\n", &encoded);
	else if (opt & SSL_OPT_R)
		ft_printf("%s \"%s\"\n", &encoded, msg);
	else
		ft_printf("base64 (\"%s\") = %s\n", msg, encoded);
	if (encoded != NULL)
	{
		ft_memset(encoded, 0, len);
		free(encoded);
	}
}

int		base64_file(const char *filename, uint8_t **encoded, int opt)
{
	int			fd;
	uint8_t		*msg;
	struct stat	stat_file;

	ft_printf("File: %s\n", filename);
	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		ft_printf("%s can't be opened\n", filename);
		return (EXIT_FAILURE);
	}
	if (fstat(fd, &stat_file) == -1)
	{
		ft_printf("Failed to stat file: %s\n", filename);
		return (EXIT_FAILURE);
	}
	if ((msg = (uint8_t*)malloc(stat_file.st_size)) == NULL)
		ft_exit(EXIT_FAILURE, FAIL_MALLOC);
	if (read(fd, (char*)msg, stat_file.st_size) == -1)
		ft_exit(EXIT_FAILURE, FAIL_READ);
	base64_data(msg, stat_file.st_size, encoded, opt);
	// memset 0?
	if (close(fd))
	{
		ft_printf("Failed to close file: %s\n", filename);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int		base64_files(int ac, char **av, int opt)
{
	int			i;
	int			fail;
	uint8_t		*encoded;

	ft_printf("Files: %d\n", ac);
	encoded = NULL;
	fail = 0;
	i = g_optind;
	while (i < ac && av[i])
	{
		fail = base64_file(av[i], &encoded, opt);
		if (!fail)
		{
			if (opt & SSL_OPT_Q)
				ft_printf("%s\n", &encoded);
			else if (opt & SSL_OPT_R)
				ft_printf("%s %s\n", &encoded, av[i]);
			else
				ft_printf("%s %s\n", av[i], &encoded);
		}
		++i;
		// should I memset encoded?
	}
	return (fail);
}
