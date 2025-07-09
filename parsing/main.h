#ifndef MINI_H
#define MINI_H


#include <stdio.h>

#include "readline/readline.h"
#include "readline/history.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <termios.h>
#include <signal.h>
#include <fcntl.h>

// type for tokens //
typedef enum s_type
{
	PIPE,
	RED_IN,
	RED_OUT,
	HEREDOC,
	APPEND,
	WORD,
} t_type;
//------------------//

typedef enum s_red_type
{
	INPUT,
	OUTPUT,
	RED_HEREDOC,
	RED_APPEND,
} t_red_type;

typedef struct s_redirection
{
	char			*name;
	t_red_type		type;
	int				expand_variable;
	struct s_redirection	*next_red;

} t_redirection;

typedef struct s_command
{
	char					**command;
	t_redirection			*red;
	struct s_command		*next_command;
} t_command;

typedef struct s_token
{
	char			*value;
	int				has_space_after;
	t_type			type;
	int				has_quote;
	struct s_token	*next;
} t_token;

typedef struct s_env 
{
    char *key;
    char *value;
    struct s_env *next;
} t_env;

typedef struct s_data
{
	int			exit_status;
	t_command	*cmd;
	pid_t		*pids;
	int			index_cmd;
	int			prev_fd;
} t_data;

t_token *new_token(char *value, int is_space_befor);
void	append_token(t_token **head, t_token *new_node);
void	assign_token_types(t_token *tokens);

//utils:
//--------------//
int				ft_isspace(char c);
int				ft_strlen(const char *s);
char			*my_strcat(char *dest, const char *src);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*my_strcpy(char *dest, const char *src);
char			*ft_strdup(const char *s1);
int				ft_strcmp(char *s1, char *s2);
char			*ft_strchr(const char *s, int c);
char			*ft_itoa(int n);
void			*ft_realloc(void *ptr, size_t new_size);
//--------------//


//print:
//--------------//
#include <stdio.h>

void			print_tokens(t_token *tokens);
void			print_commands(t_command *cmds);
void			print_env_list(t_env *env_list);
//--------------//

int				is_single_quoted(const char *str);
int				is_quoted(const char *str);
int				is_operator(char *str);
int				ft_isspace(char c);
int				has_quote(const char *s);

char			*add_spaces_around_symbols(char *input);
int				get_token_end(char *s, int i);
int				check_syntax_errors_raw(char *input);
void			join_tokens_with_no_space(t_token **tokens);
char			*remove_quotes(const char *str);
t_command		*extract_all_commands(t_token *tokens);

t_env			*init_env(char **envp);
t_redirection	*get_redirections(t_token **tokens);

void			expand_tokens(t_token **tokens, t_data *dt, t_env *env);
char			*expand_var(const char *src, t_data *dt, t_env *env);

int				check_syntax(t_token *tokens);

//excution :

void    ft_free_red(t_redirection *red);
void	ft_free_cmd(t_command *cmd);
void	ft_free_red(t_redirection *red);

int		ft_exec_cmd(t_command *cmd, t_data *dt);
int		ft_check_heredoc(t_command *cmd, t_data *dt);
int		count_cmds(t_command *cmd);
int		setup_pipe(int *pipe_fd, int *prev_fd, int i, pid_t *pids);
void	cleanup_pids(pid_t *pids, int count);
int 	is_builtin_bo_pipe(t_command *cmd_2, int its_pipe);

void	ft_signals(void);
void	ft_change_global(int flag);
void	ctlc_handler(int sig);

#endif