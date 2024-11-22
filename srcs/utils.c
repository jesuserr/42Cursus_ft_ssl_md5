/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 22:21:30 by jesuserr          #+#    #+#             */
/*   Updated: 2024/11/22 22:33:33 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

// Rotate 32-bit number to the right by given number of bits (circular shift)
// If 'bits' is negative or greater than 32, the function does nothing
void	rotate_bits_right(uint32_t *nbr, int8_t bits)
{
	if (bits < 0 || bits > 32)
		return ;
	*nbr = *nbr >> bits | *nbr << (32 - bits);
}

// Rotate 32-bit number to the left by given number of bits (circular shift)
// If 'bits' is negative or greater than 32, the function does nothing
void	rotate_bits_left(uint32_t *nbr, int8_t bits)
{
	if (bits < 0 || bits > 32)
		return ;
	*nbr = *nbr << bits | *nbr >> (32 - bits);
}
