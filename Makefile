NAME = fdf

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3
LDFLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

RM = rm -rf

SRCS = $(wildcard src/*.c) libft/libft.a
SRCS_BONUS = $(wildcard src_bonus/*.c) libft/libft.a

OBJ = $(SRCS:.c=.o)
OBJ_BONUS = $(SRCS_BONUS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	make all -C mlx_linux
	make all -C libft
	$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

libft/libft.a:
	make all -C libft

bonus: libft/libft.a $(OBJ_BONUS)
	make all -C mlx_linux
	$(CC) $(OBJ_BONUS) $(LDFLAGS) -o $(NAME)

all: $(NAME)

fclean: clean
	$(RM) $(NAME)
	make clean -C mlx_linux
	make fclean -C libft

clean:
	$(RM) $(filter-out libft/libft.a, $(OBJ) $(OBJ_BONUS))
	make clean -C mlx_linux
	make clean -C libft

re: fclean all
