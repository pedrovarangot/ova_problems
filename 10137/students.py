#!/usr/bin/env python3

import sys
import functools

def average(l):
    ra = functools.reduce(lambda i,j: i+j, l, 0) / len(l)
    return int(ra)

def one_round(debtors, creditors):
    if creditors == [] or debtors == []:
        return 0
    print("c",creditors)
    print("d",debtors)
    creditors[len(creditors)-1] += debtors[0]
    exchanged = abs(debtors[0])
    debtors[0] = 0

    debtors.sort()
    creditors.sort()

    return exchanged

def solve(n):

    expenses = []

    for i in range(n):
        (dls, cnt) = input().split('.')
        dls = int(dls)
        cnt = int(cnt)
        expenses.append(dls*100 + cnt)

    #print(expenses)
    avg = average(expenses)
    expenses = list(map(lambda i: i - avg, expenses))
    #print(expenses)

    debtors = []
    creditors = []
    for expense in expenses:
        if expense <= 0:
            debtors.append(expense)
        else:
            creditors.append(expense)

    total = 0
    thisround = 10
    while(thisround > 0):
        thisround = one_round(debtors, creditors)
        total += thisround

    neg_cred = False
    for credit in creditors:
        if credit < 0:
            neg_cred = True
            break

    if not neg_cred:
        for credit in creditors:
            if credit > 1:
                total += credit - 1

    rs = "${0}.{1:02}".format(total//100, total % 100)
    print(rs)

if __name__ == "__main__":
    while True:
        n_students = int(input())
        if n_students == 0: sys.exit(0)
        if n_students == 1:
            input()
            print("$0.00")
            continue

        solve(n_students)

