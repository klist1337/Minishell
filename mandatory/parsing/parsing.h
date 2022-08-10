/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 20:31:40 by achedmi           #+#    #+#             */
/*   Updated: 2022/07/31 18:50:32 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../minishell.h"

/*-------------------------------------------------------------------------*/
/*								parsing file                               */
/*-------------------------------------------------------------------------*/
typedef struct s_var
{
	char	*s;
	int		n;
	int		var;
	int		flag;
	int		flg;
	int		flg2;
	char	*lim;
	t_args	*args;
	t_file	*f;
	int		x;
}			t_var;

typedef struct s_tkn_var
{
	t_tkn	*i;
	t_tkn	*j;
	t_tkn	*n;
}	t_tkn_var;

int		check_pipe(char *line);
int		check_pipe2(t_tkn *token);
int		check_redirect(char *line);
int		check_redirect2(t_tkn *token);
void	check_input_redirection(t_file **file, t_cmd *cmd, char *line);
int		*get_size(t_lextok lex_tok, char *line, int nb);
t_tkn	*get_index_end(t_tkn *i);
t_tkn	*get_index(t_tkn *j, char *s);
t_tkn	*check_next_pipe(t_tkn *token);
t_tkn	*main_parser(t_lextok *lex_tok, char *line, t_cmd **cmd,
			t_settings *settings);
int		get_reverse_index(char **args, int i, char *s);
int		get_redirect_index(char *args);
int		get_redirect_index2(t_tkn *token);
int		check_next_red(char **args, int i);
int		get_nb_token(t_lextok lex_tok, char *line);
void	fill_next_cmd_red(t_cmd **cmd, t_tkn *token, int flag);
void	fill_cmd_files(t_tkn *token, t_cmd **cmd);
void	fill_next_cmd(t_tkn *token, t_cmd **cmd);
void	fill_next_cmd2(char **args, t_cmd **cmd, char *s);
void	parser(t_file *file, t_cmd *cmd, char *line);
char	**allocate_memory(t_lextok lex_tok, char *line);
void	init_var(t_var *var);
int		parsing_simple_cmd(t_tkn *token, t_cmd **cmd);
int		ft_syntax_error(t_tkn *token);
void	parse_cmd_pipe(t_tkn *token, t_cmd **cmd);
int		ft_error(t_cmd **cmd, t_tkn *token, t_var *variable);
int		ft_error2(t_tkn *i);
void	ft_join_arg2(t_tkn *j, t_var *variable, t_tkn *n);
void	join_args5(char **args, t_var *variable, int i);
void	ft_print_files(t_file **file);
void	ft_print_cmd(t_cmd **cmd);
int		main_parser2(t_cmd **cmd, t_tkn *token);
void	fill_next_cmd_red_part1(t_var *variable, t_tkn *n);
void	init_flag2(t_tkn *token, t_var *variable);
void	fill_cmd_files_init(t_var *variable, t_tkn *token);
void	fill_cmd_files_part1(t_tkn *token, t_var *variable);
void	fill_next_cmd_part1(t_cmd **cmd, t_tkn *i);
void	fill_next_cmd_part2(t_cmd **cmd, t_tkn *i);
void	fill_next_cmd_part3(t_cmd **cmd, t_tkn *i);
void	init_first_cmd_null(t_cmd **cmd);
void	ft_print_arg(t_args **args);
int		is_pipe(t_tkn *token);
void	print_error(char *s);
int		check_is_a_pipe_next_red(t_tkn *token);
int		is_pipe_next_is_red(t_tkn *token, t_tkn *next);
void	main_parser_p1(t_cmd **cmd, t_var *variable, t_tkn *token);
void	main_parser_p2(t_cmd **cmd, t_var *variable, t_tkn *token);
int		redirection_error(t_tkn *token, t_cmd **cmd);
void	free_token_lst(t_tkn *token);
void	free_arg_lst(t_args *args);
void	free_files_lst(t_file *file);
void	free_cmd_lst(t_cmd *cmd);
t_tkn	*fill_args_files_cmd(t_cmd **cmd, t_var *variable, t_tkn *token,
			t_tkn *comd);
