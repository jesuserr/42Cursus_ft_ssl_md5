/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:12:02 by jesuserr          #+#    #+#             */
/*   Updated: 2024/12/08 21:11:08 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/ft_ssl.h"

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
	else if (opt == 's' && args->print_sum == true)
	{
		ft_printf("ft_ssl: %s: %s\n", "-s", "No such file or directory");
		ft_printf("ft_ssl: %s: %s\n", optarg, "No such file or directory");
	}
}

static void	parse_hash_function(t_arguments *args, char *hash)
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

static void	parse_pipe(t_arguments *args)
{
	char		buffer[BUFFER_SIZE];
	ssize_t		bytes_read;

	if (isatty(STDIN_FILENO) == 0)
	{
		bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
		if (bytes_read < 0 || bytes_read >= BUFFER_SIZE - 1)
			print_error_and_exit("Error reading from pipe");
		buffer[bytes_read] = '\0';
		args->input_pipe = ft_strdup(buffer);
	}
}

// Uses 'mmap' to map the entire file into memory in one shot. Way more 
// efficient than reading the file multiple times. File size is kept for the
// hash functions to know how many bytes to read (specially for binary files)
// and also for the 'munmap' function to know how many bytes to unmap when the
// program finishes.
void	parse_file_content(t_arguments *args, char *file_name)
{
	int			fd;
	struct stat	file_stat;
	void		*file_content;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		print_strerror_and_exit(file_name, args);
	if (fstat(fd, &file_stat) < 0)
		print_strerror_and_exit(file_name, args);
	file_content = mmap(NULL, file_stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (file_content == MAP_FAILED)
	{
		close(fd);
		print_strerror_and_exit("mmap", args);
	}
	close(fd);
	args->input_file = (char *)file_content;
	args->file_size = file_stat.st_size;
	args->file_name = file_name;
}

// Not final version, needs more testing
void	parse_arguments(int argc, char **argv, t_arguments *args)
{
	int		opt;

	parse_pipe(args);
	opt = getopt(argc, argv, "hpqrs:");
	while (opt != -1)
	{
		parse_options(opt, args);
		opt = getopt(argc, argv, "hpqrs:");
	}
	parse_hash_function(args, argv[optind]);
	if (!argv[optind + 1] && !args->input_str && !args->input_pipe)
		print_error_and_exit("Missing arguments");
	if (optind + 1 < argc)
		parse_file_content(args, argv[optind + 1]);
	if (optind + 2 < argc)
		print_error_and_exit("Too many arguments");
}
