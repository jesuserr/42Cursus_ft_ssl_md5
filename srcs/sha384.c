/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 08:51:27 by jesuserr          #+#    #+#             */
/*   Updated: 2024/12/16 10:21:43 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/ft_ssl.h"

// Given a certain message, it is padded to a multiple of 1024 bits and filled
// in accordance with the SHA384 algorithm. Length of the message is stored as a
// 64-bit integer in big-endian format. Initial values of the digest are set.
// Appended length of the message, in bits, is a 128-bit big-endian integer
// (not implemented, it works like SHA256, low probability of message length
// exceeding 2^64 bits).
static void	create_padded_message(t_sha384_data *ssl_data)
{
	uint64_t	len;
	uint64_t	len_bits;

	if (ssl_data->args->msg_origin == IS_FILE)
		len = ssl_data->args->file_size;
	else if (ssl_data->args->msg_origin == IS_PIPE)
		len = ssl_data->args->pipe_size;
	else
		len = ft_strlen(ssl_data->args->message);
	ssl_data->msg_len = len;
	if (len % SHA384_BLOCK < SHA384_BLOCK - 16 && len % SHA384_BLOCK != 0)
		len = (len + SHA384_BLOCK - 1) & ~(SHA384_BLOCK - 1);
	else
		len = ((len + SHA384_BLOCK - 1) & ~(SHA384_BLOCK - 1)) + SHA384_BLOCK;
	ssl_data->pad_len = len;
	ssl_data->pad_msg = ft_calloc(ssl_data->pad_len, sizeof(uint8_t));
	if (!ssl_data->pad_msg)
		print_strerror_and_exit("ft_calloc", ssl_data->args);
	ft_memcpy(ssl_data->pad_msg, ssl_data->args->message, ssl_data->msg_len);
	ssl_data->pad_msg[ssl_data->msg_len] = (int8_t)0x80;
	len_bits = ssl_data->msg_len * 8;
	modify_endianness_64_bits(&len_bits);
	ft_memcpy(ssl_data->pad_msg + ssl_data->pad_len - 8, &len_bits, 8);
	ft_memcpy(ssl_data->digest, g_sha384_inits, 64);
}

// Create message schedule for the current block of the message.
// 'w' used as a kind of alias for 'schedule' to make the code more readable.
// 'j' is the current block number.
static void	create_message_schedule(t_sha384_data *ssl_data, uint64_t j)
{
	uint8_t		i;
	uint64_t	*w;

	w = ssl_data->schedule;
	i = 0;
	while (i < 16)
	{
		w[i] = *(((uint64_t *)(ssl_data->pad_msg) + i + (j * 16)));
		modify_endianness_64_bits(&w[i]);
		i++;
	}
	while (i < SHA384_ROUNDS)
	{
		ssl_data->s0 = right_rotation_64(w[i - 15], 1) ^ \
		right_rotation_64(w[i - 15], 8) ^ (w[i - 15] >> 7);
		ssl_data->s1 = right_rotation_64(w[i - 2], 19) ^ \
		right_rotation_64(w[i - 2], 61) ^ (w[i - 2] >> 6);
		w[i] = w[i - 16] + ssl_data->s0 + w[i - 7] + ssl_data->s1;
		i++;
	}
	ft_memcpy(ssl_data->state, ssl_data->digest, 64);
}

// Compression function for the current block of the message.
// 'state' used as a kind of alias for 'ssl_data->state' to make the code more
// readable. 'i' is the current round number (0-63).
static void	compression_function(t_sha384_data *ssl_data, uint8_t i)
{
	uint64_t	tmp1;
	uint64_t	tmp2;
	uint64_t	*state;

	state = ssl_data->state;
	ssl_data->s1 = right_rotation_64(state[E], 14) ^ \
	right_rotation_64(state[E], 18) ^ right_rotation_64(state[E], 41);
	ssl_data->ch = (state[E] & state[F]) ^ ((~state[E]) & state[G]);
	tmp1 = state[H] + ssl_data->s1 + ssl_data->ch + g_sha384_roots_add[i] + \
	ssl_data->schedule[i];
	ssl_data->s0 = right_rotation_64(state[A], 28) ^ \
	right_rotation_64(state[A], 34) ^ right_rotation_64(state[A], 39);
	ssl_data->maj = (state[A] & state[B]) ^ (state[A] & state[C]) ^ \
	(state[B] & state[C]);
	tmp2 = ssl_data->s0 + ssl_data->maj;
	state[H] = state[G];
	state[G] = state[F];
	state[F] = state[E];
	state[E] = state[D] + tmp1;
	state[D] = state[C];
	state[C] = state[B];
	state[B] = state[A];
	state[A] = tmp1 + tmp2;
}

// Print the digest in hexadecimal format in accordance with the combination of
// flags provided in the arguments. Although arguments are already inside 
// ssl_data, they are passed as a parameter to make the function more readable.
// 'ssl_data.digest[G]' and 'ssl_data.digest[H]' are omitted because are not 
// part of the SHA384 digest.
static void	print_sha384_digest(t_sha384_data *ssl_data, t_arguments *args)
{
	uint8_t	i;

	i = 0;
	if (args->msg_origin == IS_PIPE && !args->echo_stdin && args->input_file)
		return ;
	if (args->quiet_mode)
	{
		if (args->echo_stdin && args->msg_origin == IS_PIPE)
			print_message_from_pipe(args);
		while (i < SHA384_OUTPUT_SIZE / SHA384_WORD_SIZE)
			print_hex_bytes((uint8_t *)&(ssl_data->digest[i++]), 7, 0);
		ft_printf("\n");
		return ;
	}
	print_prehash_output("SHA384", args);
	while (i < SHA384_OUTPUT_SIZE / SHA384_WORD_SIZE)
		print_hex_bytes((uint8_t *)&(ssl_data->digest[i++]), 7, 0);
	if (args->reverse_output && args->msg_origin == IS_STRING)
		ft_printf(" \"%s\"", args->message);
	else if (args->reverse_output && args->msg_origin == IS_FILE)
		ft_printf(" %s", args->file_name);
	ft_printf("\n");
}

// Main function to calculate the SHA384 digest.
void	sha384_sum(t_arguments *args)
{
	t_sha384_data	ssl_data;
	uint8_t			i;
	uint64_t		j;

	ft_bzero(&ssl_data, sizeof(t_sha384_data));
	ssl_data.args = args;
	create_padded_message(&ssl_data);
	j = 0;
	while (j < ssl_data.pad_len / SHA384_BLOCK)
	{
		create_message_schedule(&ssl_data, j++);
		i = 0;
		while (i < SHA384_ROUNDS)
			compression_function(&ssl_data, i++);
		ssl_data.digest[A] += ssl_data.state[A];
		ssl_data.digest[B] += ssl_data.state[B];
		ssl_data.digest[C] += ssl_data.state[C];
		ssl_data.digest[D] += ssl_data.state[D];
		ssl_data.digest[E] += ssl_data.state[E];
		ssl_data.digest[F] += ssl_data.state[F];
		ssl_data.digest[G] += ssl_data.state[G];
		ssl_data.digest[H] += ssl_data.state[H];
	}
	print_sha384_digest(&ssl_data, args);
	free(ssl_data.pad_msg);
}
