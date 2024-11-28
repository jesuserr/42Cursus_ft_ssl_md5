/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:12:21 by jesuserr          #+#    #+#             */
/*   Updated: 2024/11/28 20:20:04 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	main(int argc, char **argv)
{
	t_arguments	args;

	if (argc < 2)
		print_error_and_exit("Hash function required");
	ft_bzero(&args, sizeof(t_arguments));
	parse_arguments(argc, argv, &args);
	sha256_sum(&args);
	return (EXIT_SUCCESS);
}
