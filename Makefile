SRCS	=	srcs/main.cpp
SRCSVECTOR = srcs/mainVector.cpp
SRCSSTACK = srcs/mainStack.cpp
SRCSMAP = srcs/mainMap.cpp

OBJS	=	${SRCS:.c=.o}
OBJSVECTOR	=	${SRCSVECTOR:.c=.o}
OBJSSTACK	=	${SRCSSTACK:.c=.o}
OBJSMAP	=	${SRCSMAP:.c=.o}

CXX		=	c++

CFLAGS0	=	-Wall -Werror -Wextra -DVERSION=0 -std=c++98
CFLAGS1	=	-Wall -Werror -Wextra -DVERSION=1 -std=c++98

NAME0	=	containers_ft
NAME1	=	containers_std

${NAME0}	:	${OBJS}
		${CXX} ${CFLAGS0} ${OBJS} -o ${NAME0} 

${NAME0}_vector	:	${OBJSVECTOR}
		${CXX} ${CFLAGS0} ${OBJSVECTOR} -o ${NAME0}
${NAME0}_stack	:	${OBJSSTACK}
		${CXX} ${CFLAGS0} ${OBJSSTACK} -o ${NAME0}
${NAME0}_map	:	${OBJSMAP}
		${CXX} ${CFLAGS0} ${OBJSMAP} -o ${NAME0}

${NAME1}	:	${OBJS}
		${CXX} ${CFLAGS1} ${OBJS} -o ${NAME1} 

${NAME1}_vector	:	${OBJSVECTOR}
		${CXX} ${CFLAGS1} ${OBJSVECTOR} -o ${NAME1}
${NAME1}_stack	:	${OBJSSTACK}
		${CXX} ${CFLAGS1} ${OBJSSTACK} -o ${NAME1}
${NAME1}_map	:	${OBJSMAP}
		${CXX} ${CFLAGS1} ${OBJSMAP} -o ${NAME1}

all		:	${NAME0} ${NAME1}

vector		:	${NAME0}_vector ${NAME1}_vector
	./$(NAME0) 10
	./$(NAME0) 10000 > containersFT
	./$(NAME1) 10000 > containersSTD
	diff containersFT containersSTD
	@echo "NO DIFF WAS RECORDED";

stack		:	${NAME0}_stack ${NAME1}_stack
	./$(NAME0) 10
	./$(NAME0) 10000 > containersFT
	./$(NAME1) 10000 > containersSTD
	diff containersFT containersSTD
	@echo "NO DIFF WAS RECORDED";

map		:	${NAME0}_map ${NAME1}_map
	./$(NAME0) 10
	./$(NAME0) 10000 > containersFT
	./$(NAME1) 10000 > containersSTD
	diff containersFT containersSTD
	@echo "NO DIFF WAS RECORDED";

test : $(NAME0) $(NAME1)
	./$(NAME0) 10000 > containersFT
	./$(NAME1) 10000 > containersSTD
	diff containersFT containersSTD
	@echo "NO DIFF WAS RECORDED";

clean	:

fclean	:	clean
			rm -rf ${NAME0} ${NAME1} containersFT containersSTD
			$(MAKE) -C . clean

re	:	fclean all

.PHONY	:	all clean fclean re
