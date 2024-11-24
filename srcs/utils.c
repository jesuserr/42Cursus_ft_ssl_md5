/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 22:21:30 by jesuserr          #+#    #+#             */
/*   Updated: 2024/11/24 19:43:07 by jesuserr         ###   ########.fr       */
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
