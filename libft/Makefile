NAME	=	libft.a

SRCS	= ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
ft_memchr.c ft_memcmp.c ft_strlen.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
ft_strncmp.c ft_strlcpy.c ft_strlcat.c ft_strnstr.c ft_atoi.c ft_calloc.c \
ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
ft_putnbr.c ft_putstr.c ft_putnbr_base.c ft_intlen.c ft_intlen_base.c

SRCS2	=	$(SRCS) ft_lstnew_bonus.c ft_lstadd_front_bonus.c \
ft_lstadd_back_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

OBJS	=	$(SRCS:.c=.o)

OBJS2 = $(SRCS2:.c=.o)

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

CLEAN	=	clean

all		: $(NAME)

$(NAME)	:	$(OBJS) libft.h
			ar rc $(NAME) $(OBJS)
			ranlib $(NAME)

bonus	: $(OBJS2) libft.h
				ar rc $(NAME) $(OBJS2)
				ranlib $(NAME)

%.o: %.c
			$(CC) $(CFLAGS) -I. -o $@ -c $<

clean	:
			rm -f $(OBJS2)

fclean	:	clean
			rm -f $(NAME)

re		:	fclean all

test	:	fclean bonus
			$(CC) $(CFLAGS) main.c -L. -lft
			./a.out | cat -e

.PHONY:	all clean fclean re bonus test
