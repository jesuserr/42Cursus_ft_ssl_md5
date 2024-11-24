/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:25:44 by jesuserr          #+#    #+#             */
/*   Updated: 2024/11/24 13:36:59 by jesuserr         ###   ########.fr       */
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
	ssl_data->state[A] = INIT_A;
	ssl_data->state[B] = INIT_B;
	ssl_data->state[C] = INIT_C;
	ssl_data->state[D] = INIT_D;
}

void	block_calculations(t_ssl_data *ssl_data, uint64_t i)
{
	uint32_t		tmp_b;

	if (i < 16)
		tmp_b = (ssl_data->state[B] & ssl_data->state[C]) | \
		(~ssl_data->state[B] & ssl_data->state[D]);
	else if (i >= 16 && i < 32)
		tmp_b = (ssl_data->state[B] & ssl_data->state[D]) | \
		(ssl_data->state[C] & ~ssl_data->state[D]);
	else if (i >= 32 && i < 48)
		tmp_b = ssl_data->state[B] ^ ssl_data->state[C] ^ ssl_data->state[D];
	else if (i >= 48 && i < 64)
		tmp_b = ssl_data->state[C] ^ (ssl_data->state[B] | ~ssl_data->state[D]);
	tmp_b = tmp_b + ssl_data->state[A] + g_add[i];
	tmp_b = tmp_b + *((uint32_t *)(ssl_data->pad_msg + g_index[i] * WORD_SIZE));
	rotate_bits_left_32_bits(&tmp_b, g_shift[i]);
	tmp_b = tmp_b + ssl_data->state[B];
	ssl_data->state[A] = ssl_data->state[D];
	ssl_data->state[D] = ssl_data->state[C];
	ssl_data->state[C] = ssl_data->state[B];
	ssl_data->state[B] = tmp_b;
	return ;
}

void	md5_sum(t_ssl_data *ssl_data)
{
	uint64_t		i;
	uint64_t		j;

	create_padded_message(ssl_data);
	j = 0;
	while (j < ssl_data->pad_len / BLOCK_SIZE)
	{
		i = 0;
		while (i < BLOCK_SIZE)
			block_calculations(ssl_data, i++);
		ssl_data->state[A] = ssl_data->state[A] + INIT_A;
		ssl_data->state[B] = ssl_data->state[B] + INIT_B;
		ssl_data->state[C] = ssl_data->state[C] + INIT_C;
		ssl_data->state[D] = ssl_data->state[D] + INIT_D;
		j++;
	}
	printf("J: %lu\n", j);
	i = 0;
	while (i < 4)
	{
		modify_endianness_32_bits(&ssl_data->state[i]);
		printf("%08x", ssl_data->state[i++]);
	}
	printf("\n");
	free(ssl_data->pad_msg);
	return ;
}

/*
ft_hex_dump(ssl_data->state, 4 * WORD_SIZE, 4);
printf("\n");
ft_hex_dump(ssl_data->pad_msg, ssl_data->pad_len, 4);

printf("Word %02ld\t", i);
printf("\nOrig. len: %lu (%lu)\n", ssl_data->msg_len, ssl_data->msg_len * 8);
printf("Padded len: %lu (%lu)\n", ssl_data->pad_len, ssl_data->pad_len * 8);
printf("A: %08x\tB: %08x\t", ssl_data->state[A], ssl_data->state[B]);
printf("C: %08x\tD: %08x\t", ssl_data->state[C], ssl_data->state[D]);
msg = *((uint32_t *)(ssl_data->pad_msg + i * WORD_SIZE));
modify_endianness_32_bits(&msg);
printf("Msg: %08x\n", msg);
printf("D + msg: %08x\n", 256 + msg);
temp = ssl_data->state[A];
ssl_data->state[A] = ssl_data->state[D];
ssl_data->state[D] = ssl_data->state[C];
ssl_data->state[C] = ssl_data->state[B];
ssl_data->state[B] = temp * 2;
i++;
	}
*/
