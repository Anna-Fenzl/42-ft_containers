# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/04 15:03:12 by afenzl            #+#    #+#              #
#    Updated: 2023/02/21 12:31:06 by afenzl           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_FT = ft_containers 
NAME_STD = std_containers 

CPP = c++
CPP_FLAGS = -Wall -Werror -Wextra -g -std=c++98
RM := rm -f

HEADER = ./include/vector.hpp ./include/stack.hpp ./include/map.hpp ./include/set.hpp\
		 ./include/iterators/iterator.hpp ./include/iterators/vector_iterator.hpp \
		 ./include/iterators/reverse_iterator.hpp ./include/iterators/rbt_iterator.hpp \
		 ./include/utils/type_traits.hpp ./include/utils/compare.hpp \
		 ./include/utils/pair.hpp ./include/utils/rbt_node.hpp ./include/utils/redblack.hpp \
		 ./tests/ft/ft_tests.hpp ./tests/std/tests.hpp

FT_PATH = ./tests/ft/
STD_PATH = ./tests/std/

FT_SRC = $(FT_PATH)ft_main.cpp $(FT_PATH)ft_vector.cpp $(FT_PATH)ft_stack.cpp $(FT_PATH)ft_map.cpp $(FT_PATH)ft_set.cpp $(FT_PATH)ft_other.cpp
STD_SRC = $(STD_PATH)std_main.cpp $(STD_PATH)std_vector.cpp $(STD_PATH)std_stack.cpp $(STD_PATH)std_map.cpp $(STD_PATH)std_set.cpp $(STD_PATH)std_other.cpp

STD_OBJ = $(STD_SRC:.cpp=.o)
FT_OBJ = $(FT_SRC:.cpp=.o)

all: $(NAME_FT) $(NAME_STD)
	@echo "                                                         "
	@echo " \033[0;31m  ___|\033[0;32m   _ \ \033[0;33m   \  |\033[0;34m   _ \ \033[0;35m_ _|\033[0;36m  |   \033[0;31m   ____|\033[0;32m  __ \ \033[0;33m  | "
	@echo " \033[0;31m |    \033[0;32m  |   |\033[0;33m  |\/ |\033[0;34m  |   |\033[0;35m  | \033[0;36m  |   \033[0;31m   __|  \033[0;32m  |   |\033[0;33m  | "
	@echo " \033[0;31m |    \033[0;32m  |   |\033[0;33m  |   |\033[0;34m  ___/ \033[0;35m  | \033[0;36m  |   \033[0;31m   |    \033[0;32m  |   |\033[0;33m _| "
	@echo " \033[0;31m\____|\033[0;32m \___/ \033[0;33m _|  _|\033[0;34m _|    \033[0;35m___|\033[0;36m _____|\033[0;31m _____|\033[0;32m ____/ \033[0;33m _) \033[0m"
	@echo "                                                        "

$(NAME_FT): $(FT_OBJ) $(HEADER)
	@$(CPP) $(CPP_FLAGS) $(FT_OBJ) -o $(NAME_FT)

$(NAME_STD): $(STD_OBJ)
	@$(CPP) $(CPP_FLAGS) $(STD_OBJ) -o $(NAME_STD)

clean:
	@$(RM) $(FT_OBJ) $(STD_OBJ)
	@echo "\033[0;33m removed object files!\033[0m"

fclean: clean
	@$(RM) $(NAME_FT) $(NAME_STD) 
	@echo "\033[0;31m removed binary file!\033[0m"

re: fclean all
