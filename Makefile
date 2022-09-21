SRCDIR1 = ./prog1/

SRCDIR2 = ./prog2/

OBJDIR1 = ./objects/

OBJDIR2 = ./objects/

SRCS1 = $(wildcard $(SRCDIR1)*.cpp)

SRCS2 = $(wildcard $(SRCDIR2)*.cpp)

OBJ1 = $(patsubst $(SRCDIR1)%.cpp, $(OBJDIR1)%.o, $(SRCS1))

OBJ2 = $(patsubst $(SRCDIR2)%.cpp, $(OBJDIR2)%.o, $(SRCS2))

HEADER1 = ./headers/common_client.hpp

HEADER2 = ./headers/common_server.hpp

CC = g++

NAME1 = client

NAME2 = server

all			:	$(NAME1) $(NAME2)

serv		:	$(NAME2)

cli			:	$(NAME1)

$(NAME1)	:	$(OBJ1)
	$(CC) $(SRCS1) -o $(NAME1)

$(NAME2)	:	$(OBJ2)
	$(CC) $(SRCS2) -o $(NAME2)

$(OBJDIR1)%.o: $(SRCDIR1)%.cpp $(HEADER1)
	$(CC) -c $< -o $@

$(OBJDIR2)%.o: $(SRCDIR2)%.cpp $(HEADER2)
	$(CC) -c $< -o $@

clean	:
	rm -rf $(OBJDIR1)*.o

fclean	:	clean
	rm -rf $(NAME1) $(NAME2)