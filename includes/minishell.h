/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 23:04:45 by anmarque          #+#    #+#             */
/*   Updated: 2023/02/09 20:24:11 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define EMPTY 0
# define CMD 1
# define ARG 2
# define TRUNC 3
# define APPEND 4
# define INPUT 5
# define PIPE 6
# define END 7

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define SKIP 1
# define NOSKIP 0

# define BUFF_SIZE 4096
# define EXPANSION -36
# define ERROR 1
# define SUCCESS 0
# define IS_DIRECTORY 126
# define UNKNOWN_COMMAND 127

typedef struct	s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct	s_env
{
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct	s_ms
{
	t_token			*start;
	t_env			*env;
	t_env			*secret_env;
	int				in;
	int				out;
	int				fdin;
	int				fdout;
	int				pipin;
	int				pipout;
	int				pid;
	int				charge;
	int				parent;
	int				last;
	int				ret;
	int				exit;
	int				no_exec;
}				t_ms;

typedef struct	s_sig
{
	int				sigint;
	int				sigquit;
	int				exit_status;
	pid_t			pid;
}				t_sig;

typedef struct	s_expansions
{
	char			*new_arg;
	int				i;
	int				j;
}				t_expansions;

/*
** MINISHELL
*/
void			redir(t_ms *ms, t_token *token, int type);
void			input(t_ms *ms, t_token *token);
int				mspipe(t_ms *ms);
char			*expansions(char *arg, t_env *env, int ret);

/*
** EXEC
*/
void			exec_cmd(t_ms *ms, t_token *token);
int				exec_bin(char **args, t_env *env, t_ms *ms);
int				exec_builtin(char **args, t_ms *ms);
int				is_builtin(char	*command);

/*
** BUILTINS
*/
int				ft_echo(char **args);
int				ft_cd(char **args, t_env *env);
int				ft_pwd(void);
int				ft_export(char **args, t_env *env, t_env *secret);
int				ft_env(t_env *env);
int				env_add(const char *value, t_env *env);
char			*get_env_name(char *dest, const char *src);
int				is_in_env(t_env *env, char *args);
int				ft_unset(char **args, t_ms *ms);
void			ms_exit(t_ms *ms, char **cmd);

/*
** PARSING
*/
void			parse(t_ms *ms);
t_token			*get_tokens(char *line);
void			squish_args(t_ms *ms);
int				is_last_valid_arg(t_token *token);
int				quotes(char *line, int index);
void			type_arg(t_token *token, int separator);
int				is_sep(char *line, int i);
int				ignore_sep(char *line, int i);

/*
** ENV
*/
int				check_line(t_ms *ms, t_token *token);
char			*env_to_str(t_env *lst);
int				env_init(t_ms *ms, char **env_array);
int				secret_env_init(t_ms *ms, char **env_array);
char			*get_env_value(char *arg, t_env *env);
char			*env_value(char *env);
int				env_value_len(const char *env);
int				is_env_char(int c);
int				is_valid_env(const char *env);
void			print_sorted_env(t_env *env);
void			increment_shell_level(t_env *env);
size_t			size_env(t_env *lst);

/*
** FD TOOLS
*/
void			reset_std(t_ms *ms);
void			close_fds(t_ms *ms);
void			ft_close(int fd);
void			reset_fds(t_ms *ms);

/*
** FREE TOOLS
*/
void			free_token(t_token *start);
void			free_env(t_env *env);
void			free_tab(char **tab);

/*
** TOKEN TOOLS
*/
t_token			*next_sep(t_token *token, int skip);
t_token			*prev_sep(t_token *token, int skip);
t_token			*next_run(t_token *token, int skip);
void 			print_tokens(t_token *token);

/*
** TYPE TOOLS
*/
int				is_type(t_token *token, int type);
int				is_types(t_token *token, char *types);
int				has_type(t_token *token, int type);
int				has_pipe(t_token *token);
t_token			*next_type(t_token *token, int type, int skip);

/*
** EXPANSIONS
*/
int				ret_size(int ret);
int				get_var_len(const char *arg, int pos, t_env *env, int ret);
int				arg_alloc_len(const char *arg, t_env *env, int ret);
char			*get_var_value(const char *arg, int pos, t_env *env, int ret);

/*
** SIGNAL
*/
void			sig_int(int code);
void			sig_quit(int code);
void			sig_init(void);

extern t_sig g_sig;
#endif