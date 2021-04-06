PUSH_SWAP =		push_swap
CHECKER =		checker
NAME =			$(PUSH_SWAP) $(CHECKER)
LIBARR_A =		libarr.a
LIBSTR_A =		libstr.a

COMP =			gcc -g -Wall -Werror -Wextra -I inc -I array/inc -I array/libarr -I string/inc -I string/libst -c -o

OBJ_DIR =		obj/
S_SRC_DIR =		src_common/
P_SRC_DIR =		src_push_swap/
C_SRC_DIR =		src_checker/
LIBARR =		array/
LIBSTR =		string/

S_SRC =			utils.c \
				commands.c \

P_SRC =			push_swap.c \

C_SRC =			checker.c \

S_OBJ =			$(S_SRC:%.c=%.o)
P_OBJ =			$(P_SRC:%.c=%.o)
C_OBJ =			$(C_SRC:%.c=%.o)
OBJ =			$(S_OBJ) $(P_OBJ) $(C_OBJ)

S_SRC_PATH =   	$(S_SRC:%=$(S_SRC_DIR)%)
P_SRC_PATH =   	$(P_SRC:%=$(P_SRC_DIR)%)
C_SRC_PATH =   	$(C_SRC:%=$(C_SRC_DIR)%)
SRC_PATH =		$(S_SRC_PATH) $(P_SRC_PATH) $(C_SRC_PATH)

S_OBJ_PATH =	$(addprefix $(OBJ_DIR), $(S_OBJ))
P_OBJ_PATH =	$(addprefix $(OBJ_DIR), $(P_OBJ))
C_OBJ_PATH =	$(addprefix $(OBJ_DIR), $(C_OBJ))
OBJ_PATH =		$(S_OBJ_PATH) $(P_OBJ_PATH) $(C_OBJ_PATH)

all:			complibs $(OBJ_DIR) $(NAME)
				@echo "\\n\033[32;1m PUSH_SWAP AND CHECKER COMPLETE \033[0m \\n"

$(OBJ_DIR):
				@mkdir -p $(OBJ_DIR)
				@echo Create: Object directory

$(NAME):		$(OBJ_PATH)
				@gcc -g $(S_OBJ_PATH) $(P_OBJ_PATH) *.a -o push_swap \
					-I includes -I libft/includes
				@gcc -g $(S_OBJ_PATH) $(C_OBJ_PATH) *.a -o checker \
					-I includes -I libft/includes

$(S_OBJ_PATH):	$(S_SRC_PATH)
				@$(MAKE) $(S_OBJ)

$(P_OBJ_PATH):	$(P_SRC_PATH)
				@$(MAKE) $(P_OBJ)

$(C_OBJ_PATH):	$(C_SRC_PATH)
				@$(MAKE) $(C_OBJ)

$(S_OBJ):		$(LIBARR_A) $(LIBSTR_A)	
				@echo Create: $(@:obj/%=%)"\x1b[1A\x1b[M"
				@$(COMP) $(OBJ_DIR)$@ $(S_SRC_DIR)$(@:%.o=%.c)
$(C_OBJ):		$(LIBARR_A) $(LIBSTR_A)	
				@echo Create: $(@:obj/%=%)"\x1b[1A\x1b[M"
				@$(COMP) $(OBJ_DIR)$@ $(C_SRC_DIR)$(@:%.o=%.c)
$(P_OBJ):		$(LIBARR_A) $(LIBSTR_A)	
				@echo Create: $(@:obj/%=%)"\x1b[1A\x1b[M"
				@$(COMP) $(OBJ_DIR)$@ $(P_SRC_DIR)$(@:%.o=%.c)

complibs:
				@make -C $(LIBARR)
				@make -C $(LIBSTR)
				@cp $(LIBARR)/$(LIBARR_A) .
				@cp $(LIBSTR)/$(LIBSTR_A) .


clean:
				@/bin/rm -rf $(OBJ_DIR) $(LIBARR_A) $(LIBSTR_A)
				@make -C $(LIBARR) clean
				@make -C $(LIBSTR) clean
				@echo "\\n\033[32;1m Cleaned libft object files \033[0m"

fclean:			clean
				@/bin/rm -f $(PUSH_SWAP) $(CHECKER) $(LIBARR_A) $(LIBSTR_A)
				@make -C $(LIBARR) fclean
				@make -C $(LIBSTR) fclean
				@echo "\\n\033[32;1m Cleaned $(NAME) \033[0m \\n"

re: 			fclean all

.PHONY:			all clean flcean re colorUSH_SWAP		= push_swap
