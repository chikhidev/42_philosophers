NAME = philo
CFLAGS = -Wall -Wextra -Werror

SRC =	philo.c 	\
		parse.c 	\
		routine.c

SRC += 	utils/ft_atoi.c		\
		utils/ft_itoa.c		\
		utils/ft_strlen.c	\
		utils/ft_strncmp.c	\
		utils/ft_strdup.c	\
		utils/ft_memcpy.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

b: all clean

$(NAME): $(OBJ)
	@cc $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	@cc $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)