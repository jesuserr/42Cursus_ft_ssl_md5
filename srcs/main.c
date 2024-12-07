/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:12:21 by jesuserr          #+#    #+#             */
/*   Updated: 2024/12/07 22:39:41 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/ft_ssl.h"

// Uses an array of function pointers to call the hashing function selected by
// the user. Performs three calls to the hashing function, one for each possible
// input source: pipe, string or file.
static void	calls_to_hashing_function(t_arguments *args)
{
	void		(*hash_functions[])(t_arguments *) = \
				{md5_sum, sha224_sum, sha256_sum, sha384_sum, sha512_sum};

	if (args->input_pipe)
	{
		args->msg_origin = IS_PIPE;
		args->message = args->input_pipe;
		hash_functions[args->hash_function](args);
		free(args->input_pipe);
	}
	if (args->input_str)
	{
		args->msg_origin = IS_STRING;
		args->message = args->input_str;
		hash_functions[args->hash_function](args);
	}
	if (args->input_file)
	{
		args->msg_origin = IS_FILE;
		args->message = args->input_file;
		hash_functions[args->hash_function](args);
		if (munmap(args->input_file, args->file_size) < 0)
			print_strerror_and_exit("munmap", args);
	}
}

int	main(int argc, char **argv)
{
	t_arguments	args;

	if (argc < 2)
		print_error_and_exit("Hash function required");
	ft_bzero(&args, sizeof(t_arguments));
	parse_arguments(argc, argv, &args);
	calls_to_hashing_function(&args);
	return (EXIT_SUCCESS);
}
