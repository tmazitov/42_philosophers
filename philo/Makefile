NAME := philo

GREEN := \033[0;32m
NC := \033[0m
CC := gcc
CFLAGS := -Wall -Wextra -Werror -fsanitize=address

SRCS := philo.c \
		philo_state.c \
		philo_state_utils.c \
		philo_validation.c \
		fork/fork.c \
		fork/fork_utils.c \
		fork/fork_storage.c \
		fork/fork_storage_lock.c \
		fork/fork_storage_check.c \
		fork/fork_storage_actions.c \
		person/person.c \
		person/person_utils.c \
		person/person_behavior.c \
		person/person_storage.c \
		person/person_storage_dead.c \
		person/person_storage_lock.c \
		utils/ft_atoi.c \
		utils/ft_itoa.c \
		utils/ft_strcmp.c \
		utils/ft_strchr.c \
		utils/ft_isdigit.c \
		utils/ft_strlen.c \
		utils/ft_usleep.c \


OBJS := $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME) 
	@echo "$(GREEN)Philo build successfully!$(NC)"

all: $(NAME)

clean:
	rm -f $(OBJS)
	@echo "$(GREEN)Philo clean successfully!$(NC)"

fclean: clean
	rm -f $(NAME)
	@echo "$(GREEN)Philo clean all successfully!$(NC)"

re:		fclean all

.PHONY: all, re, clean, fclean