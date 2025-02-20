NAME= cub3d

CFLAGS=  -Wall -Wextra -Werror #-fsanitize=address -g

LIB = MLX/build/libglfw3.a MLX/build/libmlx42.a  -framework Cocoa -framework OpenGL -framework IOKit

SRCS= 	./mandatory/main.c ./mandatory/utils.c ./mandatory/get_next_line.c\
		./mandatory/get_next_line_utils.c ./mandatory/print.c ./mandatory/map.c\
		./mandatory/get_colors.c ./mandatory/draw.c ./mandatory/init_things.c\
		./libc/parse_split.c ./libc/parse_substr.c ./libc/small_functions.c\

GREEN = "\033[32m"

OBJS= ${SRCS:.c=.o}

all :  $(NAME)

$(NAME): $(OBJS)
	@echo ${GREEN}"Compiling ${NAME}..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIB)  -o $(NAME)
	@echo "Successfully compiled ${NAME}!"

%.o:%.c ./include/*.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)

fclean: clean
	@rm -rf $(NAME)

re: clean all