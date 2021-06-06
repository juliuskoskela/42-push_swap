###############################################################################
#
#	Makefile
#
###############################################################################

NAME		=	libcom.a

SRC_DIR		=	src/
INC_DIR		=	inc/
OBJ_DIR		=	obj/
DEP_DIR		=	.deps/
CORE_DIR	= ../../core

CORE		= $(CORE_DIR)/libcore.a

CC			= gcc
CFLAGS 		= -g -Wall -Wextra -Werror -fPIC
CPPFLAGS	= -I . -I inc -I $(CORE_DIR)
DEPFLAGS	= -MT $@ -MMD -MP -MF $(DEP_DIR)$*.d
COMPILE.c	= $(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -c

SRC_BASE	=	pa.c \
				pb.c \
				ra.c \
				rb.c \
				rra.c \
				rrb.c \
				rr.c \
				rrr.c \
				sa.c \
				sb.c \
				ss.c \
				ps_exec.c \
				ps_free_stacks.c \
				ps_new_stack.c \
				ps_print_stacks.c \
				ps_sorted.c \
				ps_norm_stack.c \

SRC			=	$(addprefix $(SRC_DIR), $(SRC_BASE))
OBJ			=	$(addprefix $(OBJ_DIR), $(SRC_BASE:.c=.o))

all:
				@$(MAKE) -j $(NAME)

$(NAME): $(OBJ)
				@ar -rcs $(NAME) $(OBJ)
				@echo "\\n\033[32;1mCHECKER FUNCTIONS COMPILED\033[0m \\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(DEP_DIR)%.d | $(OBJ_DIR) $(DEP_DIR)
				@$(COMPILE.c) $< -o $@
				@echo $@

$(OBJ_DIR):
				@mkdir -p $@

$(DEP_DIR):
				@mkdir -p $@

$(CORE): $(CORE_DIR)
	@$(MAKE) -C $(CORE_DIR)

DEPFILES = $(addprefix $(DEP_DIR), $(SRC_BASE:.c=.d))
$(DEPFILES):

clean:
				@rm -rf $(OBJ_DIR) $(DEP_DIR)

fclean: clean
				@rm -rf $(NAME);

re: fclean all

.PHONY: all fclean clean re

include $(wildcard $(DEPFILES))