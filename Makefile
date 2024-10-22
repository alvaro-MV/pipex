SRCS=src/pipex.c \
     src/pipe.c \
     src/system_calls.c \

SRCS_BONUS=bonus/get_next_line_bonus.c \
	 	   bonus/get_next_line_utils_bonus.c \
		   bonus/heredoc.c \
		   bonus/pipex_bonus.c \
		   bonus/pipe_bonus.c \
		   bonus/system_calls_bonus.c \
		   bonus/bonus_utils.c

LIB_DIR=./lib
LIBFT=./lib/libft.a

NAME=pipex
NAME_BONUS= pipex_bonus
CC=cc -Wall -Werror -Wextra 

ifeq ($(DEBUG), 1)
    DEBUGFLAGS =-g
endif

OBJ=$(SRCS:.c=.o)
OBJ_BONUS=$(SRCS_BONUS:.c=.o)

all: $(NAME)

$(LIBFT):
	@make -sC $(LIB_DIR) 

%.o: %.c
	$(CC)  -c $< -o $@ $(DEBUGFLAGS)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(OBJ) $(LIBFT) -o $@ $(DEBUGFLAGS)

$(NAME_BONUS): $(LIBFT) $(OBJ_BONUS)
	$(CC) $(OBJ_BONUS) $(LIBFT) -o $@ $(DEBUGFLAGS)

bonus: $(NAME_BONUS)

clean:
	make -sC $(LIB_DIR) fclean
	rm -rf $(OBJ) $(OBJ_BONUS)
fclean: clean
	rm -rf $(NAME) $(NAME_BONUS)

re: fclean all

norm: 
	norminette $(SRCS)

.PHONY:all clean fclean re norm bonus
