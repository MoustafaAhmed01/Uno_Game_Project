# UNO Game in C++ - README

Welcome to our UNO game repository! This project was developed entirely from scratch by our team. We are proud to present a fully original implementation with over 6800 lines of code. No external sources were used, and the concept of the game itself was a product of our brainstorming sessions.

## Project Details

- **Supervisor:** Dr. Omar Naser
- **Institution:** Cairo University Faculty of Engineering (Embedded Systems), Data Structure Course

## About the Game

This UNO game implementation is a C++ project that simulates the popular card game UNO. It provides the option to play against the computer or another player. If you choose to play against the computer, there are three difficulty modes available: normal, hard, and insane.

## Key Features

- Utilizes stack and linked list data structures.
- Implements a comprehensive set of UNO cards and rules.
- Supports player-vs-player and player-vs-computer modes.
- Offers different difficulty levels for computer AI.
- Handles power cards, normal cards, and wild cards (color change and plus four).
- Provides detailed game illustrations and explanations.

## How to Play

For a comprehensive guide on how to play UNO, please refer to the official game rules provided by [UltraBoardGames](https://www.ultraboardgames.com/uno/game-rules.php).

## Project Structure

1. **Cards Class:** Defines the CARD structure, which contains information about each card's reference, color, number, and type.

2. **Stack:** Utilizes stack data structure to store and draw cards.

3. **Linked List:** Implements linked list data structure to manage players' cards.

4. **UNO Class:** Controls the game flow, initializes players, and handles the core gameplay logic.

## Gameplay Overview

1. Initialize the CARD structure and create the deck of 108 cards.
2. Shuffle the deck and store it in the stack.
3. Distribute 7 cards to each player using the stack's pop function.
4. Manage player hands using linked lists (Playerone and Playertwo objects).
5. Start the game with the UNO class's Game function by drawing the first card.
6. Alternate turns between players, following UNO rules.

## Difficulty Levels

### Easy

- The computer plays with a slightly random approach.
- Prioritizes playing normal cards and wild cards (color change and plus four).

### Normal

- The computer makes more strategic decisions.
- Prioritizes power cards, then plus four cards, and finally normal cards.

### Hard

- The computer adopts a smarter strategy.
- Prioritizes power cards, plus four cards, normal cards, and then color change cards.

### Insane

- The computer makes highly calculated moves.
- Prioritizes power cards, plus four cards, normal cards (preferring those with different colors), and finally color change cards.

## Conclusion

We hope you enjoy our implementation of the UNO game in C++. Please feel free to explore the code, try different difficulty levels, and provide any feedback you may have. Remember, this project was created with a passion for coding and game development.

Thank you for checking out my repository!

