SRCS=src/pipex.c \
     src/pipe.c \
     src/heredoc.c \
     src/system_calls.c \
	 src/get_next_line.c \
	 src/get_next_line_utils.c

NORMAL_SRCS=$(SRCS)
TEST_SRCS=$(SRCS) test.c

LIB_DIR=./lib
LIB_SRCS=$(wildcard $(LIB_DIR)/*.c)
LIBFT=./lib/libft.a

NAME=pipex
NAME_TEST= pipex_test
CC=cc -Wall -Werror -Wextra

ifeq ($(DEBUG), 1)
    DEBUGFLAGS =-g
endif

OBJ=$(patsubst %.c, %.o, $(NORMAL_SRCS))
OBJ_TEST=$(patsubst %.c, %.o, $(TEST_SRCS))

all: $(LIBFT) $(NAME)

$(LIBFT): $(LIB_SRCS)
	@make -C $(LIB_DIR)

%.o: %.c
	$(CC)  -c $< -o $@ $(DEBUGFLAGS)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBFT) -o $@ $(DEBUGFLAGS)

$(NAME_TEST): $(OBJ_TEST)
	$(CC) $(OBJ_TEST) $(LIBFT) -o $@ $(DEBUGFLAGS)

test: $(NAME_TEST)
	./$(NAME_TEST)

clean:
	rm -rf $(OBJ) $(OBJ_TEST)
fclean:
	rm -rf $(OBJ) $(OBJ_TEST) $(NAME)

re:
	@make fclean
	@make all
norm: 
	norminette $(SRCS)

.PHONY:all clean fclean re norm test
