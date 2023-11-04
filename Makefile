# Nombre del ejecutable
TARGET = graph

# Compilador
CC = g++

# Flags de compilación
CFLAGS = -std=c++11 -Wall -I include

# Directorio de los archivos de código fuente
SRCDIR = src

# Directorio de los archivos objeto
OBJDIR = obj

# Encuentra todos los archivos de C++ en el directorio src para compilar
SRC = $(wildcard $(SRCDIR)/*.cpp)

# Sustituye la extensión .cpp de los archivos fuente por .o para los objetos
OBJ = $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Regla principal
all: $(TARGET)

# Regla para enlazar el ejecutable
$(TARGET): $(OBJ)
	$(CC) $^ -o $@

# Regla para compilar los archivos fuente
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para limpiar los archivos compilados
clean:
	rm -f $(OBJDIR)/*.o $(TARGET)

# Regla para imprimir variables (útil para depuración)
print-%:
	@echo $* = $($*)

# Incluye dependencias
-include $(OBJ:.o=.d)

# Regla que genera archivos de dependencia
$(OBJDIR)/%.d: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -MM -MT $(@:.d=.o) $< -MF $@