t_tkn	*after_pipe(t_cmd **cmd, t_var *variable, t_tkn *token);
void	no_cmd_after_but_red_part1(t_tkn *tmp, t_var *variable);
void	no_cmd_after_but_red_part2(t_cmd **cmd, t_tkn *tmp, t_var *variable);
void	no_cmd_after_but_redirection(t_cmd **cmd, t_tkn *tmp, t_var *variable);
void	cmd_and_redsymbol_2(t_tkn *n, t_var *variable);
void	cmd_and_redsymbol(t_cmd **cmd, t_tkn *tmp,
			t_tkn *head, t_var *variable);
void	fill_cmd_files_pt1(t_tkn *tmp, t_cmd **cmd, t_var *variable);
void	fill_cmd_files_part2_2(t_tkn *n, t_var *variable);
void	fill_cmd_files_pt2(t_cmd **cmd, t_tkn *tmp, t_var *variable);
int		main_parser1(t_cmd **cmd, t_tkn *token);
int		main_parsing(t_cmd **cmd, t_tkn *tkn, t_var variable);
int		check_redirection_error(t_tkn *token);
void	fill_lst_token(char *line, t_lextok *lex_tok,
			t_tkn **tkn, t_settings *settings);
void	heredoc_flw_by_red(t_cmd **cmd, t_var *variable, t_tkn *tmp);
void	heredoc_flw_by_cmd(t_cmd **cmd, t_var *variable, t_tkn *token);
void	after_pipe_2(t_tkn **token, t_var *variable);
void	no_cmd_after_but_red_part2_2(t_cmd **cmd, t_tkn *tmp, t_var *variable);
int		check_another_red(t_tkn *token);
void	pipe_next_red(t_cmd **cmd, t_var *variable, t_tkn *tmp);
void	init_cmd(t_cmd **cmd, t_tkn *head, t_var *variable);
t_tkn	*after_pipe_red_next(t_cmd **cmd, t_tkn *current, t_var *variable);
void	init_cmd_after_pipe_red(t_cmd **cmd, t_tkn **token, t_var *variable);
void	init_pipe_cmd_after_pipe_red(t_cmd **cmd, t_tkn **token,
			t_var *variable);
void	after_pipe_red1(t_cmd **cmd, t_tkn **current, t_var *variable);
void	after_pipe_red2(t_cmd **cmd, t_tkn **current, t_var *variable);
void	after_red_pipe_with_pipe_after(t_cmd **cmd, t_tkn **token,
			t_var *variable);
void	collect_args_file(t_tkn **token, t_var *variable);
void	aft_pipred_with_cmd_after2(t_cmd **cmd, t_tkn **token, t_var *variable);
void	collect_args_file(t_tkn **token, t_var *variable);
void	init_cmd_pipe2(t_tkn **token, t_var *variable);
void	set_null(t_var *variable);
void	collect_files(t_tkn **token, t_var *variable);
void	init_command(t_cmd **cmd, t_tkn **token, t_var *variable);
void	init_cmd_pipe2(t_tkn **token, t_var *variable);
void	init_pipe_cmd(t_cmd **cmd, t_tkn **token, t_var *variable);
void	checker(t_cmd **cmd, t_tkn **current, t_tkn *tmp, t_var *variable);
void	checker1(t_cmd **cmd, t_tkn *n, t_tkn *tmp, t_var *variable);
void	checker2(t_cmd **cmd, t_tkn *n, t_tkn *tmp, t_var *variable);
void	heredoc_with_cmd_after(t_cmd **cmd, t_tkn **token, t_var *variable);
void	heredoc_with_no_cmd_after2(t_cmd **cmd, t_tkn **token, t_var *variable);
void	heredoc_with_no_cmd_after(t_cmd **cmd, t_tkn **n, t_var *variable);
void	heredoc_with_pipe_after(t_cmd **cmd, t_tkn **token, t_var *variable);
void	heredoc_with_cmd_after2(t_cmd **cmd, t_tkn **token, t_var *variable);
void	collect_args_file(t_tkn **token, t_var *variable);
void	pipe_next_red_case2(t_cmd **cmd, t_var *variable, t_tkn *tmp);
void	freeing(char **repl, char **value, t_settings *settings);
void	no_cmd_after_part2_2_1(t_cmd **cmd, t_tkn **tmp, t_var *variable);
void	iterator(t_tkn **tmp, t_var *variable);
/*-------------------------------------------------------------------------*/
/*								lexer file                                 */
/*-------------------------------------------------------------------------*/

