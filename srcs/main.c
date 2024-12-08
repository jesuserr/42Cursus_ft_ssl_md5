/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:12:21 by jesuserr          #+#    #+#             */
/*   Updated: 2024/12/08 18:56:48 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/ft_ssl.h"

void	print_usage(void)
{
	ft_printf("Usage\n"
		"  ./ft_ssl <command> [flags] [file]\n\n"
		"Options:\n"
		"  command     md5, sha224, sha256, sha384 or sha512\n"
		"  -h          print help and exit\n"
		"  -p          echo STDIN to STDOUT and append the checksum to STDOUT\n"
		"  -q          quiet mode\n"
		"  -r          reverse the format of the output\n"
		"  -s <string> print the sum of the given string\n");
	exit(EXIT_SUCCESS);
}

// Uses an array of function pointers to call the hashing function selected by
// the user. Performs up to three calls to the hashing function, one for each
// possible input source (pipe, string or file) that has some content.
static void	calls_to_hashing_function(t_arguments *args)
{
	void		(*hash_functions[])(t_arguments *) = \
				{md5_sum, sha224_sum, sha256_sum, sha384_sum, sha512_sum};
	char		*msg[3] = {args->input_pipe, args->input_str, args->input_file};
	uint8_t		origin;

	origin = IS_PIPE;
	while (origin <= IS_FILE)
	{
		if (msg[origin])
		{
			args->msg_origin = origin;
			args->message = msg[origin];
			hash_functions[args->hash_function](args);
		}
		origin++;
	}
	if (args->input_pipe)
		free(args->input_pipe);
	if (args->input_file)
		if (munmap(args->input_file, args->file_size) < 0)
			print_strerror_and_exit("munmap", args);
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
