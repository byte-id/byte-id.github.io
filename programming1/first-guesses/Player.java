import java.util.List;

public class Player {

    //variables to keep track of data
    private final List<Card> cards;


    public Player(List<Card> cards) {
        this.cards = cards;
    }

    public int howManyColour(Colour colour) {
        int count = 0;
        for (Card card : cards) {
            if (card.getColour() == colour) {
                count++;
            }
        }
        return count;
    }

    public int howManyShape(Shape shape) {
        int count = 0;
        for (Card card : cards) {
            if (card.getShape() == shape) {
                count++;
            }
        }
        return count;
    }

    public int howManyNumber(int number) {
        int count = 0;
        for (Card card : cards) {
            if (card.getNumber() == number) {
                count++;
            }
        }
        return count;
    }

    public int howManyColourNumber(Colour colour, int number) {
        int count = 0;
        for (Card card : cards) {
            if (card.getColour() == colour && card.getNumber() == number) {
                count++;
            }
        } return count;
    }

    public int howManyColourShape(Colour colour, Shape shape) {
        int count = 0;
        for (Card card : cards) {
            if (card.getColour() == colour && card.getShape() == shape) {
                count++;
            }
        } return count;

    }

    public int howManyShapeNumber(Shape shape, int number) {
        int count = 0;
        for (Card card : cards) {
            if (card.getShape() == shape && card.getNumber() == number) {
                count++;
            }
        } return count;
    }

    public boolean hasCard(Card card) {
        for (Card c : cards) {
            if (c.getColour() == card.getColour() &&
                c.getShape() == card.getShape() &&
                c.getNumber() == card.getNumber()) {
                    return true;
                }
        } return false;
    }
}