t_lexer	*init_lexer(char *contents);
void	lexer_advance(t_lexer *lexer);
void	lexer_skip_whitespace(t_lexer *lexer);
t_token	*lexer_parse_cmd(t_lexer *lexer, t_settings *settings);
t_token	*lexer_get_heredoc(t_lexer *lexer);
t_token	*lexer_get_g_great(t_lexer *lexer);
t_token	*lexer_collect_string(t_lexer *lexer, t_settings *settings);
t_token	*lexer_get_next_token(t_lexer *lexer, t_settings *settings);
t_token	*lexer_get_next_token2(t_lexer *lexer, char next, t_settings *settings);
t_token	*lexer_get_is_printable(t_lexer *lexer);
t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token);
t_token	*lexer_collect_dollars2(t_lexer *lexer, t_settings *settings);
t_token	*token_dollars(t_lexer *lexer, char **value);
void	export_token(t_lexer *lexer, char **value);
void	lexer_parse_cmd_f2(t_lexer *lexer, char **value, t_settings *settings);
void	lexer_parse_cmd_f3(t_lexer *lexer, char **value);
void	collect_dollars_f21(t_lexer *lexer, char **value, t_settings *settings);
void	collect_string_f2(t_lexer *lexer, char next, char **value,
			t_settings *settings);
char	*collect_string(t_lexer *lexer, char *s);
char	*collect_string2(t_lexer *lexer, char *s);
t_token	*lexer_collect_string3(t_lexer *lexer);
void	collect_string_f3(t_lexer *lexer, char **value);
void	collect_string_f4(char **value);
char	*replace_val(char *str, t_settings *settings);
char	*lexer_get_current_char_as_string(t_lexer *lexer);
int		iskeychar(char c);

/*-------------------------------------------------------------------------*/
/*								lexelst_funct_cmdr file                    */
/*-------------------------------------------------------------------------*/

t_cmd	*lst_new(char *commande, t_args *args);
t_cmd	*lst_new_cmd(char *commande, t_args *args, t_file *files);
t_cmd	*last_lst(t_cmd *cmd);
void	lst_addback(t_cmd **cmd, t_cmd *new);

/*-------------------------------------------------------------------------*/
/*								lexelst_funct_files file			       */
/*-------------------------------------------------------------------------*/

t_file	*lst_new_f(char *name, int type, char *lim);
t_file	*last_lst_f(t_file *file);
void	lst_addback_f(t_file **file, t_file *new);

/*-------------------------------------------------------------------------*/
/*								token file							       */
/*-------------------------------------------------------------------------*/

t_token	*init_token(char *value, int type);

/*-------------------------------------------------------------------------*/
/*						lst_function_arg		       					   */
/*-------------------------------------------------------------------------*/
t_args	*lst_new_args(char *content);
t_args	*last_lst_args(t_args *args);
void	lst_addback_args(t_args **args, t_args *new);

/*-------------------------------------------------------------------------*/
/*						lst_function_tkn		       					   */
/*-------------------------------------------------------------------------*/
t_tkn	*lst_new_tkn(char *content, int value);
t_tkn	*last_lst_tkn(t_tkn *tkn);
void	lst_addback_tkn(t_tkn **tkn, t_tkn *new);
#endif
