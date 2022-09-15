NAME = philo

CC = cc

CFLAGS = -g

SRCS = $(wildcard ./src/*.c)

OBJS = $(patsubst %.c, %.o, $(SRCS))

RM = rm -f

.c.o:
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

all: $(NAME) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lpthread -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re bonus .c.o
