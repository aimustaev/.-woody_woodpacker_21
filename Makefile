NAME 		= woody_woodpacker
SRCS 		= woody_woodpacker.c \
				parse_utils.c read_file_utils.c g_decryptor.c \
				encrypt_func.c error.c

OBJS		= $(SRCS:.c=.o)
LIBFT		= ./libft/libft.a
LIBFT_SOURCES := $(shell find libft -name "*.c")
LIBFT_OBJECTS := $(LIBFT_SOURCES:.c=.o)
# CFLAGS		= -Wall -Werror -Wextra -I$(dir $(LIBFT)) -MMD
CFLAGS		= -Werror -I$(dir $(LIBFT)) -MMD
CC			= gcc

all:		$(NAME)

$(NAME):	$(OBJS) $(LIBFT)
			nasm -f bin inject.s -o g_decryptor
			xxd -i -c8 g_decryptor g_decryptor.c
			gcc  -o $(NAME) -L$(dir $(LIBFT)) -lft $(OBJS) $(LIBFT_OBJECTS)
			@echo ""
			@echo "▂▃▅▇█▓▒░ DONE ░▒▓█▇▅▃▂"
			@echo ""

$(LIBFT):	FORCE
			make bonus -C $(dir $(LIBFT))

FORCE:

-include	$(SRCS:.c=.d)

clean:
			make clean -C $(dir $(LIBFT))
			$(RM) $(OBJS) $(SRCS:.c=.d)

fclean:		clean
			$(RM) $(LIBFT)
			$(RM) $(NAME)

re:			fclean all

run:		$(NAME)
			./$(NAME)

.PHONY: 	all clean fclean re run norm


# nasm -f bin inject.s -o g_decryptor