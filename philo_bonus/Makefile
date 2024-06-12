CC = cc

FLAGS = -Wall -Wextra -Werror -pthread -fsanitize=thread -g

SRC =	create_process_bonus.c \
		main_bonus.c \
		data_init_bonus.c \
		ft_atoi_bonus.c \
		get_time_bonus.c \
		routine_bonus.c \
		print_bonus.c \

OBJ = $(SRC:.c=.o)

NAME = philo_bonus

RM = rm -f 

%.o : %.c philo_bonus.h
	$(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	$(CC)  $(FLAGS)  $(OBJ)  -o $(NAME)

clean : 
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean $(NAME)