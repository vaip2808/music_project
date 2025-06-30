CXX = g++
CXXFLAGS = -std=c++17 -Wall

SRC = main.cpp music_app.cpp
OBJ = $(SRC:.cpp=.o)

TEST_OBJ = $(TEST_SRC:.cpp=.o)

all: app

app: $(OBJ)
	$(CXX) $(CXXFLAGS) -o app $(OBJ)


clean:
