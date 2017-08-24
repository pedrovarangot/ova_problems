#!/usr/bin/env python3

import sys
import functools

def average(l):
    return functools.reduce(lambda i,j: i+j, l, 0) / len(l)

def solve(n):

    expenses = []

    for i in range(n):
        expenses.append(float(input()))

    #print(expenses)
    avg = average(expenses)

    expense_c = 0.0
    expense_n = 0.0
    for expense in expenses:
        if expense > avg:
            expense_c += expense - round(avg,3)
        else:
            expense_n += round(avg,2) - expense

    total = expense_n if expense_n < expense_c else expense_c

    rs = "${0:.2f}".format(total)
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

