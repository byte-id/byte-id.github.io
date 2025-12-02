# Programming 1
School Projects in 41039 Programming 1 (2023)
Java & Python

## Games / projects
1. Amateur-Sleuthing - Python
2. The Logical Imitation Game (Turing Machine) - Java
3. This is Indubitably the Bombe - Python, complete version

***Note: 2/3 is the same game, however 3 is the completed version in Python, while 2 has the structure in Java***

## Rules

### Sleuth (1)
* First player (computer) gets 3 random cards from a deck of 64 - one card for each possible combination (4^3)
* Second player asks how many cards the player is holding with a given property or combination and can guess a card the first player is holding
  * Colour, shape, number, colour & shape, colour & number or shape & number
* The game ends when the second player has guessed all the cards the first player is holding

### Turing Machine (2 + 3)
* Machine holds secret answer (3 digit number where each digit is in the range 1-5) and a collection of verifiers
* Goal is to guess the secret answer
  * User guesses 3 digit number and applies 3 verifiers to the number. If the secret number has the same property as guessed number in relation to the verifier, it will return True (Yes). If they do not, it will return False (No).
    *In actual game: digits are represented with symbols, but we will replace these with x, y, z
    * A verifier is a card (lookup table, not on card) that describes some property being tested
    * 4, 5 or 6 verifiers randomly chosen from a set of 48. Play proceeds in round where each player chooses three of the available verifiers to apply. When a player thinks they have deduced the secret number, they declare this, and look up the secret number (can no longer guess). The player who correctly guesses the secret number in the fewest rounds wins
* The results allow for logical deduction of properties of the secret number

Rules of full board game: https://turingmachine.info/files/rules/rules_EN.pdf
