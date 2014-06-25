#include <SFML/Graphics.hpp>
#include "TetrisGame.h"

int main() {
  TetrisGame game;
  game.initGame();
  game.gameLoop();
  game.closeGame();
}
