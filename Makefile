SRCS=pipex.c \
     pipe.c \
     heredoc.c \
     system_calls.c

LIB_DIR=./lib
LIB_SRCS=$(wildcard $(LIB_DIR)/*.c)
LIBFT=./lib/libft.a

NAME=pipex
CC=cc -Wall -Werror -Wextra

ifeq ($(DEBUG), 1)
    DEBUGFLAGS =-g
endif

OBJ=$(patsubst %.c, %.o, $(SRCS))

all: $(LIBFT) $(NAME)

$(LIBFT): $(LIB_SRCS)
	@make -C $(LIB_DIR)

%.o: %.c
	$(CC)  -c $< -o $@ $(DEBUGFLAGS)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBFT) -o $@ $(DEBUGFLAGS)

clean:
	rm -rf $(OBJ)
fclean:
	rm -rf $(OBJ) $(NAME)
re:
	@make fclean
	@make all
norm: 
	norminette $(SRCS)

.PHONY:all clean fclean re norm
