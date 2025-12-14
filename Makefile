INC= -I include
SRC=src
INC=include
OBJ=obj
FLAGS=-Wall -Wextra -Werror 
LINK= -lcml -lkeyutils -lnuma -lc -lm




install: dir libcml.a
	sudo mv libcml.a /usr/lib
	sudo rm -rf /usr/include/cml
	sudo mkdir /usr/include/cml 
	sudo cp include/* /usr/include/cml
	rm -rf obj


$(OBJ)/ml.o: $(SRC)/ml.c 
	gcc $(FLAGS) -D _GNU_SOURCE -c  $< -o $@

$(OBJ)/vector.o: $(SRC)/vector.c
	gcc $(FLAGS) -D _GNU_SOURCE  -c $< -o $@ 

$(OBJ)/math.o: $(SRC)/math.c
	gcc $(FLAGS) -D _GNU_SOURCE -c $< -o $@

libcml.a:  $(OBJ)/math.o  $(OBJ)/vector.o  $(OBJ)/ml.o
	ar -rv libcml.a $^


dir:
	mkdir -p obj
