import java.util.List;
import java.util.Arrays;
import java.util.ArrayList;

public class Machine {
    private int[] answer;
    private List<Verifier> verifiers;
    private char[] verifierChoices;

    public Machine(int[] answer, Verifier[] verifiers) throws IncorrectDataException {
        if (answer.length != 3 || !isValidNumber(answer)) {
            throw new IncorrectDataException();
        }
        this.answer = answer;
        this.verifiers = new ArrayList<>(Arrays.asList(verifiers));
        initialiseVChoices();
    }

    public Machine(int[] answer, List<Verifier> verifiers) throws IncorrectDataException {
        if (answer.length != 3 || !isValidNumber(answer)) {
            throw new IncorrectDataException();
        }
        this.answer = answer;
        this.verifiers = new ArrayList<>(verifiers);
        initialiseVChoices();
    }

    private void initialiseVChoices() {
        this.verifierChoices = new char[verifiers.size()];
        char currentChar = 'A';
        for (int i = 0; i < verifiers.size(); i++) {
            this.verifierChoices[i] = currentChar++;
        }
    }

    @Override
    public String toString() {
        String result = "Verifiers:\n";
        for (int i = 0; i < verifiers.size(); i++) {
            result += verifierChoices[i] + ") " + verifiers.get(i).toString();
            if (i < (verifiers.size() - 1)) {
            result += "\n";
        }  
        }
        
        return result;
    } 

    public String turn(int[] guess, char[] verifierChoices) throws IncorrectDataException {
        if (guess.length != 3 || !isValidNumber(guess) || verifierChoices.length != 3) {
            throw new IncorrectDataException();
        }

        char[] sortedChoices = new char[verifierChoices.length];
        for (int i = 0; i < verifierChoices.length; i++) {
            sortedChoices[i] = Character.toUpperCase(verifierChoices[i]);
        }
        Arrays.sort(sortedChoices);

        String result = "Results for guess " + arrayToString(guess) + ":\n";
        int count = 0;
        for (char choice : sortedChoices) {
            Verifier verifier = getVerifier(choice);
            if (verifier == null) {
                throw new IncorrectDataException();
            }
            result += choice + ") " + verifier.check(guess, answer);
            if (++count < sortedChoices.length) {
                result += "\n";
            }     
        }
        return result;
    }

    public String turn(int[] guess, String verifierChoices) throws IncorrectDataException {
        String[] choices = verifierChoices.split(",");
        if (choices.length != 3) {
            throw new IncorrectDataException();
        }
        char[] charChoices = new char[3];
        for (int i = 0; i < 3; i++) {
            charChoices[i] = choices[i].trim().toUpperCase().charAt(0);
        }
        Arrays.sort(charChoices);
        return turn(guess, charChoices);
    }

    private Verifier getVerifier(char choice) throws IncorrectDataException {
        char upperCase = Character.toUpperCase(choice);
        for (int i = 0; i < verifiers.size(); i++) {
            if (verifierChoices[i] == upperCase) {
                return verifiers.get(i);
            }
        }
        throw new IncorrectDataException();
    }

    private boolean isValidNumber(int[] array) {
        for (int n : array) {
            if (n < 1 || n > 5) {
                return false;
            }
        }
        return true;
    }

    private String arrayToString(int[] array) {
        String result = "";
        for (int num : array) {
            result += num;
        }
        return result;
    }

    public boolean finalGuess(int[] guess) throws IncorrectDataException {
        if (guess.length != 3 || !isValidNumber(guess)) {
            throw new IncorrectDataException();
        }
        return Arrays.equals(answer, guess);
    }  

}

