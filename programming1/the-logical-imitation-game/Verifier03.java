public class Verifier03 implements Verifier {
    public boolean check(int[] guess, int[] answer) {
        //select 2nd digit in array
        return (answer[1] > 3 && guess[1] > 3 || 
        answer[1] < 3 && guess[1] < 3 || 
        answer[1] == 3 && guess[1] == 3);

        //Integer.compare()
    }

    public String toString() {
        return "Compares the 2nd digit to the value '3' (is it < 3, = 3 or > 3?)";
    }
}
