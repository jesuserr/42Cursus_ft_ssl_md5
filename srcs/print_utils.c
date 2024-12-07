/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 22:21:30 by jesuserr          #+#    #+#             */
/*   Updated: 2024/12/05 22:03:24 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/ft_ssl.h"

// Prints given array of bytes in hexadecimal format. Depending on the 'start'
// and 'end' values, it prints the array in ascending or descending order to
// deal with different digest formats (big-endian / little-endian).
// 48 is ASCII code for '0', 87 is ASCII code for 'a'
void	print_hex_bytes(uint8_t *byte, uint8_t start, uint8_t end)
{
	bool	increase;

	increase = start < end;
	while (1)
	{
		if ((byte[start] >> 4) < 10)
			ft_printf("%c", (byte[start] >> 4) + 48);
		else
			ft_printf("%c", (byte[start] >> 4) + 87);
		if ((byte[start] & 0x0F) < 10)
			ft_printf("%c", (byte[start] & 0x0F) + 48);
		else
			ft_printf("%c", (byte[start] & 0x0F) + 87);
		if (start == end)
			break ;
		if (increase)
			start++;
		else
			start--;
	}
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

// Removes the newline character from the end of the string if it has been 
// introduced by the 'echo' command when reading from stdin (pipe).
// Modified only for printing purposes, for hashing purposes the message with
// the newline character is used.
void	remove_newline_character(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (str[len - 1] == '\n')
		str[len - 1] = '\0';
}
