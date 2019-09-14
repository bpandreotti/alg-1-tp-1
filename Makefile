CC := g++
CFLAGS := -g -Wall

TARGET := ./tp1
SRCDIR := src
OBJDIR := obj

# Encontra todos os arquivos .cpp no diretorio src
SOURCES := $(shell find $(SRCDIR) -type f -name *.cpp)

# Descobre quais são os arquivos .o do projeto, substituindo o
# diretório e a extensão dos arquivos .cpp encontrados
# e.g. src/foo.cpp  =>  obj/foo.o
OBJECTS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

# Linka os arquivos .o para formar o binário final
$(TARGET): $(OBJECTS)
	@mkdir -p $(@D) # Criar diretório caso necessário
	@$(CC) $^ -o $@

# Compila cada arquivo .cpp para seu .o respectivo
$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@mkdir -p $(@D) # Criar diretório caso necessário
	@$(CC) $(CFLAGS) -c $^ -o $@

# Comando run, compila (se necessário) e roda o binário target
.PHONY: run
run: $(TARGET)
	@$(TARGET)

# Comando clean, deleta todos os arquivos .o e o binário target
.PHONY: clean
clean:
	@rm -rf $(TARGET) $(OBJDIR)/*
