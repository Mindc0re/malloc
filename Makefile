ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME				=	libft_malloc_$(HOSTTYPE).so

INCLUDE_DIR			=	./includes/

MALLOC_DIR 			=	./srcs/

C_FLAGS				=	-Wall -Wextra -Werror -fPIC

FILES_MALLOC		=	ft_malloc.c malloc_utils.c zones_handling.c show_alloc_mem.c \
						find_alloc.c ft_free.c free_utils.c ft_realloc.c lib_utils.c

SRC_MALLOC			=	$(addprefix $(MALLOC_DIR), $(FILES_MALLOC))
BIN_MALLOC			= 	$(FILES_MALLOC:.c=.o)

INCLUDES 	= -I $(INCLUDE_DIR)
ALL_SRCS 	= $(SRC_MALLOC)
ALL_BINS 	= $(BIN_MALLOC) 

all: $(NAME)

$(NAME):
	gcc $(C_FLAGS) $(INCLUDES) $(ALL_SRCS) -c
	gcc $(C_FLAGS) -shared $(ALL_BINS) -o $(NAME)
	ln -s $(NAME) libft_malloc.so
	mkdir bin_folder
	mv $(ALL_BINS) bin_folder

clean:
	rm -rf bin_folder

fclean: clean
	rm -rf $(NAME) libft_malloc.so

re: fclean all