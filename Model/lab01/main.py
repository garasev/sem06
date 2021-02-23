class Chlen:
    def __init__(self, k, d):
        self.k = k
        self.d = d

    def integration(self):
        self.d += 1
        self.k /= self.d

    def __mul__(self, other):
        if isinstance(other, Chlen):
            return Chlen(k=other.k * self.k, d=other.d + self.d)
        else:
            return Chlen(k=other * self.k, d=self.d)

    def __str__(self):
        return f'k = {self.k}, d = {self.d} \n'

    def cop(self):
        return self.k, self.d


def opt(poly):
    poly.sort(key=lambda x: x.d, reverse=True)
    i = 0
    while i < len(poly) - 1:
        if poly[i].d == poly[i + 1].d:
            poly[i].k += poly[i + 1].k
            del poly[i + 1]
            i -= 1
        i += 1


def integration(poly):
    for i in poly:
        i.integration()


def f(poly):
    tmp = []
    for i in range(len(poly) - 1):
        for j in range(i + 1, len(poly)):
            tmp.append(poly[i] * poly[j] * 2)
    for i in range(len(poly)):
        poly[i].d *= 2
        poly[i].k = poly[i].k ** 2
        tmp.append(poly[i])
    return tmp


def cop(poly):
    tmp = []
    for i in poly:
        k, d = i.cop()
        tmp.append(Chlen(k, d))
    return tmp


def calc_poly(pol, x, acc=3):
    res = 0
    for i in pol:
        res += i.k * (x ** i.d)
    return round(res, acc)


pool = []
pol = [Chlen(1, 2)]
integration(pol)
pool.append(cop(pol))

for i in range(3):
    pol = f(pol)
    pol.append(Chlen(1, 2))
    integration(pol)
    opt(pol)
    pool.append(cop(pol))

print(pool)
for j in pool:
    print('=' * 20)
    for i in j:
        print(i)

step = 0.01
i = 0
width = 20
while i < 10:
    print(f'{round(i, 2):<5} |{calc_poly(pool[0], i):>10}|{calc_poly(pool[1], i):>15}|{calc_poly(pool[2], i):>20}|{calc_poly(pool[3], i):>25}|')
    i += step