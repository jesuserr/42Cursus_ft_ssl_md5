/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 22:21:30 by jesuserr          #+#    #+#             */
/*   Updated: 2024/12/05 13:25:11 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/ft_ssl.h"

// Prints given byte in hexadecimal format
// 48 is ASCII code for '0', 87 is ASCII code for 'a'
void	print_hex_byte(unsigned char byte)
{
	if ((byte >> 4) < 10)
		ft_printf("%c", (byte >> 4) + 48);
	else
		ft_printf("%c", (byte >> 4) + 87);
	if ((byte & 0x0F) < 10)
		ft_printf("%c", (byte & 0x0F) + 48);
	else
		ft_printf("%c", (byte & 0x0F) + 87);
}

// Prints system error message, closes open sockets and releases allocated
// memory. Then exits with EXIT_FAILURE status.
void	print_strerror_and_exit(char *msg, t_arguments *args)
{
	ft_printf("%s: %s\n", msg, strerror(errno));
	if (args->fd > 0)
		close(args->fd);
	if (args->input_pipe)
		free(args->input_pipe);
	exit(EXIT_FAILURE);
}

void	print_error_and_exit(char *str)
{
	ft_printf("ft_ssl: usage error: %s\n", str);
	ft_printf("Try 'ft_ssl -h' for more information.\n");
	exit (EXIT_FAILURE);
}
