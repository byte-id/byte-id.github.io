public class Verifier21 implements Verifier {
    public boolean check(int[] guess, int[] answer) {
        //If a number is present exactly twice

        int[] gCounts = countTimes(guess);
        int[] aCounts = countTimes(answer);

        return hasNumberTwice(gCounts) == hasNumberTwice(aCounts);
    }
    public String toString() {
        return "If there is a number present exactly twice";
    }

    private int[] countTimes(int[] nums) {
        int[] counts = new int[6];
        for (int n : nums) {
            counts[n]++;
        }
        return counts;
    }

    private boolean hasNumberTwice(int[] counts) {
        boolean twiceFound = false;
        for (int count : counts) {
            if (count == 2) {
                twiceFound = true;
            }
        }
    return twiceFound;
    }
}
