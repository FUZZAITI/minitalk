/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepinhei <pepinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 11:25:38 by pepinhei          #+#    #+#             */
/*   Updated: 2026/01/31 11:37:45 by pepinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

void	send_char(pid_t pid, unsigned char c);
void	send_bit(pid_t pid, int bit);
void	ack_handler(int sig);
void	handler(int sig, siginfo_t *info, void *context);

#endif
