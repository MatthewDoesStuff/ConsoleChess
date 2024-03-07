#include <iostream>

#include "src/Chess.hpp"
#include "src/Board.hpp"

class App
{
public:
	App() = default;
	~App() = default;

	void run()
	{
		std::cout << chess << '\n';
		while (!chess.getCheckMate())
		{
			std::string startPos, movePos;

			std::cout << "pick a figure you want to move: " << '\n';
			std::cin >> startPos;

			std::cout << "choose where do you want to move: " << '\n';
			std::cin >> movePos;

			const auto& moveData = chess.convertMoveData(startPos, movePos);
			if (!chess.move(moveData))
			{
				continue;
			}
			else
			{
				chess.changeTurn();
			}
			std::cout << chess << '\n';
		}
	}

private:
	Chess chess;
};


int main()
{
	App app;
	app.run();

	return 0;
}
