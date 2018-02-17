##
## Makefile for Makefile in rendu/UNIX/CONCURRENCE
## 
## Made by anony
## Login   <yoann.wargnier@epitech.eu>
## 
## Started on  Mon Mar 13 14:59:44 2017 anony
## Last update Thu Mar 16 20:36:37 2017 thomas desforges
##

CC		= gcc

CFLAGS		+= -I./include -Wall -Wextra -Werror

LDFLAGS		+= -L. -lriceferee -lpthread

RM		= rm -f

SRCS		= main.c \
		  philo.c

OBJS		= $(SRCS:.c=.o)

NAME		= philo

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

all:		$(NAME)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
