def checkOddEven(x: int) -> str:
    num = x % 2
    if num == 0:
        return "Even"
    else:
        return "Odd"
