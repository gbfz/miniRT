# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: meldora <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/04 15:05:37 by meldora           #+#    #+#              #
#    Updated: 2020/12/19 19:55:03 by meldora          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a 

SRCS		= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c 	  \
			  ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memccpy.c   \
			  ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c    \
			  ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_split.c		  \
			  ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c  \
			  ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
			  ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c			  \
			  ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstclear.c  \
			  ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c			  \
			  ft_lstsize.c

OBJS		= ${SRCS:.c=.o}

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

AR			= ar

ARFLAGS		= rc

RM			= rm -rf

.c.o:
			@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			@${AR} ${ARFLAGS} $@ $^

all:		${NAME}

bonus:		all

re:			fclean all

clean:
			@${RM} ${OBJS}

fclean:		clean
			@${RM} ${NAME}
