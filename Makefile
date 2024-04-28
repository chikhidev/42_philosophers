NAME = philo
CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address

SRC = 	main.c	\
		config.c	\
		routine.c	\
		time.c

SRC += 	utils/ft_atoi.c  \
		utils/ft_itoa.c  \
		utils/ft_memcpy.c  \
		utils/ft_strdup.c  \
		utils/ft_strlen.c  \
		utils/ft_strncmp.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Compiling philo..."
	@cc $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	@cc $(CFLAGS) -c $< -o $@ -g

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all