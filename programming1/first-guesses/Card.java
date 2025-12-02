public class Card {
    private final int number;
    private final Colour colour;
    private final Shape shape;

    public Card(Colour colour, Shape shape, int number){
        this.number = number;
        this.colour = colour;
        this.shape = shape;
    }


    public Colour getColour() {
        return colour;
    }

    public Shape getShape() {
        return shape;
    }

    public int getNumber() {
        return number;
    }

    @Override
    public String toString() {
        return number + ", " + colour + ", " + shape;
    }

}






