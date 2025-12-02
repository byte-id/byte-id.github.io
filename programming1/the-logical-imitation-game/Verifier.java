public interface Verifier {
    public boolean check(int[] guess, int[] answer);

    @Override
    String toString();
}
