NAME = project3
SRC_DIR = ./srcs/
OBJ_DIR = ./objs/
INCLUDE_DIR = ./includes/
CC = data.cc \
	io.cc \
	memory.cc \
	operate.cc \
	paging.cc \
	parse.cc \
	victim.cc \
	queue.cc
O = $(CC:.cc=.o)
SRCS = $(addprefix $(SRC_DIR), $(CC))
OBJS = $(addprefix $(OBJ_DIR), $(O))

GCC = g++ -I$(INCLUDE_DIR)
RM = rm -rf

$(NAME) : $(OBJS)
	$(GCC) -o $(NAME) $^

$(OBJ_DIR)%.o : $(SRC_DIR)%.cc
	$(GCC) -c $< -o $@

.PHONY : re all clean test

all : $(NAME)

re : clean all

clean : 
	$(RM) $(OBJS)
	$(RM) $(NAME)