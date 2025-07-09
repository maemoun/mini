# ==================== VARIABLES ====================
NAME    := minishel
CC      := cc

# LIBPATH = /Users/sabderra/.local/readline
RDLINE_PRFX = $(shell brew --prefix readline)
FLAGS =  -I$(RDLINE_PRFX)/lib 
LDFLAGS =  -lreadline -lhistory


SRC     := main.c \
           utils.c \
           token_append.c \
           syntax_errors.c \
           expand.c \
           join_tokens.c \
           tokens_type.c \
           print.c \
           add_spaces.c \
           is_funcs.c \
           get_command_args.c \
           init_env.c \
           get_redirections.c \
		   get_token_end.c \
		   expand_var.c \
		   remove_quotes.c \
                   ft_exec_cmd.c \
                   ft_free.c \
                   ft_exec_utils_1.c \
                   ft_exec_utils_2.c \
                   ft_exec_herdoc.c \
                   signals.c

        #    signals.c  \


OBJ     := $(SRC:.c=.o)


# ==================== TARGETS ====================
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(LDFLAGS) -o $(NAME) $(LDFLAGS)

%.o: %.c main.h
	$(CC) $(FLAGS) -c $< -o $@

# ==================== CLEANING ====================
clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)

re: fclean all

me: fclean all
	./$(NAME)

# ==================== ========= ====================


















