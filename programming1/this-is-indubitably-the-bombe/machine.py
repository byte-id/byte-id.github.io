def inputVerifier(filename: str):
    criterion = ""
    verifier =[]
    with open(filename) as f:
        fileLines = f.read().split("\n")
        criterion = fileLines[0]
        verifier = [[True if int(y) == 1 else False for y in x.split(",")] for x in fileLines[1:-1]]

    return criterion, verifier


def printVerifier(verifier: tuple[str, list[list[bool]]]):
    verifierStr = [["X" if y else "O" for y in x] for x in verifier[1]]
    verifierStr = "\n".join([" ".join(x) for x in verifierStr])
    return verifierStr

def guessToIndex(guess: int) -> dict[int, tuple[int, int]]:
    allPositions = {
        111: (1,4), 112: (8,9), 113: (6,1), 114: (9,9), 115: (5,4), 
        121: (4,11), 122: (10,6), 123: (6,6), 124: (1,5), 125: (1,2), 
        131: (3,4), 132: (0,9), 133: (9,4), 134: (6,7), 135: (6,9),
        141: (3,1), 142: (10,2), 143: (3,8), 144: (6,10), 145: (10,4),
        151: (3,6),  152: (2,11), 153: (11,6), 154: (4,6),  155: (3,9), 
        211: (4,10), 212: (7,4), 213: (5,3), 214: (4,8), 215: (4,7), 
        221: (5,0), 222: (1,9), 223: (3,0), 224: (7,10), 225: (10,9),
        231: (3,2), 232: (8,2), 233: (2,6), 234: (7,5), 235: (5,1), 
        241: (10,7), 242: (7,7), 243: (8,10),244: (4,5), 245: (3,10), 
        251: (9,5), 252: (2,4), 253: (9,7), 254: (7,0), 255: (1,11),
        311: (11,7), 312: (9,6),  313: (5,10), 314: (6,8),  315: (7,6), 
        321: (9,1), 322: (5,6), 323: (8,1), 324: (7,3), 325: (8,8), 
        331: (11,3), 332: (11,8), 333: (5,11), 334: (0,3),  335: (5,5), 
        341: (3,7), 342: (4,1), 343: (1,10), 344: (3,11), 345: (3,3), 
        351: (8,3),  352: (8,11), 353: (2,3),  354: (1,7),  355: (1,8), 
        411: (7,11), 412: (2,1), 413: (0,10),414: (2,2), 415: (3,5), 
        421: (6,3), 422: (4,2), 423: (9,3), 424: (6,0), 425: (8,6), 
        431: (2,10), 432: (10,8),433: (0,4), 434: (2,9),  435: (1,6),
        441: (6,2), 442: (0,6), 443: (8,0), 444: (8,7), 445: (10,5), 
        451: (5,8),  452: (10,3), 453: (4,3),  454: (4,0), 455: (6,11), 
        511: (0,8), 512: (2,7), 513: (2,8), 514: (9,2), 515: (7,1),
        521: (4,4), 522: (0,5), 523: (7,8), 524: (4,9), 525: (1,3),
        531: (11,4), 532: (7,2), 533: (9,10),534: (5,2), 535: (5,7), 
        541: (8,5), 542: (2,5),  543: (6,5),  544: (0,7),  545: (8,4), 
        551: (7,9),  552: (6,4),  553: (9,8),  554: (11,5), 555: (5,9), 
    }
    return allPositions[guess]  # (row, column)


# Given an int, return true/false
def checkVerifier(verifier: tuple[str, list[list[bool]]], guess: int) -> bool:
    r, c = guessToIndex(guess)
    _, v = verifier
    return v[r][c]


# Lists the Criteria A) str\nB) str ect
def listCriteria(criteria: list[tuple[str, list[list[bool]]]]) -> str:
    criteriaString = f"You have {len(criteria)} criteria"
    i = 'A'
    for c, _ in criteria:
        criteriaString += "\n    " + i + ") " + str(c)
        i = chr(ord(i) + 1)

    return criteriaString


# reads a string of 3 csv chars and converts them to list position
def getVerifierInput(verifierSelections) -> list:
    verifierSelections = verifierSelections.split(",")
    verifierInts = [(ord(x.capitalize())-64-1) for x in verifierSelections]
    return sorted(verifierInts)


def getTurnHistory(turnHist, guessHist) -> str:
    verifierNum = len(turnHist[0])
    turnHistStr = "xyz  "
    turnHistStr += '   '.join([f"{chr(x+64+1)}" for x in range(verifierNum)])
    turnHistStr += "\n"
    turnHistStr += "--- "*(verifierNum) + "---"
    for i in range(len(guessHist)):
        turnHistStr += "\n"
        turnHistStr += f"{guessHist[i]}  "
        status = ['Y' if x==2 else 'N' if x==1 else " "  for x in turnHist[i]]
        turnHistStr += "   ".join(status)
    return turnHistStr

