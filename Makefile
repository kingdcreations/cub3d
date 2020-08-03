NAME	=	libcub3d.a

LIBFT	=	libft/libft.a

MINILIBX = minilibx-linux/libmlx.a

CC		=	gcc -fsanitize=leak -g3 -Wall -Wextra -Werror -O2

ERROR	=	\033[0;31m
DONE	=	\033[0;32m
INFO	=	\033[0;36m
NC		=	\033[0m

SRC =	main.c \
			gnl/get_next_line.c \
			gnl/get_next_line_utils.c \
			ft_parsefile.c \
			ft_managefile.c \
			ft_handlefile.c \
			ft_errorfile.c \
			ft_save.c \
			ft_draw.c \
			ft_color.c \
			ft_sprite.c \
			ft_sprite_list.c \
			ft_myhooks.c \
			ft_keyhandling.c \
			ft_image.c \
			ft_dda.c \

OBJ		=	$(SRC:%.c=%.o)

all:		$(NAME)

$(LIBFT):
	@echo "${INFO}Calling libft makefile${NC}"
	@make -C libft

$(MINILIBX):
	@echo "${INFO}Calling minilibx-linux makefile${NC}"
	@make -C minilibx-linux

$(NAME): $(OBJ) $(LIBFT) $(MINILIBX)
	@echo "${DONE}Making libcub3d.a${NC}"
	@cp libft/libft.a $(NAME)
	@cp minilibx-linux/libmlx.a libmlx.a
	@ar rcs $(NAME) $(OBJ)
	gcc -fsanitize=leak -g3 -Wall -Werror -Wextra -O2 main.c ft_bonus_off.c libmlx.a -o Cub3D -L.  -lcub3d -lX11 -lXext -lbsd -lm -lmlx -Lmlx

%.o: %.c libftprintf.h libft/libft.h
	@$(CC) -o $@ -c $<

clean:
	@echo "${INFO}Cleaning all object files${NC}"
	@rm -f $(OBJ)
	@make clean -C libft
	@make clean -C minilibx-linux

fclean: clean
	@echo "${INFO}Cleaning all${NC}"
	@rm -f $(NAME)
	@rm -f Cub3D
	@make fclean -C libft
	@make clean -C minilibx-linux
	@rm -rf libmlx.a
	@rm -rf output.bmp

bonus: all
	gcc -Wall -Werror -Wextra -O3 main_bonus.c ft_bonus_on.c minilibx_macos/libmlx.a -L. -lcub3d -framework OpenGL -framework AppKit -o Cub3D

re: fclean all

test: all
	./cub3d test.cub

bmp: all
	./cub3d test.cub -save

.PHONY:	all clean fclean re bonus test
