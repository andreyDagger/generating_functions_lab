import math
from fractions import Fraction

r = int(input())
d = int(input())
p = list(map(int, input().split()))


def calc(n): # [t^n](1-rt)^(d+1)
    return (-r)**n*math.comb(d + 1, n)


def calc_poly(poly, x):
    res = 0
    for i in range(len(poly)):
        res += x ** i * poly[i]
    return res


q = [0] * (d + 2)
for i in range(d + 2):
    q[i] = calc(i)
a = [0] * (d + 1)
P = [0] * (d + 1)
for n in range(d + 1):
    w = 1
    for i in range(n - 1, -1, -1):
        a[n] += a[i] * (-q[w])
        w += 1
    real_a = calc_poly(p, n) * r ** n
    P[n] = real_a - a[n]
    a[n] = real_a
while P[-1] == 0:
    P.pop()
print(len(P) - 1)
print(*P)
print(len(q) - 1)
print(*q)