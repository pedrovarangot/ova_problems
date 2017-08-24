import sys
from operator import itemgetter

def display_score(score):
    totals = []
    for team in score.keys():
        solved_problems = 0
        total_penalty = 0
        for problem in score[team]:
            if score[team][problem][0] == True:
                solved_problems += 1
                total_penalty += score[team][problem][1] 

        totals.append((solved_problems, total_penalty, team))

    totals.sort(key=itemgetter(2), reverse=True)
    totals.sort(key=itemgetter(1), reverse=True)
    totals.sort(key=itemgetter(0))
    totals.reverse()

    for line in totals:
        print("{0[2]} {0[0]} {0[1]}".format(line))

if __name__ == "__main__":

    cases = int(input())
    newline = input()
    score = {}

    for line in sys.stdin.readlines():
        if line == "\n":
            display_score(score)
            cases -= 1
            if cases != 0:
                print()
            score = {}
            continue

        #print(line)
        team, problem, penalty, res = line.split()
        team = int(team)
        problem = int(problem)
        penalty = int(penalty)
        if team not in score.keys():
            score[team] = {}

        if problem not in score[team].keys() and res == 'C':
            score[team][problem] = [True, penalty]

        if problem not in score[team].keys() and res == 'I':
            score[team][problem] = [False, 20]

        if team in score.keys() and problem in score[team].keys():
            if res == 'E' and score[team][problem][0] == False:
                score[team][problem][1] += 20
            if res == 'C' and score[team][problem][0] == False:
                score[team][problem][1] += penalty 
                score[team][problem][0] = True 
        #print(score)

    display_score(score)
        


