NAME:=cubtest

CC:=clang
CFLAGS=-Wall -Wextra -Werror
# CFLAGS_DEBUG:=-Wall -Wextra -g
# Uncomment the line below to use DWARF-4 debugging information on WSL2
CFLAGS_DEBUG:=-Wall -Wextra -gdwarf-4
DEPFLAGS=-MMD -MF $(DEP_DIR)/$*.d

SRC:=main.c\
	 parse.c\
	 init.c\
	 render.c\
	 loop.c\
	 render_more.c\
	 hitside_color.c\
	 hitwall.c\
	 mlx/init.c\
	 mlx/render.c\
	 mlx/render_line.c\
	 math/utils.c\
	 math/vec2.c\
	 render/minimap.c\

INCLUDE=include mlx $(LIBFT_DIR)/include
LIBRARIES:=X11 Xext m

SRC_DIR:=src
OBJ_DIR:=obj
DEP_DIR:=dep
MLX_DIR:=mlx
LIBFT_DIR:=libft

SRCS:=$(addprefix $(SRC_DIR)/,$(SRC))
OBJS:=$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS:=$(SRCS:$(SRC_DIR)/%.c=$(DEP_DIR)/%.d)
INCS:=$(foreach d,$(INCLUDE),-I$d)
LIBS:=$(foreach l,$(LIBRARIES),-l$l)

MLX:=$(MLX_DIR)/libmlx.a
LIBFT:=$(LIBFT_DIR)/libft.a

all: makelibft $(NAME)

$(NAME): $(OBJS) $(MLX) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) $(LIBFT) $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@mkdir -p $(dir $(DEP_DIR)/$*.d)
	$(CC) $(CFLAGS) $(DEPFLAGS) $(INCS) -c $< -o $@

$(MLX):
	$(MAKE) -C $(MLX_DIR) CC="gcc -std=gnu17" all

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) all

debug:
	@$(MAKE) $(NAME) CFLAGS="$(CFLAGS_DEBUG)"

clean:
	rm -rf $(OBJ_DIR) $(DEP_DIR)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

clangflags:
	@echo $(CFLAGS) $(INCS) | tr ' ' '\n' > compile_flags.txt
	@echo "compile_flags.txt file created"

makelibft:
	$(MAKE) -C $(LIBFT_DIR) all

-include $(DEPS)

.PHONY: all clean fclean re clangflags makelibft
