/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:12:21 by jesuserr          #+#    #+#             */
/*   Updated: 2024/11/20 20:45:30 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	main(int argc, char **argv)
{
	t_ssl_data	ssl_data;

	if (argc < 2)
		print_error_and_exit("Hash function required");
	ft_bzero(&ssl_data, sizeof(t_ssl_data));
	parse_arguments(argc, argv, &ssl_data.args);
	printf("hash_function: %s\n", ssl_data.args.hash_function);
	ft_hex_dump(&ssl_data, sizeof(t_ssl_data), 16);
	return (EXIT_SUCCESS);
}
