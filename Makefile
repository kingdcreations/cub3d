NAME	=	libcub3d.a

LIBFT	=	libft/libft.a

MINILIBX = minilibx_macos/libmlx.a

CC		=	gcc -Wall -Wextra -Werror -O3

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

OBJ		=	$(SRC:%.c=%.o)

all:		$(NAME)

$(LIBFT):
	@echo "${INFO}Calling libft makefile${NC}"
	@make -C libft

$(MINILIBX):
	@echo "${INFO}Calling minilibx_macos makefile${NC}"
	@make -C minilibx_macos

$(NAME): $(OBJ) $(LIBFT) $(MINILIBX)
	@echo "${DONE}Making libcub3d.a${NC}"
	@cp libft/libft.a $(NAME)
	@ar rcs $(NAME) $(OBJ)

%.o: %.c libftprintf.h libft/libft.h
	@$(CC) -o $@ -c $<

clean:
	@echo "${INFO}Cleaning all object files${NC}"
	@rm -f $(OBJ)
	@make clean -C libft
	@make clean -C minilibx_macos

fclean: clean
	@echo "${INFO}Cleaning all${NC}"
	@rm -f $(NAME)
	@make fclean -C libft
	@make clean -C minilibx_macos

bonus: $(NAME)

re: fclean all

test:
	gcc -Wall -Werror -Wextra -O3 main.c minilibx_macos/libmlx.a -L. -lcub3d -framework OpenGL -framework AppKit -o cub3d && ./cub3d test.cub

bmp:
	gcc -g3 -Wall -Werror -Wextra -O3 main.c minilibx_macos/libmlx.a -L. -lcub3d -framework OpenGL -framework AppKit -o cub3d && ./cub3d test.cub -save

.PHONY:	all clean fclean re bonus test
