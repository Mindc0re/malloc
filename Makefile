# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dvirgile <dvirgile@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/24 18:13:29 by dvirgile          #+#    #+#              #
#    Updated: 2017/02/24 18:20:39 by dvirgile         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	malloc

INCLUDE_DIR			=	./includes

MALLOC_DIR 			=	./srcs/

COMPILER			=	gcc
C_FLAGS				=	-Wall -Wextra -Werror

FILES_MALLOC		=	ft_malloc.c malloc_utils.c zones_handling.c show_alloc_mem.c main.c

SRC_MALLOC			=	$(addprefix $(MALLOC_DIR), $(FILES_MALLOC))
BIN_MALLOC			= 	$(FILES_MALLOC:.c=.o)

INCLUDES 	= -I$(INCLUDE_DIR)
ALL_SRCS 	= $(SRC_MALLOC)
ALL_BINS 	= $(BIN_MALLOC)

all: $(NAME)

$(NAME):
	gcc $(C_FLAGS) -g $(INCLUDES) $(ALL_SRCS) -c
	gcc $(C_FLAGS) -g $(ALL_BINS) -o $(NAME)
	mkdir bin_folder
	mv $(ALL_BINS) bin_folder

clean:
	rm -rf bin_folder

fclean: clean
	rm -rf $(NAME)

re: fclean all