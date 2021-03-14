# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/14 16:39:05 by meldora           #+#    #+#              #
#    Updated: 2021/03/14 20:39:51 by meldora          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

target		:= miniRT

objs		:= $(addprefix srcs/,									\
				$(addprefix errors/,	errors.o)					\
				$(addprefix list_management/,						\
										cam_lstadd_back.o			\
										cam_lstlast.o				\
										cam_lstnew.o				\
										cam_lstsize.o				\
										img_lstadd_back.o			\
										img_lstlast.o				\
										img_lstnew.o				\
										light_lstadd_back.o			\
										light_lstlast.o				\
										light_lstnew.o				\
										object_lstadd_back.o		\
										object_lstlast.o			\
										object_lstnew.o)			\
																	\
				$(addprefix parse/,		utils.o						\
										check_line.o				\
										count_words.o				\
										parse_ambient_lighting.o	\
										parse_camera.o				\
										parse_cylinder.o			\
										parse_light.o				\
										parse_plane.o				\
										parse_resolution.o			\
										parse_sphere.o				\
										parse_square.o				\
										parse_square_utils.o		\
										parse_triangle.o			\
										parser.o)					\
																	\
				$(addprefix vector/,	vector.o)					\
																	\
				$(addprefix rotate/,	matrix.o					\
										quaternion.o)				\
																	\
				$(addprefix intersect/,	get_point.o					\
										draw_sphere.o				\
										draw_cylinder.o				\
										draw_plane.o				\
										draw_square.o				\
										draw_triangle.o)			\
																	\
				$(addprefix	color/,		get_distance.o				\
										get_shadows.o				\
										get_intensity.o				\
										get_color.o)				\
																	\
				$(addprefix draw/,		free_cam.o					\
										hook.o						\
										pixel.o						\
										params.o					\
										render.o					\
										main.o)						\
				)
				


CC			:= gcc

CFLAGS		:= -Wall -Wextra -Werror

all:		$(target)

deps		:= $(patsubstr %.o,%.d,$(objs))
-include	$(deps)
DEPFLAGS	:= -MMD -MF $(@:.o=.d)

miniRT:		$(objs)
			$(CC) $(CCFLAGS) libmlx.dylib -framework OpenGL -framework AppKit $^ get_next_line/*.c libft/*.c -o $@

clean:
			rm -rf $(objs)

%.o:		$(objs)%.c
			$(CC) $(CCFLAGS) -c $^ $(DEPFLAGS)