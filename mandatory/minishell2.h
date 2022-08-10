/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 19:30:14 by achedmi           #+#    #+#             */
/*   Updated: 2022/07/30 11:16:41 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL2_H
# define MINISHELL2_H

typedef struct s_settings
{
	char		*current_dir;
	char		**envp;
	int			env_len;
}t_settings;

typedef struct s_file
{
	int				type;
	char			*name;
	char			*lim;

	struct s_file	*next;
}t_file;

typedef struct s_args
{
	char			*content;
	struct s_args	*next;
}t_args;

typedef struct s_commande
{
	char				*commande;
	t_args				*args;
	char				**m_args;
	struct s_file		*files;
	int					output;
	int					input;
	int					id;
	struct s_commande	*next;
}	t_cmd;

typedef struct s_lexer
{
	unsigned int	i;
	char			*contents;
	char			c;
}	t_lexer;	

typedef struct s_token
{
	char	*value;
	enum
	{
		TOKEN_CMD,
		TOKEN_PIPE,
		TOKEN_EQUALS,
		TOKEN_SEMI,
		TOKEN_LESS,
		TOKEN_GREAT,
		TOKEN_HEREDOC,
		TOKEN_G_GREAT,
		TOKEN_ERROR,
		TOKEN_DOLLARS,
		TOKEN_RPARENT,
		TOKEN_LPARENT,
		TOKEN_QUOTES,
		TOKEN_DOLLARINT,
		TOKEN_ISPRINTABLES,
		TOKEN_EOF,
	}	e_type;
}	t_token;

typedef struct s_tkn
{
	char			*content;
	int				type;
	struct s_tkn	*next;
}	t_tkn;

typedef struct token_lexer
{
	t_lexer	*lexer;
	t_token	*token;
}		t_lextok;

typedef struct global_vars
{
	int				is_main;
	struct termios	termios;
	int				status;
	int				sysntax_err;
	int				exit_value;
}		t_global;

t_global	g_global;

#endif