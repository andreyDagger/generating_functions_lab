m = 7
ONE = [1, 0, 0, 0, 0, 0, 0]


def mul(a, b):
    res = [0] * m
    for i in range(m):
        for j in range(i + 1):
            res[i] += a[j] * b[i - j]
    return res


def divide(a, b):
    res = [0] * m
    for i in range(m):
        res[i] = a[i]
        for j in range(i):
            res[i] -= res[j] * b[i - j]
        assert b[0] == 1
        res[i] //= b[0]
    return res


def sub(a, b):
    res = [0] * m
    for i in range(m):
        res[i] = a[i] - b[i]
    return res


def binpow(a, p):
    if p == 0:
        return ONE
    if p % 2 != 0:
        return mul(a, binpow(a, p - 1))
    t = binpow(a, p // 2)
    return mul(t, t)


def parse(s, i):
    if s[i] == 'B':
        res = [0] * m
        res[1] = 1
        return [res, i + 1]
    elif s[i] == 'L':
        assert s[i + 1] == '('
        res, j = parse(s, i + 2)
        assert j == len(s) or s[j] == ')'

        w = [0] * m
        w[0] = 1
        for ii in range(1, m):
            w[ii] = res[ii]
            for jj in range(1, ii):
                w[ii] += res[jj] * w[ii - jj]

        return w, j + 1
    elif s[i] == 'S':
        assert s[i + 1] == '('
        p, j = parse(s, i + 2)
        assert j == len(s) or s[j] == ')'
        res = ONE
        for w in range(1, m):
            lel = [0] * m
            lel[w] = 1
            cur = divide(ONE, sub(ONE, lel))
            res = mul(res, binpow(cur, p[w]))
        return res, j + 1
    else:
        assert s[i] == 'P'
        assert s[i + 1] == '('
        p1, j1 = parse(s, i + 2)
        assert s[j1] == ','
        p2, j2 = parse(s, j1 + 1)
        assert j2 == len(s) or s[j2] == ')'
        return mul(p1, p2), j2 + 1


s = input()
res, _ = parse(s, 0)
for x in res:
    print(x, end=' ')