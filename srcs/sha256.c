/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:00:42 by jesuserr          #+#    #+#             */
/*   Updated: 2024/11/28 22:17:16 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

// Prints system error message, closes the socket (if ssl_data has been passed
// containing an open socket) and then exits with EXIT_FAILURE status.
static void	print_strerror_and_exit(char *msg, t_sha256_data *ssl_data)
{
	ft_printf("%s: %s\n", msg, strerror(errno));
	if (ssl_data && ssl_data->args->fd > 0)
		close(ssl_data->args->fd);
	exit(EXIT_FAILURE);
}

// Given a certain message, it is padded to a multiple of 512 bits and filled in
// accordance with the SHA256 algorithm. Length of the message is stored as a 
// 64-bit integer in big-endian format. Initial values of the digest are set.
static void	create_padded_message(t_sha256_data *ssl_data)
{
	uint64_t	len;
	uint64_t	len_bits;

	len = ft_strlen(ssl_data->args->input_str);
	ssl_data->msg_len = len;
	if (len % SHA256_BLOCK < SHA256_BLOCK - 8 && len % SHA256_BLOCK != 0)
		len = (len + SHA256_BLOCK - 1) & ~(SHA256_BLOCK - 1);
	else
		len = ((len + SHA256_BLOCK - 1) & ~(SHA256_BLOCK - 1)) + SHA256_BLOCK;
	ssl_data->pad_len = len;
	ssl_data->pad_msg = ft_calloc(ssl_data->pad_len, sizeof(uint8_t));
	if (!ssl_data->pad_msg)
		print_strerror_and_exit("ft_calloc", ssl_data);
	ft_memcpy(ssl_data->pad_msg, ssl_data->args->input_str, ssl_data->msg_len);
	ssl_data->pad_msg[ssl_data->msg_len] = (uint8_t)0x80;
	len_bits = ssl_data->msg_len * 8;
	modify_endianness_64_bits(&len_bits);
	ft_memcpy(ssl_data->pad_msg + ssl_data->pad_len - 8, &len_bits, 8);
	ssl_data->digest[A] = SHA256_INIT_A;
	ssl_data->digest[B] = SHA256_INIT_B;
	ssl_data->digest[C] = SHA256_INIT_C;
	ssl_data->digest[D] = SHA256_INIT_D;
	ssl_data->digest[E] = SHA256_INIT_E;
	ssl_data->digest[F] = SHA256_INIT_F;
	ssl_data->digest[G] = SHA256_INIT_G;
	ssl_data->digest[H] = SHA256_INIT_H;
}

// SHA256 algorithm core function.
static void	block_calculations(t_sha256_data *ssl_data, uint8_t i, uint64_t j)
{
	uint32_t	tmp_b;
	uint64_t	index;

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
	tmp_b = tmp_b + ssl_data->state[A] + g_sha256_roots_add[i];
	index = (j * SHA256_BLOCK) + (g_sha256_index[i] * SHA256_WORD_SIZE);
	tmp_b = tmp_b + *((uint32_t *)(ssl_data->pad_msg + index));
	rotate_bits_left_32_bits(&tmp_b, g_sha256_rotations[i]);
	tmp_b = tmp_b + ssl_data->state[B];
	ssl_data->state[A] = ssl_data->state[D];
	ssl_data->state[D] = ssl_data->state[C];
	ssl_data->state[C] = ssl_data->state[B];
	ssl_data->state[B] = tmp_b;
}

// Print the digest in hexadecimal format.
static void	print_sha256_digest(t_sha256_data *ssl_data)
{
	uint8_t	i;
	uint8_t	j;
	uint8_t	*byte;

	i = 0;
	ft_printf("SHA256 (\"%s\") = ", ssl_data->args->input_str);
	while (i < 4)
	{
		byte = (uint8_t *)&(ssl_data->digest[i]);
		j = 0;
		while (j < 8)
			print_hex_byte(byte[j++]);
		i++;
	}
	ft_printf("\n");
}

// Main function to calculate the SHA256 digest.
void	sha256_sum(t_arguments *args)
{
	t_sha256_data	ssl_data;
	uint8_t			i;
	uint64_t		j;

	ft_bzero(&ssl_data, sizeof(t_sha256_data));
	ssl_data.args = args;
	create_padded_message(&ssl_data);
	printf("pad_len: %lu\n", ssl_data.pad_len);
	ft_hex_dump(ssl_data.pad_msg, ssl_data.pad_len, 16);
	//return ;
	j = 0;
	while (j < ssl_data.pad_len / SHA256_BLOCK)
	{
		ssl_data.state[A] = ssl_data.digest[A];
		ssl_data.state[B] = ssl_data.digest[B];
		ssl_data.state[C] = ssl_data.digest[C];
		ssl_data.state[D] = ssl_data.digest[D];
		i = 0;
		while (i < SHA256_BLOCK)
			block_calculations(&ssl_data, i++, j);
		ssl_data.digest[A] = ssl_data.digest[A] + ssl_data.state[A];
		ssl_data.digest[B] = ssl_data.digest[B] + ssl_data.state[B];
		ssl_data.digest[C] = ssl_data.digest[C] + ssl_data.state[C];
		ssl_data.digest[D] = ssl_data.digest[D] + ssl_data.state[D];
		j++;
	}
	print_sha256_digest(&ssl_data);
	free(ssl_data.pad_msg);
}
