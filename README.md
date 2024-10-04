Pachinko Game (Console-based)
Overview
  This is a Pachinko Game developed in C. Pachinko is a popular mechanical game from Japan, and this version is a simple, text-based console implementation. The game mimics the action of dropping balls into   a vertical board, where they bounce off pegs and land in different slots, determining the score.

Features
  -Text-based Gameplay: Play the game directly from the terminal.
  -Randomized Ball Movement: The balls follow a randomized path as they bounce off pegs and obstacles.
  -Score Calculation: The player's score is determined by the slot where the ball lands.
  -Simple UI: The game runs purely in the terminal, with ASCII art representing the board.


How to Run the Game
  Prerequisites:
    - A C compiler like gcc must be installed on your system.
  Steps to Run:
    - Clone the repository or download the ZIP file:
      git clone https://github.com/AliSoua/Pachinko-Game-Simulation.git
  Alternatively, you can download the project as a ZIP and extract it.


Compile the Game: Open a terminal in the project directory and run:

bash
  gcc -o pachinko pachinko.c
  Run the Game: Once compiled, run the game with:

bash
  ./pachinko
  Controls:
  -The game will prompt you to release balls.
  -Enter the required input, and watch the results displayed in the terminal as the balls fall through the board.
  -The game displays your total score once all balls have been released.
