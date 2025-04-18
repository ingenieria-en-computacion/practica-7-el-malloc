# Configuración
CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -g
LDFLAGS = -lm
TEST_LDFLAGS = -lcheck -lm -lpthread

# Fuentes
COMMON_SRCS = src/node.c src/linkedlist.c
APP_SRC = src/main.c
TEST_SRC = test/main.c

# Targets
APP_TARGET = bin/linkedlist_app
TEST_TARGET = bin/linkedlist_test

.PHONY: all app test clean memcheck run-app run-test

# Crear directorio bin si no existe
$(shell mkdir -p bin)

# Default: compilar todo
all: app test

# Compilar solo la aplicación
app: $(APP_TARGET)

# Compilar solo los tests
test: $(TEST_TARGET)

# Regla para la aplicación
$(APP_TARGET): $(APP_SRC) $(COMMON_SRCS)
    $(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

# Regla para los tests
$(TEST_TARGET): $(TEST_SRC) $(COMMON_SRCS)
    $(CC) $(CFLAGS) $^ $(TEST_LDFLAGS) -o $@

# Ejecutables
run-app: $(APP_TARGET)
    ./$(APP_TARGET)

run-test: $(TEST_TARGET)
    ./$(TEST_TARGET)

# Chequeo de memoria
memcheck: $(TEST_TARGET)
    valgrind --leak-check=full ./$(TEST_TARGET)

# Limpieza
clean:
    rm -rf bin
