SRCS=src/pipex.c \
     src/pipe.c \
     src/system_calls.c \
	 src/checker_args.c

SRCS_BONUS=bonus/get_next_line_bonus.c \
	 	   bonus/get_next_line_utils_bonus.c \
		   bonus/heredoc.c \
		   bonus/pipex_bonus.c \
		   bonus/pipe_bonus.c \
		   bonus/system_calls_bonus.c \
		   bonus/checker_args_bonus.c

LIB_DIR=./lib
LIBFT=./lib/libft.a

NAME=pipex
NAME_BONUS= pipex_bonus
CC=cc -Wall -Werror -Wextra

ifeq ($(DEBUG), 1)
    DEBUGFLAGS =-g
endif

OBJ=$(patsubst %.c, %.o, $(SRCS))
OBJ_BONUS=$(patsubst %.c, %.o, $(SRCS_BONUS))

all: $(NAME)

$(LIBFT):
	@make -Cs $(LIB_DIR)

%.o: %.c
	$(CC)  -c $< -o $@ $(DEBUGFLAGS)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBFT) -o $@ $(DEBUGFLAGS)

$(NAME_BONUS): $(OBJ_BONUS)
	$(CC) $(OBJ_BONUS) $(LIBFT) -o $@ $(DEBUGFLAGS)

bonus: $(NAME_BONUS)

clean:
	rm -rf $(OBJ) $(OBJ_BONUS)
fclean:
	rm -rf $(OBJ) $(OBJ_BONUS) $(NAME)

re:
	@make -s fclean
	@make all
norm: 
	norminette $(SRCS)

.PHONY:all clean fclean re norm bonus
