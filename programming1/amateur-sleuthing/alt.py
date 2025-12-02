from cap import Shape, Colour, Card, Player
from random import shuffle  # Just here to shuffle the deck


def play(player: Player) -> None:
    while True:





# cString = questionOptions[qChoice - 1]
        # print(cString)
        # if "colour" in cString:
        #     colourOpt()
        # elif "shape" in cString:
        #     shapeOpt()
        # elif "number" in cString:
        #     numberOpt()

if qChoice == 1:
    colour = input("yeh")
    count = cap.how_many_colour(Colour(colour.upper()))
    print(f"{count} {colour}")

    player = Player(deck[0:3])
    count = player.how_many_colour(Colour.GREEN)
    print(count)



def verGuess():
    count = 0
    for c in deck[0:3]:
        if c.colour == colour or c.shape == shape or c.number == number:
            count += 1
    return count


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
