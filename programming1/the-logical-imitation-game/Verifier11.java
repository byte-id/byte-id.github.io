public class Verifier11 implements Verifier {
    public boolean check(int[] guess, int[] answer) {
        //Checks 1st digit compared to 2nd
        return (answer[0] > answer[1] && guess[0] > guess[1] || 
        answer[0] < answer [1] && guess[0] < guess[1] || 
        answer[0] == answer[1] && guess[0] == guess[1]);
    }

    public String toString() {
        return "Checks the 1st digit compared to the 2nd (ie x<y, x=y or x>y)";
    }
}
