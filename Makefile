CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla
OBJECTS = main.o game.o board.o piece.o scoreboard.o tile.o textdisplay.o builder.o move.o subject.o player.o computereasy.o computermedium.o computerhard.o window.o graphicsdisplay.o 
EXEC = chess
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
