# Probably should put a few functions hereabouts
def inputCard(filename: str) -> tuple[str, list[list[bool]]]:
    with open(filename, 'r') as f:
        lines = f.readlines()
        criterion = lines[0].strip()
        verifier = []
        for line in lines[1:]:
            #row[] -- row.append(bool(int(x))) -- verifier.append(row)
            row = [bool(int(x)) for x in line.strip().split(',')]
            verifier.append(row)
    return criterion, verifier


def getVerifierInput(verifierInput: str) -> list[int]:
    characters = verifierInput.lower().split(',')
    #ASCII/unicode
    #indices.sort()
    indices = [ord(char)-ord('a') for char in characters]
    return sorted(indices)


def guessToIndex(guess: int) -> tuple[int, int]:
    with open("verifierAddress.in", 'r') as f_in:
        for line in f_in:
            parts = line.strip().split(',')
            if parts[0] == str(guess):
                return int(parts[1]), int(parts[2])
    # raise Error('Guess value not found')


def checkVerifier(gameCard: tuple[str, list[list[bool]]], guess: int) -> bool:
    _, verifier = gameCard
    x, y = guessToIndex(guess)
    return verifier[x][y]


def listCriteria (gameCards: list[tuple[str, list[list[bool]]]]) -> str:
    criteria = [card[0] for card in gameCards]
    result = [f"You have {len(criteria)} criteria"]
    x = 0
    for criterion in criteria:
        result.append(f"    {chr(65+x)}) {criterion}")
        x += 1
    return '\n'.join(result)


def showTurnHistory(pastGuesses: list[int], turnHistory: list[list[int]]) -> str:
    # top = "xyz"
    # for i in range(len(turnHistory[0]))
    #     result = [str(guess)]
    # for res in history:
    #     if  res == 2:
    #         result.append("0")
    #     elif res == 1:
    #         result.append("X")
    #     else
    #         result.append(" ")
    # row = " ".join(result)
    # rows.append(row)
    top = "xyz  " + "   ".join(chr(65+i) for i in range(len(turnHistory[0])))
    sep = "---" + " ---"*len(turnHistory[0])
    rows = []
    for i in range(len(pastGuesses)):
        guess = pastGuesses[i]
        history = turnHistory[i]
        guess_str = f"{guess}"
        result_str = [("O" if res == 2 else "X" if res == 1 else " ") for res in history]
        row = f"{guess_str}  {'   '.join(result_str)}"
        rows.append(row)
    return f"{top}\n{sep}\n" + "\n".join(rows)


def showVerifier(gameCard: tuple[list[list[bool]]]) -> str:
    _, verifier = gameCard
    return '\n'.join(' '.join('X' if cell else 'O' for cell in row) for row in verifier)
    # criterion, verifier = gameCard
    # form_rows = []
    # for row in verifier:
    #     form_cell = []
    #     for cell in row:
    #         if cell:
    #             form_cell.append('0')
    #         else:
    #             form_cell.append('X')
    #     form_row = ' '.join(form_cell)
    #     form_row.append(form_row)
    # return '\n'.join(form_row)


if __name__ == "__main__":
    # This is not part of the tests, so you can use this
    # to help check your code is working.
    a = getVerifierInput('A')
    b = guessToIndex(111)
    pastGuesses = [124, 214]
    turnHistory = [[1, 2, 1, 0, 0], [1, 0, 1, 0, 1]]
    c = showTurnHistory(pastGuesses, turnHistory)
    print(a, b)
    print(c)
    # verifierInput = input()
    pass
