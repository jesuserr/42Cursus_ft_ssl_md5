/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:25:44 by jesuserr          #+#    #+#             */
/*   Updated: 2024/11/21 16:21:40 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint64_t	padding(t_ssl_data *ssl_data)
{
	uint64_t	len;

	len = ft_strlen(ssl_data->args.input_string);
	if (len % BLOCK_SIZE < BLOCK_SIZE - 8 && len % BLOCK_SIZE != 0)
		len = (len + BLOCK_SIZE - 1) & ~(BLOCK_SIZE - 1);
	else
		len = ((len + BLOCK_SIZE - 1) & ~(BLOCK_SIZE - 1)) + BLOCK_SIZE;
	return (len);
}
