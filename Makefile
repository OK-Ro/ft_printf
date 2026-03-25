NAME = libftprintf.a
SRC = ft_print.c ft_printf_char.c \
		ft_printf_str.c ft_printf_nbr.c \
		ft_printf_ptr.c ft_printf_unit.c ft_printf_hex.c
OBJECT = $(SRC: .c=.o)
CC = cc 
CFLAGS = -Wall -Wextra -Werror

#DEFAULT RULE
all: $(NAME) 

#BUILD LIBRARY
$(NAME): $(OBJECT)
	ar rcs $(NAME) $(OBJECT)

# COMPILE .c -> .o
%.o: %.c ft_print.h.
	$(CC) $(CFLAGS) -c $< -o $@

# CLEAN OBJECT FILES
clean:
	rm -f $(OBJECT)

# REMOVE OBJECT FILES AND LIBRARY
fclean: clean
	rm -f $(NAME)

# REBUILD EVERYTHING
re: fclean all

# TEST PROGRAM
test: $(NAME)
	$(CC) test_ft_printf.c -L. -lftprinft -lbsd -o test
	./test

.PHONY: clean fclean re test all
