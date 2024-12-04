/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:12:21 by jesuserr          #+#    #+#             */
/*   Updated: 2024/12/04 10:11:51 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/ft_ssl.h"

int	main(int argc, char **argv)
{
	t_arguments	args;

	if (argc < 2)
		print_error_and_exit("Hash function required");
	ft_bzero(&args, sizeof(t_arguments));
	parse_arguments(argc, argv, &args);
	sha512_sum(&args);
	return (EXIT_SUCCESS);
}
