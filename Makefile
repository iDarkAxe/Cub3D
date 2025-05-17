.PHONY : all clean fclean re bonus clean-lib clean-bin clean-obj debug debug-cc debug-print
CC = cc
CFLAGS = -Wextra -Wall -Werror
DEPENDANCIES = -MMD -MP
NO_DIR = --no-print-directory
MAKE := $(MAKE) -j $(NO_DIR)
NAME_TEST = test
NAME = cub3d

# Debugging flags
CFLAGS_DEBUG = -Wall -Wextra -g3 -D DEBUG=1
CC_DEBUG = clang
CC_DEBUG_CFLAGS = -g3 -D DEBUG=1 -Weverything -Wno-padded -pedantic -O2 -Wwrite-strings -Wconversion -fsanitize=address -fsanitize=leak -Wno-suggest-override -Wno-suggest-destructor-override -Wno-incompatible-pointer-types-discards-qualifiers -Wno-disabled-macro-expansion -Wno-strict-prototypes
#############################################################################################
#                                                                                           #
#                                         DIRECTORIES                                       #
#                                                                                           #
#############################################################################################
# Source directories
P_SRC = src/
P_DRAW = draw/
P_MAP_VERIF = map_verif/
P_UTILS = utils/
P_PLAYER = player/
P_PRINT = print/

# Object directories
P_OBJ = .obj/

# Header directories
P_INC = inc/
P_INC_MLX = inc_mlx/

P_INCS = \
	$(P_INC) \
	$(P_INC_MLX) \
	$(P_LIBFT)inc/

# Libraries directories
P_LIB = lib/
P_LIBFT = libft/
#############################################################################################
#                                                                                           #
#                                           FILES                                           #
#                                                                                           #
#############################################################################################
# Headers
INC = \
	ft_keys.h \
	so_long.h \
	ft_textures.h \
	ft_print.h

INC_MLX = \
	mlx.h 

# Source files
SRC = \
	main.c \
	cub3d.c \
	ft_hooks.c \

DRAW = \
	ft_draw.c \
	ft_draw_map.c \
	ft_store_textures.c

MAP_VERIF = \
	ft_map_dimensions.c \
	ft_map_fill.c \
	ft_verify_access.c

UTILS = \
	ft_map_utils.c \
	ft_random.c \
	ft_free.c \
	ft_exit.c \
	ft_strdup.c

PLAYER = \
	ft_player.c

PRINT = \
	ft_print.c \
	ft_print_special.c

LIBS = \
	libmlx_Linux.a \
	libso_long.a

IMG = \
	parquet_versailles.xpm \
	end_portal_off.xpm \
	end_portal_on.xpm \
	player_fl_end_portal_off.xpm \
	player_fr_end_portal_off.xpm \
	stone_bricks_v2.xpm 

IMG_UNUSED = \
	player.xpm \
	settings.xpm

LIBS = \
	-L$(P_LIBFT) -lft \
	-Lminilibx-linux -lmlx_Linux \
	-lXext \
	-lX11

LIBFT = $(P_LIBFT)libft.a
#############################################################################################
#                                                                                           #
#                                        MANIPULATION                                       #
#                                                                                           #
#############################################################################################
SRCS =	\
	$(addprefix $(P_SRC), $(SRC)) \
	$(addprefix $(P_SRC)$(P_DRAW), $(DRAW)) \
	$(addprefix $(P_SRC)$(P_MAP_VERIF), $(MAP_VERIF)) \
	$(addprefix $(P_SRC)$(P_UTILS), $(UTILS)) \
	$(addprefix $(P_SRC)$(P_PLAYER), $(PLAYER)) \
	$(addprefix $(P_SRC)$(P_PRINT), $(PRINT))

# List of object files (redirect to P_OBJ)
OBJS = $(subst $(P_SRC), $(P_OBJ), $(SRCS:.c=.o))
P_OBJS = $(subst $(P_SRC), $(P_OBJ), $(SRCS))

# List of depedencies
DEPS = $(OBJS:%.o=%.d)

# List of header files
INCS = \
	$(addprefix $(P_INC), $(INC)) \
	$(addprefix $(P_INC_MLX), $(INC_MLX)) \
	$(P_LIBFT)inc/libft.h
#############################################################################################
#                                                                                           #
#                                          RULES                                            #
#                                                                                           #
#############################################################################################
all:
	@$(MAKE) $(NAME)

# Create so_long executable
$(NAME): $(OBJS) $(INCS) $(LIBFT) $(P_LIB)libmlx_Linux.a
	@if $(CC) $(CFLAGS) $(DEPENDANCIES) $(DEBUG_STATE) -I $(P_INC) -I $(P_INC_MLX) -I $(P_LIBFT)inc -o $(NAME) $(OBJS) $(LIBS); then \
		echo "$(Green)Creating executable $@$(Color_Off)"; \
	else \
		echo "$(Red)Error creating $@$(Color_Off)"; \
	fi

