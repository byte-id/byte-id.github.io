import java.util.Scanner;
import java.util.ArrayList;
import java.util.List;
public class Runner {
    public static void main(String[] args) {
        //You can use this to test and debug your code.
        int[] answer = {5,3,2};

        List<Verifier> verifiers = new ArrayList<>();
        verifiers.add(new Verifier03());
        verifiers.add(new Verifier08());
        verifiers.add(new Verifier11());
        verifiers.add(new Verifier21());

        try {
            Machine machine = new Machine(answer, verifiers);
            System.out.println("Hi! Welcome to Turing Machine!" + "\n" +
                               "Please guess a number (newline or space separated): " );
    
            Scanner sc = new Scanner(System.in);

            int[] guess = new int[3];
            for (int i = 0; i < 3; i++) {
                guess[i] = sc.nextInt();
            }
            sc.nextLine();

            // Comma separated input
            // String guessStr = sc.nextLine();
            // int[] guess;
            // if (guessStr.contains(",")) {
            //     guess = parseGuess(guessStr);
            // }

            System.out.println("Please select your verifiers (comma separated): ");
            System.out.println(machine);

            String verifierChoices = sc.nextLine();
            String result = machine.turn(guess, verifierChoices);
            System.out.println(result);

            System.out.println("Do you want to check your answer? y/n");
            char in = sc.next().charAt(0);

            if (in == 'y') {
                boolean a = machine.finalGuess(guess);
                System.out.println(a); 
            }

            sc.close();
        } catch (IncorrectDataException e) {
            System.out.println("Error in runner: " + e.getMessage());
            e.printStackTrace();
        }
    }

            // Parse comma input to int array
            
            // private static int[] parseGuess(String guessStr) {
            //     String[] guessParts = guessStr.split(",");
            //     int[] guess = new int[3];
            //     for (int i = 0; i < 3; i++) {
            //         guess[i] = Integer.parseInt(guessParts[i].trim());
            //     }
            //     return guess;
            // }
}

