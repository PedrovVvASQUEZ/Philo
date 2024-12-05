# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgrellie <pgrellie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/31 16:14:27 by pgrellie          #+#    #+#              #
#    Updated: 2024/11/28 15:13:43 by pgrellie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

######################################################### 
# TERMINAL COLORS OP ##

NORMAL = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m
EPIX_WHITE = \033[5;97m
EPIX_GREEN = \033[5;92m
EPIX_RED = \033[5;91m

#########################################################
##### FOLDERS PATH ####

SRCS_DIR = ./srcs_mandatory/
SRCS_BONUS_DIR = ./srcs_bonus/
OBJS_DIR = ./Objs/
BIN_DIR = ./bin/
HEADER_DIR = ./Includes/

#########################################################
###### ARGUMENTS ######

NAME = $(BIN_DIR)philo
CFLAGS = -Wall -Werror -Wextra -g -g3
COMP = cc
RM = rm -rf
MKDIR = mkdir -p

##########################################################
######  SOURCES  ######
SRCS_FILES = death_managing.c\
				init_philo.c\
				parsing.c\
				the_routine.c\
				utils.c\
				philo.c\

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_FILES))			

##########################################################
######  OBJECTS  ######

OBJS_FILES = $(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS))
OBJS = $(addprefix $(OBJS_DIR), $(OBJS_FILES))

##########################################################
######   RULES   ######

all: $(NAME)
	
$(NAME) : $(OBJS_DIR) $(OBJS_FILES)
	@echo "$(GREEN)\n<<< Done >>>\n$(NORMAL)"
	@echo "$(YELLOW)\nBuilding project ...\n$(NORMAL)"
	@$(MKDIR) $(BIN_DIR)
	@$(LIBFT_MAKE_COMMAND)
	@$(COMP) $(CFLAGS) $(OBJS_FILES) -o $(NAME)
	@echo "$(GREEN)\n<<< [MINISHELL] has been compiled >>>\n" 
	@echo "$(EPIX_WHITE)                   /!\/!\/!\/!\/!\/!\ \n$(NORMAL)" 
	@echo "$(WHITE) Use this command : ./bin/philo Nb_philos && T_to_die && T_to_eat && T_to_sleep && [Meal_nb]\n$(NORMAL)"
	
#Creer le repertoire 'Objs' et compiles C source files into object files
$(OBJS_DIR):
	@echo "$(YELLOW)\nProcessing c files into o files ...\n$(NORMAL)"
	@$(MKDIR) $(OBJS_DIR)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@$(MKDIR) $(dir $@)
	@$(COMP) $(CFLAGS) -I $(HEADER_DIR) -c $< -o $@

#Clean objects files and dependencies
clean:
	@$(RM) $(OBJS_DIR) $(OBJS_BONUS_DIR)
	@echo "$(MAGENTA)\n<<< Object files have been removed >>>\n$(NORMAL)"

#Cleans everething generated by the Makefile
fclean: clean
	@$(RM) $(NAME) $(BIN_DIR) $(OBJS_DIR)
	@echo "$(MAGENTA)\n<<< Executable files, object files and Directories have been removed >>>\n$(NORMAL)"

#Remake	
re: fclean all

.PHONY: all clean fclean re