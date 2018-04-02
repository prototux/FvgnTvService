# Project name
NAME = fvgntvservice

# Compiler and linker options
CC = arm-linux-gnueabihf-gcc
CFLAGS = -I./include -W -Wall -ansi -Wno-unused-parameter --std=gnu99
FPP_DEPS = -lapp-mgr -lcrypt_ntk -lhdcp2_platform -lhdcp_ntk -lnteec -ltcl_dlna -ltcl_pbi -lwotv -lz
LDLIBS = -lm -lonion -lfpp $(FPP_DEPS)
LDFLAGS = -L./lib

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) $(LDLIBS) -o $(NAME)

upload:
	ssh root@${TV_IP} "killall -s KILL ${NAME} 2>/dev/null || exit 0"
	cat ./${NAME} | ssh root@${TV_IP} "cat > /tmp/${NAME}"
	ssh root@${TV_IP} "chmod +x /tmp/${NAME}"

clean:
	rm -f $(OBJ) $(NAME)
	rm -rf doc/output

doc:
	mkdir doc/output
	doxygen doc/Doxyfile

check:
	 cppcheck --quiet --enable=all --suppress=missingIncludeSystem --std=c99  src/

test: $(UNIT_TESTS)

.PHONY: all clean doc
