import sys

if __name__ == "__main__":

    cases = int(input())

    for case in range(cases):
        days = int(input())
        parties = int(input())
        daysh = [False] * 3651
        hartals = 0

        for partie in range(parties):
            hartal = int(input())
            for day in range(1, days+1):
                if day % 7 == 6 or day % 7 == 0:
                    continue

                if day % hartal == 0 and not daysh[day]:
                    daysh[day] = True
                    hartals += 1

        print(hartals)

