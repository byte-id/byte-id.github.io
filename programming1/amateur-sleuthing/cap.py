from enum import Enum, auto
from typing import Callable


class Colour(Enum):
    RED = auto()
    BLUE = auto()
    GREEN = auto()
    YELLOW = auto()

    def __str__(self) -> str:
        return self.name


class Shape(Enum):
    HEXAGON = auto()
    CIRCLE = auto()
    DIAMOND = auto()
    RHOMBUS = auto()

    def __str__(self) -> str:
        return self.name


class Card:

    def __init__(self, colour: Colour, shape: Shape, number: int):
        self.colour = colour
        self.shape = shape
        self.number = number

    def get_colour(self) -> Colour:
        return self.colour

    def get_shape(self) -> Shape:
        return self.shape

    def get_number(self) -> int:
        return self.number

    def __repr__(self) -> str:
        return "(" + str(self.number) + ", " + str(self.colour) + \
                ", " + str(self.shape) + ")"

    def __eq__(self, o) -> bool:
        if not isinstance(o, Card):
            return False
        return self.colour is o.get_colour() and \
            self.shape is o.get_shape() and \
            self.number == o.get_number()


class Player:

    def __init__(self, hand: list[Card]):
        self.hand = hand

    def __match(self, test: Callable[[Card], bool]) -> int:
        return len([card for card in self.hand if test(card)])

    def how_many_colour(self, colour: Colour) -> int:
        return self.__match(lambda x: x.get_colour() is colour)

    def how_many_shape(self, shape: Shape) -> int:
        return self.__match(lambda x: x.get_shape() is shape)

    def how_many_number(self, number: int) -> int:
        return self.__match(lambda x: x.get_number() == number)

    def how_many_colour_number(self, colour: Colour, number: int) -> int:
        return self.__match(lambda x: x.get_colour() is colour and
                            x.get_number() == number)

    def how_many_shape_number(self, shape: Shape, number: int) -> int:
        return self.__match(lambda x: x.get_shape() is shape and
                            x.get_number() == number)

    def how_many_colour_shape(self, colour: Colour, shape: Shape) -> int:
        return self.__match(lambda x: x.get_colour() is colour and
                            x.get_shape() is shape)

    def has_card(self, guess: Card) -> bool:
        return guess in self.hand
