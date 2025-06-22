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
CC_DEBUG_CFLAGS = -g3 -D DEBUG=1 -Weverything -Wno-padded -pedantic -O2 -Wwrite-strings -Wconversion -Wno-suggest-override -Wno-suggest-destructor-override -Wno-incompatible-pointer-types-discards-qualifiers -Wno-disabled-macro-expansion -Wno-strict-prototypes

#############################################################################################
#                                                                                           #
#                                         DIRECTORIES                                       #
#                                                                                           #
#############################################################################################
# Source directories
P_SRC = src/
P_MAP_VERIF = map_verif/
P_FT_MLX = ft_mlx/
P_PARSING = parsing/
P_PRINT = print/

# Object directories
P_OBJ = .obj/

# Header directories
P_INC = inc/
P_INC_MLX = $(P_MLX)

P_INCS = \
	$(P_INC) \
	$(P_INC_MLX) \
	$(P_LIBFT)inc/

# Libraries directories
P_LIB = lib/
P_LIBFT = libft/
P_GET_NEXT_LINE = get_next_line/
P_MLX = minilibx-linux/
#############################################################################################
#                                                                                           #
#                                           FILES                                           #
#                                                                                           #
#############################################################################################
# Headers
INC = \
	cub3d.h \
	ft_keys.h \
	ft_print.h

INC_MLX = \
	mlx.h 

# Source files
SRC = \
	main.c \
	cub3d.c \
	ft_safe.c \
	ft_free.c \
	ft-utils.c

FT_MLX = \
	ft_init_mlx.c

MAP_VERIF = \
	ft_file_fill.c \
	ft_map_check.c \
	ft_search_config.c \
	ft_search_map.c \
	ft_check_colors.c \
	ft_map_boundaries.c \
	ft_validate_map.c \

PARSING = \
	check_args.c \

PRINT = \
	ft_print_errors.c \
	ft_print_special.c \
	ft_print_color.c \

LIBS = \
	-L$(P_LIBFT) -lft \
	-L$(P_GET_NEXT_LINE) -lgnl \
	-L$(P_LIBFT) -lft \
	-L$(P_MLX) -lmlx_Linux \
	-lXext \
	-lX11

LIBFT = $(P_LIBFT)libft.a
GET_NEXT_LINE = $(P_GET_NEXT_LINE)libgnl.a
#############################################################################################
#                                                                                           #
#                                        MANIPULATION                                       #
#                                                                                           #
#############################################################################################
SRCS =	\
	$(addprefix $(P_SRC), $(SRC)) \
	$(addprefix $(P_SRC)$(P_MAP_VERIF), $(MAP_VERIF)) \
	$(addprefix $(P_SRC)$(P_MLX), $(MLX)) \
	$(addprefix $(P_SRC)$(P_PARSING), $(PARSING)) \
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

# Create cub3d executable
$(NAME): $(OBJS) $(INCS) $(LIBFT) $(P_MLX)libmlx_Linux.a $(GET_NEXT_LINE)
	@if $(CC) $(CFLAGS) $(DEPENDANCIES) $(DEBUG_STATE) -I $(P_INC) -I $(P_GET_NEXT_LINE) -I $(P_INC_MLX) -I $(P_LIBFT)inc -o $(NAME) $(OBJS) $(LIBS); then \
		echo "$(Green)Creating executable $@$(Color_Off)"; \
	else \
		echo "$(Red)Error creating $@$(Color_Off)"; \
	fi

# Custom rule to compilate all .c with there path
$(P_OBJ)%.o: $(P_SRC)%.c $(INCS)
	@mkdir -p $(dir $@)
	@if $(CC) $(CFLAGS) $(DEPENDANCIES) $(DEBUG_STATE) -I $(P_INC) -I $(P_GET_NEXT_LINE) -I $(P_INC_MLX) -I $(P_LIBFT)inc -c $< -o $@; then \
		echo "$(Cyan)Compiling $<$(Color_Off)"; \
	else \
		echo "$(Red)Error creating $@$(Color_Off)"; \
	fi

bonus:
	@echo "$(Red)No bonus available now$(Color_Off)"

force:

$(LIBFT): force
	@$(MAKE) -C $(P_LIBFT)

$(GET_NEXT_LINE): force
	@$(MAKE) -C $(P_GET_NEXT_LINE)

# Create mlx library
$(P_MLX)libmlx_Linux.a: force
	@$(MAKE) -C $(P_MLX) --silent CFLAGS="$(CFLAGS_MLX)" CC="gcc" all $(HIDE_STDOUT)

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
	@$(MAKE) -C $(P_MLX) clean HIDE=0
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
	@$(MAKE) $(NAME) CFLAGS="$(CFLAGS_DEBUG)"

debug-cc:
	@$(MAKE) $(NAME) CFLAGS="$(CC_DEBUG_CFLAGS)" CC="$(CC_DEBUG)" Cyan="$(Yellow)" Green="$(Purple)"

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
# Flag to hide output
# 0 = Show output, 1 = Hide output
# HIDE_STDOUT is used to redirect the output of the make command
HIDE ?= 1
ifeq ($(HIDE),1)
HIDE_STDOUT =>/dev/null
else
HIDE_STDOUT =
endif

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
On_Yellow=\033[43m

-include $(DEPS)