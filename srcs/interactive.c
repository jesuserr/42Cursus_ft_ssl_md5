/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:09:10 by jesuserr          #+#    #+#             */
/*   Updated: 2024/12/16 10:22:13 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/ft_ssl.h"

// Reads from standard input and stores the string in the 'args->input_pipe'.
// Uses 'gnl_strjoin' to concatenate the input lines and using the flag 'erase'
// set to 1,  frees the previous content of the 'input_pipe' field.
void	read_interactive_mode(t_arguments *args)
{
	char	*input;

	input = get_next_line(STDIN_FILENO);
	args->input_pipe = ft_strdup("");
	while (input)
	{
		args->input_pipe = gnl_strjoin(args->input_pipe, input, 1);
		free(input);
		input = get_next_line(STDIN_FILENO);
	}
	args->pipe_size = ft_strlen(args->input_pipe);
	free(input);
}

// Since message coming from stdin can be not null-terminated, write() is used 
// instead of printf() to print the exact length of the message. Function
// removes also the newline character from the end of the message if it has been
// introduced by the 'echo' command when reading from stdin (pipe). Modified 
// only for printing purposes, for hashing purposes the message with the newline
// character is processed.
void	print_message_from_pipe(t_arguments *args)
{
	if (args->pipe_size > 0 && args->message[args->pipe_size - 1] == '\n')
		args->message[args->pipe_size - 1] = '\0';
	if (args->quiet_mode)
	{
		write (1, args->message, args->pipe_size);
		ft_printf("\n");
	}
	else
	{
		ft_printf("(\"");
		write (1, args->message, args->pipe_size);
		ft_printf("\")= ");
	}
}
