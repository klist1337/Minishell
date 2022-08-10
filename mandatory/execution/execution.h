/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 20:31:40 by achedmi           #+#    #+#             */
/*   Updated: 2022/07/29 12:46:07 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "../minishell.h"

void	free_matrice(char **matrice);
int		arg_len(t_args *args);
char	**add_cmd_to_args(t_cmd *cmd);
char	**args_to_matrice(struct s_args *args);
int		matrice_len(char **matrice);

char	*get_value(char **matrice, char *key);
int		is_valid_key(char **matrice, char *key);
void	remove_value_of_key(char **matrice, char *key);
void	change_value_of_key(char **matrice, char *key, char *value);
int		has_pipe(t_cmd *cmd);

int		is_builtins(t_cmd *cmd);
void	exe_builtins(t_cmd *cmd, t_settings *settings, int builtin_nubmer);
void	is_built_in_with_pipe(t_cmd *cmd, t_settings *settings,
			int builtin_nubmer, int pipe);
int		check_built_ins(int is_built_in, t_cmd *tmp_cmd,
			t_settings *settings, int pipe);
void	change_directory2(char *new_path, t_settings *settings);
void	change_directory(t_settings *settings, t_cmd *cmd);
void	echo2(t_cmd *commande, char **arguments, int has_next_line, int i);
void	echo(t_cmd *cmd);

char	**just_env(t_settings *settings);
int		search_env(t_settings *settings, char *line);
char	**add_env(t_settings *settings, char *str);
void	replace_env(t_settings *settings, char *str, int index);
void	print_envp_item_with_val(char *str, t_cmd *cmd);

void	env_cmd(char **matrice, t_cmd *commande);
char	**remove_env(t_settings *settings, char *var);
int		get_index_of_envp(char **matrice, char *key);

void	waiting(t_cmd *cmds);
void	executing(t_cmd *cmds, t_settings *settings);
void	forking(t_cmd *cmd, t_settings *settings);
void	start_execution(t_cmd *cmds, t_settings *settings);

int		costum_exit(t_cmd *cmd);

void	empty_export(char **matrice, t_cmd *commande);
void	export(t_settings *settings, char **vars);
int		str_validation(char *str, char *type);
void	unset(t_settings *settings, char **vars);
char	*plus_case(char *str);

char	*check_acess2(char *long_path, char *cmd);
char	*check_acces(char **envp, char *cmd);

void	free_l_lextok(t_lextok *lex_tok);
void	free_args(t_args *args);
void	free_files(t_file *files);
void	free_cmd(t_cmd *cmd);

void	here_doc2(t_file *file, int fd);
void	here_doc(t_cmd *commande, t_file *file);

void	init(t_settings **settings, char **envp);

void	current_dir(t_settings *settings, t_cmd *cmd);

void	close_fd(int fd);
int		re_in(t_cmd *commande, t_file *file);
int		open_files(t_cmd *cmd);
void	piping(t_cmd *prev, t_cmd *next);

void	sig_handler(int sig);
void	set_vquit(int v_quit);
void	here_doc_sig_handler(int sig);

void	sig_handler(int sig);
void	here_doc_sig_handler(int sig);
void	set_vquit(int v_quit);
void	init_signal(void);
#endif
