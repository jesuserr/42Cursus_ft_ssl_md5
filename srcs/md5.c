/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:25:44 by jesuserr          #+#    #+#             */
/*   Updated: 2024/11/22 22:26:38 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	create_padded_message(t_ssl_data *ssl_data)
{
	uint64_t	len;
	uint64_t	len_bits;

	len = ft_strlen(ssl_data->args.input_str);
	ssl_data->msg_len = len;
	if (len % BLOCK_SIZE < BLOCK_SIZE - 8 && len % BLOCK_SIZE != 0)
		len = (len + BLOCK_SIZE - 1) & ~(BLOCK_SIZE - 1);
	else
		len = ((len + BLOCK_SIZE - 1) & ~(BLOCK_SIZE - 1)) + BLOCK_SIZE;
	ssl_data->pad_len = len;
	ssl_data->pad_msg = ft_calloc(ssl_data->pad_len, sizeof(uint8_t));
	if (!ssl_data->pad_msg)
		print_strerror_and_exit("ft_calloc", ssl_data);
	ft_memcpy(ssl_data->pad_msg, ssl_data->args.input_str, ssl_data->msg_len);
	ssl_data->pad_msg[ssl_data->msg_len] = (uint8_t)0x80;
	len_bits = ssl_data->msg_len * 8;
	ft_memcpy(ssl_data->pad_msg + ssl_data->pad_len - 8, &len_bits, 8);
}

void	md5_sum(t_ssl_data *ssl_data)
{
	create_padded_message(ssl_data);
	printf("Orig. len: %lu (%lu)\n", ssl_data->msg_len, ssl_data->msg_len * 8);
	printf("Padded len: %lu (%lu)\n", ssl_data->pad_len, ssl_data->pad_len * 8);
	ft_hex_dump(ssl_data->pad_msg, ssl_data->pad_len, 4);
	free(ssl_data->pad_msg);
	return ;
}
