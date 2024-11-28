/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 22:21:30 by jesuserr          #+#    #+#             */
/*   Updated: 2024/11/28 21:48:55 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

// Rotate 32-bit number to the right by given number of bits (circular shift)
// If 'bits' is negative or greater than 32, the function does nothing
void	rotate_bits_right_32_bits(uint32_t *nbr, int8_t bits)
{
	if (bits < 0 || bits > 32)
		return ;
	*nbr = *nbr >> bits | *nbr << (32 - bits);
}

// Rotate 32-bit number to the left by given number of bits (circular shift)
// If 'bits' is negative or greater than 32, the function does nothing
void	rotate_bits_left_32_bits(uint32_t *nbr, int8_t bits)
{
	if (bits < 0 || bits > 32)
		return ;
	*nbr = *nbr << bits | *nbr >> (32 - bits);
}

// Modify endianness of 32-bit number
void	modify_endianness_32_bits(uint32_t *nbr)
{
	*nbr = ((*nbr >> 24) & 0x000000FF) | ((*nbr >> 8) & 0x0000FF00) | \
			((*nbr << 8) & 0x00FF0000) | ((*nbr << 24) & 0xFF000000);
}

void	modify_endianness_64_bits(uint64_t *nbr)
{
	*nbr = ((*nbr >> 56) & 0x00000000000000FF) | \
			((*nbr >> 40) & 0x000000000000FF00) | \
			((*nbr >> 24) & 0x0000000000FF0000) | \
			((*nbr >> 8) & 0x00000000FF000000) | \
			((*nbr << 8) & 0x000000FF00000000) | \
			((*nbr << 24) & 0x0000FF0000000000) | \
			((*nbr << 40) & 0x00FF000000000000) | \
			((*nbr << 56) & 0xFF00000000000000);
}

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
