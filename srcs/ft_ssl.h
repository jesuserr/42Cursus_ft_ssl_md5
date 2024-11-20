/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:11:34 by jesuserr          #+#    #+#             */
/*   Updated: 2024/11/19 17:14:37 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                              HEADERS
*/
# include "../libft/includes/libft.h"
# include <stdio.h>				// for printf
# include <stdlib.h>			// for exit
# include <unistd.h>			// for getopt
# include <stdbool.h>			// for booleans
# include <bits/getopt_core.h>	// Delete, just to fix intellisense vscode error
# include <sys/socket.h>		// for socket, sendto
# include <netinet/in.h>		// for IPPROTO_ICMP
# include <netinet/ip_icmp.h>	// for struct icmphdr
# include <netinet/ip.h>		// for struct iphdr
# include <arpa/inet.h>			// for inet_addr
# include <sys/time.h>  		// for gettimeofday
# include <sys/types.h>			// for struct addrinfo
# include <netdb.h>				// for struct addrinfo
# include <errno.h>				// for errno
# include <string.h>			// for strerror

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                              DEFINES
*/
# define SOCKET_DOMAIN		AF_INET
# define SOCKET_TYPE		SOCK_RAW
# define SOCKET_PROTOCOL	IPPROTO_ICMP
# define ICMP_PACKET_SIZE	64
# define BUFFER_LEN			1024
# define DEFAULT_FIRST_HOP	1					// first_hop
# define DEFAULT_MAX_HOPS	64					// max_hops
# define DEFAULT_PACKETS	3					// packets_per_hop
# define DEFAULT_TIMEOUT	3					// seconds
# define PAYLOAD_56_B "Written by Jesus Serrano (jesuserr) on Nov '24 for 42BCN"
/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                              STRUCTS
*/
typedef struct s_arguments
{
	char		*dest;
	bool		resolve_hostnames;
	u_int8_t	first_hop;
	u_int8_t	max_hops;
	u_int8_t	packets_per_hop;
	u_int8_t	timeout;	
}	t_arguments;

typedef struct s_icmp_packet
{
	struct icmphdr	icmp_header;
	char			payload[ICMP_PACKET_SIZE - sizeof(struct icmphdr)];
}	t_icmp_packet;

typedef struct s_ping_data
{
	t_icmp_packet		packet;
	t_arguments			args;
	struct sockaddr_in	dest_addr;
	struct addrinfo		hints;
	int					sockfd;
	char				ip_str[INET_ADDRSTRLEN];
	bool				printed_ip;
	bool				destiny_reached;
	uint64_t			seconds;
	uint64_t			microseconds;
}	t_ping_data;

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                        FUNCTION PROTOTYPES
*/
/********************************** main.c ************************************/
void		print_error_and_exit(char *str);
void		print_strerror_and_exit(char *msg, t_ping_data *ping_data);

/********************************** parser.c **********************************/
void		parse_arguments(int argc, char **argv, t_arguments *args);

#endif
