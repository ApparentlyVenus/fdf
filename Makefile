
NAME = fdf

SRC_DIR = src
INC_DIR = inc
LIB_DIR = lib
MLX_DIR = minilibx-linux

SRC_FILES = draw_line.c \
			map_utils.c \
			map.c \
			parse_utils.c parse.c \
			draw_wireframe.c \
			event_handle.c \
			projections.c \
			color.c \
			main.c \
			validate.c \
			
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(SRCS:.c=.o)

LIBFT = $(LIB_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I$(INC_DIR) -I$(LIB_DIR) -I$(MLX_DIR)
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib/X11 -lXext -lX11 -lm

all: $(NAME)

$(SRCS:.c=.o): %.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIB_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIB_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