# Custom rule to compilate all .c with there path
$(P_OBJ)%.o: $(P_SRC)%.c $(INCS)
	@mkdir -p $(dir $@)
	@if $(CC) $(CFLAGS) $(DEPENDANCIES) $(DEBUG_STATE) -I $(P_INC) -I $(P_INC_MLX) -I $(P_LIBFT)inc -c $< -o $@; then \
		echo "$(Cyan)Compiling $<$(Color_Off)"; \
	else \
		echo "$(Red)Error creating $@$(Color_Off)"; \
	fi

force:

$(LIBFT): force
	@$(MAKE) -C $(P_LIBFT)

# Create mlx library
$(P_LIB)libmlx_Linux.a:
	@mkdir -p $(P_LIB)
	@$(MAKE) -C minilibx-linux
	@cp minilibx-linux/libmlx_Linux.a $(P_LIB)
	@cp minilibx-linux/mlx.h inc_mlx/
	@cp /usr/include/X11/X.h inc_mlx/

#############################################################################################
#                                                                                           #
#                                      Other RULES                                          #
#                                                                                           #
#############################################################################################
# Rules for clean up
clean:
	@rm -rfd $(P_OBJ)
	@rm -rfd $(OBJS)
	@rm -rfd $(DEPS)
	@$(MAKE) -C minilibx-linux clean > /dev/null 2>&1
	@echo "$(Green)Cleaned $(P_OBJ), $(OBJS), $(DEPS) and minilibx-linux$(Color_Off)"

clean-lib:
	@rm -rfd $(P_LIB)
	$(MAKE) -C $(P_LIBFT) fclean
	@echo "$(Green)Cleaned $(P_LIB)$(Color_Off)"
	@echo "$(Green)Cleaned $(P_LIBFT)$(Color_Off)"

clean-bin:
	@rm -f $(NAME)
	@rm -f $(NAME_TEST)
	@echo "$(Green)Cleaned $(NAME)$(Color_Off)"

clean-obj:
	@$(MAKE) clean

fclean:
	@$(MAKE) clean-obj
	@$(MAKE) clean-lib
	@$(MAKE) clean-bin
	@$(MAKE) -C minilibx-linux clean > /dev/null 2>&1

re:
	@$(MAKE) fclean
	@$(MAKE) all

# Aliases
clear: clean
fclear: fclean
flcean: fclean
flcear: fclean

#############################################################################################
#                                                                                           #
#                                           DEBUG                                           #
#                                                                                           #
#############################################################################################
# Debugging rules
debug:
	@$(MAKE) $(OBJS) CFLAGS="$(CFLAGS_DEBUG)"

debug-cc:
	@$(MAKE) $(OBJS) CFLAGS="$(CC_DEBUG_CFLAGS)" CC="$(CC_DEBUG)" Cyan="$(Yellow)" Green="$(Purple)"

# Debugging print
debug-print:
	@$(MAKE) debug-print-project

debug-print-separator:
	@echo ""
	@echo "$(On_Yellow)____________________$(Color_Off)"
	@echo ""

define check_var
	@if [ "$(strip $(1))" = "" ]; then \
		echo "$(Red)No $(2) found$(Color_Off)"; \
	else \
		echo "$(Red)$(2): \n\t$(Blue)$(1)$(Color_Off)"; \
	fi
endef

debug-print-project:
	$(call check_var,$(NAME),"Project")
	$(call check_var,$(SRCS),"SRCS")
	$(call check_var,$(OBJS),"OBJS")
	$(call check_var,$(INCS),"INCS")
	$(call check_var,$(LIBS),"LIBS")
	@$(MAKE) debug-print-separator
	$(call check_var,$(SRCS_TEST),"SRCS_TEST")
	$(call check_var,$(OBJS_TEST),"OBJS_TEST")

#############################################################################################
#                                                                                           #
#                                         COSMETIC                                          #
#                                                                                           #
#############################################################################################
# Reset
Color_Off=\033[0m	# Text Reset

# Regular Colors
Black=\033[0;30m
Red=\033[0;31m
Green=\033[0;32m
Yellow=\033[0;33m
Blue=\033[0;34m
Purple=\033[0;35m
Cyan=\033[0;36m
White=\033[0;37m

# Background
On_Black=\033[40m
On_Red=\033[41m
On_Green=\033[42m
On_Yellow=\033[43m
On_Blue=\033[44m
On_Purple=\033[45m
On_Cyan=\033[46m
On_White=\033[47m

-include $(DEPS)%