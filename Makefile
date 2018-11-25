# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/04 14:33:42 by sjuery            #+#    #+#              #
#    Updated: 2018/11/06 14:14:06 by sjuery           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= nibbler

SRC		= 	srcs/nibbler.cpp

OBJ 	= $(SRC:.c=.o)
CFLAGS	= -Wall -Wextra -Werror -g -O3 -fsanitize=address -fsanitize=undefined -march=native -std=c++14
LDFLAGS = -fsanitize=address -fsanitize=undefined

all: $(NAME)

$(NAME): $(OBJ)
	@printf '\033[31m[...] %s\n\033[0m\033[33m' "Creating Nibbler"
	g++ $(LDFLAGS) $(CFLAGS) -shared -fPIC $(shell pkg-config --cflags sfml-graphics sfml-window sfml-system) $(shell pkg-config --libs sfml-graphics sfml-window sfml-system) -Wl,-rpath /nfs/2017/s/sjuery/.brew/lib srcs/extern_sfml.cpp -o extern_sfml.dylib
	g++ $(LDFLAGS) $(CFLAGS) -shared -fPIC -lncurses srcs/extern_ncursus.cpp -o extern_ncursus.dylib
	g++ $(LDFLAGS) $(CFLAGS) -shared -fPIC -framework OpenGl -I/nfs/2017/s/sjuery/.brew/Cellar/glfw/3.2.1/include -I/nfs/2017/s/sjuery/.brew/Cellar/glm/0.9.9.3/include -I/nfs/2017/s/sjuery/.brew/Cellar/glfw/3.2.1/include srcs/extern_opengl.cpp -o extern_opengl.dylib -L/nfs/2017/s/sjuery/.brew/Cellar/glfw/3.2.1/lib -lglfw -framework Cocoa -framework IOKit -framework CoreFoundation -framework CoreVideo
	g++ $(LDFLAGS) $(CFLAGS) $^ -o $(NAME)
	@printf '\033[32m[ ✔ ] %s\n\033[0m' "Created Nibbler"

clean:
	@printf '\033[31m[...] %s\n\033[0m' "Cleaning Nibbler"
	@/bin/rm -f *.dylib
	@/bin/rm -rf *.dSYM
	@printf '\033[32m[ ✔ ] %s\n\033[0m' "Cleaned Nibbler"

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all test
