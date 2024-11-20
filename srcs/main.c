/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:12:21 by jesuserr          #+#    #+#             */
/*   Updated: 2024/11/19 17:18:19 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	print_error_and_exit(char *str)
{
	printf("ft_ssl: usage error: %s\n", str);
	printf("Try 'ft_ssl -h' or 'ft_ssl -?' for more ");
	printf("information.\n");
	exit (EXIT_FAILURE);
}

// Prints system error message, closes the socket (if ping_data has been passed
// containing an open socket) and then exits with EXIT_FAILURE status.
void	print_strerror_and_exit(char *msg, t_ping_data *ping_data)
{
	printf("%s: %s\n", msg, strerror(errno));
	if (ping_data && ping_data->sockfd > 0)
		close(ping_data->sockfd);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_ping_data	ping_data;

	if (argc < 2)
		print_error_and_exit("Destination address required");
	ft_bzero(&ping_data, sizeof(t_ping_data));
	parse_arguments(argc, argv, &ping_data.args);
	return (EXIT_SUCCESS);
}
