/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 19:09:05 by achedmi           #+#    #+#             */
/*   Updated: 2022/07/29 13:51:15 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT && g_global.is_main == 1)
	{	
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_global.exit_value = 1;
	}
	else if (sig == SIGINT && g_global.is_main == 0)
		g_global.status = 130;
	else if (sig == SIGQUIT && g_global.is_main == 1)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT && g_global.is_main == 0)
	{
		write(1, "Quit: 3\n", 8);
		g_global.status = 131;
	}
}

void	here_doc_sig_handler(int sig)
{
	if (sig == SIGINT)
		exit(1);
}

void	set_vquit(int v_quit)
{
	g_global.termios.c_cc[VQUIT] = v_quit;
	tcsetattr(STDIN_FILENO, TCSANOW, &g_global.termios);
}

void	init_signal(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}
