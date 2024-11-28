/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:11:34 by jesuserr          #+#    #+#             */
/*   Updated: 2024/11/28 19:01:02 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                              HEADERS
*/
# include "../libft/includes/libft.h"		// libft library
# include "../libft/includes/ft_printf.h"	// for ft_printf
# include <stdint.h>						// for fixed-width integer types
# include "types.h"							// for t_arguments
# include "md5.h"							// for MD5 hash function
# include "sha256.h"						// for SHA256 hash function
# include <string.h>						// for strerror
# include <fcntl.h>							// for open
# include <errno.h>							// for errno
# include <stdio.h>							// for printf (ERASE)
# include <bits/getopt_core.h>	// Delete, just to fix intellisense vscode error

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                              DEFINES
*/

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                              STRUCTS
*/

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                        FUNCTION PROTOTYPES
*/
/********************************** parser.c **********************************/
void	print_error_and_exit(char *str);
void	parse_arguments(int argc, char **argv, t_arguments *args);

/********************************** utils.c ***********************************/
void	rotate_bits_right_32_bits(uint32_t *nbr, int8_t bits);
void	rotate_bits_left_32_bits(uint32_t *nbr, int8_t bits);
void	modify_endianness_32_bits(uint32_t *nbr);
void	print_hex_byte(uint8_t byte);

#endif
