FLAGS = -I. -std=c++11
all: main
main:
	g++ -c action/action.cpp $(FLAGS)
	g++ -c file/file.cpp $(FLAGS)
	g++ -c frame/frame.cpp $(FLAGS)
	g++ -c miv/controller.cpp $(FLAGS)
	g++ -c miv/miv.cpp $(FLAGS)
	g++ -c ui/ui.cpp $(FLAGS)
	g++ -c xarray/xarray.cpp $(FLAGS)
	g++ -c ui/ncurses.cpp $(FLAGS)
	g++ -o main main.cpp $(FLAGS)
	rm *.o 

