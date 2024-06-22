CC = cc 

FLAGS = -Wall -Wextra -Werror -g -fsanitize=thread

RM = rm -f 

SRC =	create_philo.c \
		ft_atoi.c \
		get_time.c \
		init_data.c \
		main.c \
		routine.c \
		ft_mutex.c \

OBJ = $(SRC:.c=.o)

NAME = philo

all : $(NAME)


$(NAME) : $(OBJ)
	$(CC) $(FLAGS)  $(OBJ) -o $(NAME)

%.o : %.c philo.h
	$(CC) $(FLAGS) -c $< 

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean $(NAME)