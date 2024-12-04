/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:11:34 by jesuserr          #+#    #+#             */
/*   Updated: 2024/12/04 12:25:42 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                              HEADERS
*/
# include "../../libft/includes/libft.h"		// libft library
# include "../../libft/includes/ft_printf.h"	// for ft_printf
# include <stdint.h>						    // for fixed-width integer types
# include "types.h"							    // for t_arguments
# include "md5.h"							    // for MD5 hash function
# include "sha256.h"						    // for SHA256 hash function
# include "sha224.h"						    // for SHA224 hash function
# include "sha512.h"						    // for SHA512 hash function
# include <string.h>						    // for strerror
# include <fcntl.h>							    // for open
# include <errno.h>							    // for errno
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
void		print_error_and_exit(char *str);
void		parse_arguments(int argc, char **argv, t_arguments *args);

/********************************** bitwise_utils.c ***************************/
uint32_t	right_rotation(uint32_t nbr, int8_t bits);
uint32_t	left_rotation(uint32_t nbr, int8_t bits);
void		modify_endianness_32_bits(uint32_t *nbr);
void		modify_endianness_64_bits(uint64_t *nbr);
uint64_t	right_rotation_64(uint64_t nbr, int8_t bits);

/********************************** print_utils.c *****************************/
void		print_hex_byte(uint8_t byte);
void		print_strerror_and_exit(char *msg, int fd);

#endif
