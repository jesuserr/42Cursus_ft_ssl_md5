/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:12:21 by jesuserr          #+#    #+#             */
/*   Updated: 2024/11/21 19:59:30 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	print_stuff(t_ssl_data *ssl_data)
{
	printf("hash_function: %s\n", ssl_data->args.hash_function);
	printf("input_str: %s\n", ssl_data->args.input_str);
	printf("file: %s\n", ssl_data->args.input_file);
	ft_hex_dump(&ssl_data, sizeof(t_ssl_data), 16);
	printf("len: %lu, ", ft_strlen(ssl_data->args.input_str));
}

int	main(int argc, char **argv)
{
	t_ssl_data	ssl_data;

	if (argc < 2)
		print_error_and_exit("Hash function required");
	ft_bzero(&ssl_data, sizeof(t_ssl_data));
	parse_arguments(argc, argv, &ssl_data.args);
	md5_sum(&ssl_data);
	//print_stuff(&ssl_data);
	return (EXIT_SUCCESS);
}
