import math
from fractions import Fraction

r, k = map(int, input().split())
p = list(map(int, input().split()))


def calc(n): # [t^n](1-rt)^(k+1)
    return (-r)**n*math.comb(k + 1, n)


div = []
for i in range(k + 1):
    res = p[i]
    for j in range(i):
        res -= div[j] * calc(i - j)
    div.append(res)
a = [[Fraction(0) for i in range(k + 1)] for j in range(k + 1)]
b = [Fraction(0) for i in range(k + 1)]
for i in range(k + 1):
    b[i] = Fraction(div[i])
    for j in range(k + 1):
        a[i][j] = Fraction(i ** j * r ** i)

who = [-1] * (k + 1)
for i in range(k + 1):
    for j in range(k + 1):
        if a[i][j] != 0:
            who[i] = j
            break
    assert who[i] != -1
    for j in range(i + 1, k + 1):
        mul = a[j][who[i]] / a[i][who[i]]
        for t in range(k + 1):
            a[j][t] -= a[i][t] * mul
        b[j] -= b[i] * mul
for i in range(k, -1, -1):
    for j in range(i):
        b[j] -= b[i] * a[j][who[i]] / a[i][who[i]]
        a[j][who[i]] = Fraction(0)
ans = [Fraction(0)] * (k + 1)
for i in range(k + 1):
    ans[who[i]] = b[i] / a[i][who[i]]
for i in range(k + 1):
    print(str(ans[i].numerator) + '/' + str(ans[i].denominator), end=' ')