#!/usr/bin/env python3

def votes_empty(n):
    votes = {}
    for i in range(n):
        votes[i] = 0
    return votes

def read_votes(n):
    votes = []
    vote = input()
    while vote != '':
        candidates_s = vote.split(' ')
        candidates_n = []
        for c in candidates_s:
            candidates_n.append(int(c) - 1)

        votes.append(candidates_n)
        try:
            vote = input()
        except:
            vote = '' 

    wins_with = len(votes) // 2 + 1 # len(votes) % 2 
    #print(wins_with)
    counted_votes = votes_empty(n)
    eliminated = []
    winner = False
    rounds = 0
    all_votes = votes

    while not winner and rounds < n:

        counted_votes_indexes = []
        #print(votes)
        for vote in votes:
            counted_votes[vote[0]] += 1

        #print(counted_votes)

        max_votes = 0
        for c,v in counted_votes.items():
            if v > max_votes:
                max_votes = v

        if max_votes >= wins_with:
            #print(max_votes)
            winner = True
        else:
            min_votes = 1001
            for c,v in counted_votes.items():
                if v < min_votes and not c in eliminated:
                    min_votes = v

            for c,v in counted_votes.items():
                if v == min_votes and not c in eliminated:
                    eliminated.append(c)

            #print(eliminated)

        newvotes = []
        for vit in range(len(all_votes)):
            vote = all_votes[vit]
            a_valid_candidate = False
            count_to_remove = 0
            for it in range(len(vote)):
                if not vote[it] in eliminated:
                    break
                else:
                    a_valid_candidate = True
                    count_to_remove += 1
            if a_valid_candidate and vote[count_to_remove:] != []:
                newvotes.append(vote[count_to_remove:])
                all_votes[vit] = vote[count_to_remove:]

        votes = newvotes

        rounds += 1
    
    max_votes = 0
    #print(counted_votes)
    for c,v in counted_votes.items():
        if v > max_votes:
            max_votes = v 
    
    winners = []
    for c,v in counted_votes.items():
        if v == max_votes:
            winners.append(c)

    return winners 
     

def read_candidates(n):
    candidates = []
    for i in range(n):
        candidates.append(input())
    return candidates

if __name__ == "__main__":

    total_votes = int(input())
    input()

    for i in range(total_votes):
        candidate_n = int(input())
        candidates = read_candidates(candidate_n)
        winners = read_votes(candidate_n)
        for winner in winners:
            print(candidates[winner])
        if i != total_votes - 1:
            print("")

