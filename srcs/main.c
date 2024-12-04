/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:12:21 by jesuserr          #+#    #+#             */
/*   Updated: 2024/12/04 19:59:08 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/ft_ssl.h"

int	main(int argc, char **argv)
{
	t_arguments	args;
	void		(*hash_functions[])(t_arguments *) = \
				{md5_sum, sha224_sum, sha256_sum, sha512_sum};

	if (argc < 2)
		print_error_and_exit("Hash function required");
	ft_bzero(&args, sizeof(t_arguments));
	parse_arguments(argc, argv, &args);
	hash_functions[args.hash_function](&args);
	return (EXIT_SUCCESS);
}
