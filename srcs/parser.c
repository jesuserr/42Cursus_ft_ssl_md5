/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:12:02 by jesuserr          #+#    #+#             */
/*   Updated: 2024/12/05 09:24:29 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/ft_ssl.h"

static void	print_usage(void)
{
	ft_printf("Usage\n"
		"  ./ft_ssl command [flags] <file/string>\n\n"
		"Options:\n"
		"  command     md5, sha224, sha256, sha384 or sha512\n"
		"  -h          print help and exit\n"
		"  -p          echo STDIN to STDOUT and append the checksum to STDOUT\n"
		"  -q          quiet mode\n"
		"  -r          reverse the format of the output\n"
		"  -s          print the sum of the given string\n");
	exit(EXIT_SUCCESS);
}

void	print_error_and_exit(char *str)
{
	ft_printf("ft_ssl: usage error: %s\n", str);
	ft_printf("Try 'ft_ssl -h' for more information.\n");
	exit (EXIT_FAILURE);
}

static void	parse_options(int opt, t_arguments *args)
{
	if (opt == 'h')
		print_usage();
	else if (opt == 'p')
		args->echo_stdin = true;
	else if (opt == 'q')
		args->quiet_mode = true;
	else if (opt == 'r')
		args->reverse_output = true;
	else if (opt == 's' && args->print_sum == false)
	{
		args->print_sum = true;
		args->input_str = optarg;
	}
}

void	parse_hash_function(t_arguments *args, char *hash)
{
	if (!ft_strncmp(hash, "md5", 3) && ft_strlen(hash) == 3)
		args->hash_function = 0;
	else if (!ft_strncmp(hash, "sha224", 6) && ft_strlen(hash) == 6)
		args->hash_function = 1;
	else if (!ft_strncmp(hash, "sha256", 6) && ft_strlen(hash) == 6)
		args->hash_function = 2;
	else if (!ft_strncmp(hash, "sha384", 6) && ft_strlen(hash) == 6)
		args->hash_function = 3;
	else if (!ft_strncmp(hash, "sha512", 6) && ft_strlen(hash) == 6)
		args->hash_function = 4;
	else
		print_error_and_exit("Incorrect hash function");
}

// Not final version, needs more testing
void	parse_arguments(int argc, char **argv, t_arguments *args)
{
	int		opt;

	opt = getopt(argc, argv, "hpqrs:");
	while (opt != -1)
	{
		parse_options(opt, args);
		opt = getopt(argc, argv, "hpqrs:");
	}
	if (optind >= argc)
		print_error_and_exit("Hash function required");
	parse_hash_function(args, argv[optind]);
}
