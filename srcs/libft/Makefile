# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/04 15:05:37 by meldora           #+#    #+#              #
#    Updated: 2021/03/15 18:41:41 by meldora          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

target		:= libft.a 

objs		:=	ft_atof.o ft_atoi.o ft_bzero.o ft_calloc.o ft_isalnum.o		\
				ft_isalpha.o ft_isascii.o ft_isdigit.o ft_isprint.o			\
				ft_isspace.o ft_itoa.o ft_lstadd_back.o ft_lstadd_front.o	\
				ft_lstclear.o ft_lstdelone.o ft_lstiter.o ft_lstlast.o		\
				ft_lstmap.o ft_lstnew.o ft_lstsize.o ft_memccpy.o			\
				ft_memchr.o ft_memcmp.o ft_memcpy.o ft_memmove.o			\
				ft_memset.o ft_putchar_fd.o ft_putendl_fd.o ft_putnbr_fd.o	\
				ft_putstr_fd.o ft_split.o ft_strchr.o ft_strcmp.o			\
				ft_strdup.o ft_strjoin.o ft_strlcat.o ft_strlcpy.o			\
				ft_strlen.o ft_strmapi.o ft_strncmp.o ft_strnstr.o			\
				ft_strrchr.o ft_strtrim.o ft_substr.o ft_tolower.o			\
				ft_toupper.o

CC			:= gcc

CFLAGS		:= -Wall -Wextra -Werror

AR			:= ar

ARFLAGS		:= rc

RM			= rm -rf

all:		$(target)

deps		:= $(patsubst %.o,%.d,$(objs))
-include	$(deps)
DEPFLAGS	= -MMD -MF $(@:.o=.d)

$(target):	$(objs)
			$(AR) $(ARFLAGS) $@ $^

%.o:		%.c
			$(CC) $(CFLAGS) -c $< $(DEPFLAGS)

clean:
			rm -rf $(objs) $(deps)

fclean:		clean
			rm -rf $(target)