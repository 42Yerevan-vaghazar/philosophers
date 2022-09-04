NAME = philo

BONUS = philo_bonus

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = $(wildcard ./src/*.c)

SRCS_BONUS = $(wildcard ./src_bonus/*.c)

OBJS = $(patsubst %.c, %.o, $(SRCS))

SRCS_BONUS += $(filter-out ./src/main.c, $(SRCS))

OBJS_BONUS = $(patsubst %.c, %.o, $(SRCS_BONUS))

RM = rm -f

# $(info $$var is [$(SRCS_BONUS)])

.c.o:
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

all: $(NAME) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lpthread -o $(NAME)

bonus: $(BONUS)

$(BONUS): $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -lpthread -lm -lrt -o $(BONUS)

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(BONUS)

re:	fclean all

.PHONY: all clean fclean re bonus .c.o
