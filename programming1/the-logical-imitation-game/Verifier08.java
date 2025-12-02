public class Verifier08 implements Verifier {
    public boolean check(int[] guess, int[] answer) {
        //Iterate throuh answer array, if contains 1, continue through
        int countAnswer = 0;
        int countGuess = 0;
        for (int n : answer) {
            if (n == 1) {
                countAnswer++;
            }
        }

        for (int n : guess) {
            if (n == 1) {
                countGuess++;
            }
        }
        return countAnswer == countGuess; 

    }


    public String toString() {
        return "Number of 1s in the code";
    }
}
