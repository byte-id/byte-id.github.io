from cap import Shape, Colour, Card, Player
from random import shuffle  # Just here to shuffle the deck

# Complete this function

def play(player: Player) -> None:
    print("Welcome to Sleuth!")
    # print(deck[0:3])
    guessedCards = []
    correctCards = []
    numberofQuest = 0
    incorrectGuess = 0
    while True:
        topmenu()
        menu1 = int(input("Which option would you like? "))
        if menu1 == 1:
            questionChoice()
            numberofQuest = pickQuest(player, numberofQuest)
        elif menu1 == 2:
            incorrectGuess = guessCard(player, incorrectGuess, guessedCards, correctCards)
        else:
            notOption()
        if len(correctCards) == 3:
            finishGame(correctCards, numberofQuest, incorrectGuess)
            break

def topmenu():
    print("Would you like to:\n"
        "1. Ask a question.\n"
        "2. Guess a card.")


questionOptions = [
    "How many cards with a certain colour?",
    "How many cards with a certain shape?",
    "How many cards with a certain number?",
    "How many cards with a certain colour and number?",
    "How many cards with a certain shape and number?",
    "How many cards with a certain colour and shape?"
]


def questionChoice():
    print("Which question would you like to ask?")
    for i, quest in enumerate(questionOptions, start=1):
        print(f"{i}. {quest}")

def pickQuest(player, numberofQuest):
    while True:
        qChoice = int(input("Which option would you like? "))
        # if qChoice in [1, 2, 3]:
        #     numberofQuest += 1
        # elif qChoice in [4, 5, 6]:
        #     numberofQuest += 2
        if qChoice in [1, 2, 3, 4, 5, 6]:
            numberofQuest += 1

        match qChoice:
            case 1:
                colour = colourOpt()
                count = player.how_many_colour(colour)
                print(f"The player has {count} cards with colour {colour}.")
            case 2:
                shape = shapeOpt()
                count = player.how_many_shape(shape)
                print(f"The player has {count} cards with shape {shape}.")
            case 3:
                number = numberOpt()
                count = player.how_many_number(number)
                print(f"The player has {count} cards with number {number}.")
            case 4:
                colour = colourOpt()
                number = numberOpt()
                count = player.how_many_colour_number(colour, number)
                print(f"The player has {count} cards with colour {colour} and number {number}.")
            case 5:
                shape = shapeOpt()
                number = numberOpt()
                count = player.how_many_shape_number(shape, number)
                print(f"The player has {count} cards with shape {shape} and number {number}.")
            case 6:
                colour = colourOpt()
                shape = shapeOpt()
                count = player.how_many_colour_shape(colour, shape)
                print(f"The player has {count} cards with colour {colour} and shape {shape}.")
            case _:
                notOption()
                questionChoice()
                continue
        break
    return numberofQuest

def colourOpt():
    print("The colour options are:")
    for i, colour in enumerate(Colour, start=1):
        print(f"{i}. {colour}")
    while True:
        colour = input("Which colour do you want? ")
        if not colour.isdigit() or not 1 <= int(colour) <= len(Colour):
            notOption()
            continue
        break
    return Colour(int(colour))


def shapeOpt():
    print("The shape options are:")
    for i, shape in enumerate(Shape, start=1):
        print(f"{i}. {shape}")
    while True:
        shape = input("Which shape do you want? ")
        if not shape.isdigit() or not 1 <= int(shape) <= len(Shape):
            notOption()
            continue
        break
    return Shape(int(shape))


def numberOpt():
    while True:
        number = int(input("Enter a number from 1-4 (inclusive): "))
        if not (1 <= number <= 4):
            notOption()
            continue
        break
    return number


def guessCard(player, incorrectGuess, guessedCards, correctCards):
    colour = colourOpt()
    shape = shapeOpt()
    number = numberOpt()
    card = Card(colour, shape, number)

    if player.has_card(card):
        print(f"The player has the card {card}.")
        correctCards.append(card)
        if (card not in guessedCards):
            print("Good guess!")
        else:
            print("But you already knew that.")
    else:
        print(f"The player does not have the card {card}.")
        incorrectGuess += 1

    guessedCards.append(card)
    return incorrectGuess


def finishGame(correctCards, numberofQuest, incorrectGuess):
    print(f"Congratulations!\n"
        f"It took you {numberofQuest} questions and {incorrectGuess} incorrect guesses.\n"
        f"The player's hand was: {correctCards[0]}, {correctCards[1]}, {correctCards[2]}")


def notOption():
    print("That is not an option, try again.")


if __name__ == "__main__":
    # The code here is not part of the tests, so you
    # can modify this as you like to do your own testing.
    deck = []
    for colour in Colour:
        for shape in Shape:
            for number in range(1, 5):
                deck.append(Card(colour, shape, number))
    shuffle(deck)
    play(Player(deck[0:3]))

