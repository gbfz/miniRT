NAME		:=	miniRT

objs		:=	get_next_line_utils.o		\
			get_next_line.o			\
							\
			errors.o			\
							\
			vector.o			\
							\
			cam_lstadd_back.o		\
			cam_lstlast.o			\
			cam_lstnew.o			\
			cam_lstsize.o			\
			img_lstadd_back.o		\
			img_lstlast.o			\
			img_lstnew.o			\
			light_lstadd_back.o		\
			light_lstlast.o			\
			light_lstnew.o			\
			object_lstadd_back.o		\
			object_lstlast.o		\
			object_lstnew.o			\
							\
			utils.o				\
			utils2.o			\
			check_line.o			\
			count_words.o			\
			parse_ambient_lighting.o	\
			parse_camera.o			\
			parse_cylinder.o		\
			parse_light.o			\
			parse_plane.o			\
			parse_resolution.o		\
			parse_sphere.o			\
			parse_square.o			\
			parse_square_utils.o		\
			parse_triangle.o		\
			parser.o			\
							\
			matrix.o			\
			quaternion.o			\
							\
			get_point.o			\
			draw_sphere.o			\
			draw_cylinder_utils.o		\
			draw_cylinder.o			\
			draw_plane.o			\
			draw_square_utils.o		\
			draw_square.o			\
			draw_triangle.o			\
			draw_triangle_utils.o		\
							\
			get_distance.o			\
			get_shadows.o			\
			get_intensity.o			\
			get_color.o			\
							\
			free_cam.o			\
			hook.o				\
			pixel.o				\
			params.o			\
			render.o			\
			bmp.o				\
			main.o

VPATH		:=	srcs/errors:srcs/list_management:	\
			srcs/vector:srcs/parse:srcs/rotate:	\
			srcs/intersect:srcs/color:srcs/draw:	\
			srcs/get_next_line

CC		:=	gcc

CFLAGS		:=	-Wall -Wextra -Werror

all:		$(NAME)

deps		:= $(patsubst %.o,%.d,$(objs))
-include	$(deps)
DEPFLAGS	= -MMD -MF $(@:.o=.d)

$(NAME):	$(objs)
		make -C srcs/libft && cp srcs/libft/libft.a .
		make -C srcs/minilibx_mms_20200219 && cp srcs/minilibx_mms_20200219/libmlx.dylib .
		$(CC) $(CFLAGS) -O3 -I./includes libmlx.dylib libft.a -framework OpenGL -framework AppKit $^ -o $@

libft:		srcs/libft/*.d
		make -C srcs/libft && cp srcs/libft/libft.a .

%.o:		%.c
		$(CC) $(CFLAGS) -c $< $(DEPFLAGS)

clean:
		rm -rf $(objs) $(deps)
		make clean -C srcs/libft
		make clean -C srcs/minilibx_mms_20200219

fclean:		clean
		rm -rf $(NAME) libft.a libmlx.dylib
		make fclean -C srcs/libft
