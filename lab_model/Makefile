SRC = sdl_main.c renderLab.c imgui.cpp imgui_impl_sdl.cpp \
	imgui_draw.cpp event.cpp ui.cpp app_state_and_events.cpp \
	face.cpp modeler.cpp object.cpp cube.cpp load_tex.cpp \
	door.cpp table.cpp computer.cpp box.cpp aircond.cpp press.cpp power_plug.cpp

OBJ = sdl_main.o renderLab.o imgui.o imgui_impl_sdl.o \
	  imgui_draw.o event.o ui.o app_state_and_events.o \
	  face.o modeler.o object.o cube.o load_tex.o \
	  door.o table.o computer.o box.o aircond.o press.o power_plug.o

INC=`sdl2-config --cflags` `Magick++-config --cppflags` -I /usr/include -I /usr/local/include

LIBS=`sdl2-config --cflags --libs` `Magick++-config --cppflags --libs` -L /usr/lib -L /usr/lib64 -L /usr/local/lib -L /usr/local/lib64 -lGLEW -lGL -lGLU -l glut -lm

.cpp.o:
	c++ -std=c++11 -g -c $<  $(INC)
all: $(OBJ)
	c++ -std=c++11 -o lab_model $(OBJ) $(LIBS)
clean:
	@rm -f *.o lab_model > /dev/null
tags:
	@ctags -fR .

