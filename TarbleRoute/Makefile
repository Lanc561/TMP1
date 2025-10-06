# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
LDFLAGS = 

# Имя исполняемого файла
TARGET = TableRouteCipher

# Директории
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# Исходные файлы
SOURCES = $(SRCDIR)/main.cpp $(SRCDIR)/TableRouteCipher.cpp
OBJECTS = $(OBJDIR)/main.o $(OBJDIR)/TableRouteCipher.o

# Правило по умолчанию
all: $(BINDIR)/$(TARGET)

# Создание исполняемого файла
$(BINDIR)/$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# Компиляция объектных файлов
$(OBJDIR)/main.o: $(SRCDIR)/main.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/TableRouteCipher.o: $(SRCDIR)/TableRouteCipher.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Создание директорий
$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

# Очистка
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Пересборка
rebuild: clean all

# Запуск программы
run: all
	./$(BINDIR)/$(TARGET)

# Отладочная сборка
debug: CXXFLAGS += -g -DDEBUG
debug: rebuild

# Помощь
help:
	@echo "Доступные цели:"
	@echo "  all      - сборка программы (по умолчанию)"
	@echo "  clean    - удаление скомпилированных файлов"
	@echo "  rebuild  - полная пересборка"
	@echo "  run      - сборка и запуск программы"
	@echo "  debug    - отладочная сборка"
	@echo "  help     - показать эту справку"

.PHONY: all clean rebuild run debug help
