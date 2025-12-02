import sys
from machine import *

answer = sys.argv[2]
g_filenames = sys.argv[1].split(',')

turnHist = []
guessHist = []

def showVerifiers():
    criteria_v = []
    for filename in g_filenames:
        criteria_v.append(inputVerifier(filename))
    return criteria_v


def numVer():
    num = 0
    for filename in g_filenames:
        num += 1
    return num


def getGuess():
    while True:
        guess = input("Guess? ").strip()
        if len(guess) != 3 or any(a not in '12345' for a in guess):
            print("Error! Please enter a 3 digit number each value being 1-5 inclusive")
            continue
        return guess


def getVerifier():
    while True:
        num = len(showVerifiers())
        max_letter = chr(65 + num - 1)
        v_letters = ''.join([chr(65 + i) for i in range(num)])
        verifier_inp = input(f"Input 3 comma separated verifiers: (A - {max_letter}) ").strip().upper()
        ver_select = verifier_inp.split(',')
        if len(ver_select) != 3 or any(x not in v_letters for x in ver_select):
            print(f"Error! Please enter only 3 comma separated verifiers: (A - {max_letter})")
            continue
        return verifier_inp


def checkV(criteria_v, guess, verifier_inp):
    verifier_indices = getVerifierInput(verifier_inp)
    result = []
    for x in range(len(criteria_v)):
        if x in verifier_indices:
            if checkVerifier(criteria_v[x], int(guess)):
                result.append(2)
            else:
                result.append(1)
        else:
            result.append(0)
    return result


def showHistory(guess, result, turnHist, guessHist):
    guessHist.append(guess)
    turnHist.append(result)
    return getTurnHistory(turnHist, guessHist)


def guessSolution():
    sol = input("Ready to solve? (Y/N) ").strip().lower()
    turn_text = "turn" if len(guessHist) == 1 else "turns"
    if sol == 'y':
        while True:
            g = input("What is your final guess? ").strip()
            if len(g) != 3 or any(a not in '12345' for a in g):
                print("Error! Please enter a 3 digit number each value being 1-5 inclusive")
                continue
            g = int(g)
            break

        if g == int(answer):
            print(f"You're right! The answer is {answer}. You solved it in {len(guessHist)} {turn_text}")
        else:
            print(f"Sorry! The answer is {answer}, you guessed {g} after {len(guessHist)} {turn_text}")
        return True


if __name__ == "__main__":
    final = False
    criteria_v = showVerifiers()
    while not final:
        print(listCriteria(criteria_v))
        guess = getGuess()
        verifier_inp = getVerifier()
        result = checkV(criteria_v, guess, verifier_inp)
        print(showHistory(guess, result, turnHist, guessHist))
        final = guessSolution()
        # if final:
        #     break


