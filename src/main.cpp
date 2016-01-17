#include "Game.hpp"

int main(int argc, char* argv[])
{
    Game game;
    //AnimationFilmHolder* an = AnimationFilmHolder::Get();
    //an->Load("../src/data.json",game._renderer);
	return game.OnExecute();
	
}