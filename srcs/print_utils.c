/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 22:21:30 by jesuserr          #+#    #+#             */
/*   Updated: 2024/12/03 10:41:43 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

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

// Prints system error message, closes the socket (if it exists) and then exits
// with EXIT_FAILURE status.
void	print_strerror_and_exit(char *msg, int fd)
{
	ft_printf("%s: %s\n", msg, strerror(errno));
	if (fd > 0)
		close(fd);
	exit(EXIT_FAILURE);
}
