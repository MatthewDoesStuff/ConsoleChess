#include <iostream>

#include "src/chess.hpp"
#include "src/board.hpp"

int main() {
	Chess C;
	Board B;
	std::cout << B << std::endl;

	while (!B.isCheckMate()) {
		C.moveData = Chess::getMoveData();
		while(!B.checkMoveDataForNullptr(C.moveData))
		{
			C.moveData = Chess::getMoveData();
		}
		B.move(C.moveData);
		std::cout << B << std::endl;
	}

	return 0;
}
