class Polynom:
    def __init__(self, k, d):
        self.k = k
        self.d = d

    def integration(self):
        self.d += 1
        self.k /= self.d

    def __mul__(self, other):
        if isinstance(other, Polynom):
            return Polynom(k=other.k * self.k, d=other.d + self.d)
        else:
            return Polynom(k=other * self.k, d=self.d)

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
        tmp.append(Polynom(k, d))
    return tmp


def init_pickar():
    pool = []
    pol = [Polynom(1, 2)]
    integration(pol)
    pool.append(cop(pol))
    #
    for i in range(3):
        pol = f(pol)
        pol.append(Polynom(1, 2))
        integration(pol)
        opt(pol)
        pool.append(cop(pol))
    return pool


def calc_poly(pol, x, acc=3):
    res = 0
    for i in pol:
        res += i.k * (x ** i.d)
    return round(res, acc)


def func(x, y):
    return x * x + y * y


def euler():
    y = [0]
    for i in range(1, len(x)):
        y.append(y[i - 1] + step * func(x[i - 1], y[i - 1]))
    return y


def runge(a=0.5):
    y = [0]
    for i in range(1, len(x)):
        k1 = func(x[i - 1], y[i - 1])
        k2 = func(x[i - 1] + step / (2 * a), y[i - 1] + step / (2 * a) * k1)
        y.append(y[i - 1] + step * ((1 - a) * k1 + a * k2))
    return y


def output(a):
    if a > 10 ** 5:
        return f'{a:>12.3e}'
    else:
        return f'{a:>12.3f}'


pool = init_pickar()

print(pool)
for j in pool:
    print('=' * 20)
    for i in j:
        print(i)

step = 10 ** -6
x_min = 0
x_max = 2.1
skip = 1000
i = x_min
n = int((x_max - x_min) / step) + 1
x = [x_min + i * step for i in range(n)]

y_euler = euler()
y_runge_1 = runge(a=0.5)
y_runge_2 = runge(a=1)
print('+{text1:-^5}+{text2:-^12}+{text3:-^12}+{text4:-^12}+{text5:-^12}+{text6:-^12}+{text7:-^12}+{text8:-^12}+'
      .format(text1='-', text2='-', text3='-', text4='-', text5='-', text6='-', text7='-', text8='-'))
print('|{text1:^5}|{text2:<12}|{text3:<12}|{text4:<12}|{text5:<12}|{text6:<12}|{text7:<12}|{text8:<12}|'
      .format(text1='X', text2='Пикар 1', text3='Пикар 2', text4='Пикар 3',
              text5='Пикар 4', text6='Эйлер', text7='Рунге a=0.5', text8='Рунге a=1'))
print('+{text1:-^5}+{text2:-^12}+{text3:-^12}+{text4:-^12}+{text5:-^12}+{text6:-^12}+{text7:-^12}+{text8:-^12}+'
      .format(text1='-', text2='-', text3='-', text4='-', text5='-', text6='-', text7='-', text8='-'))
for i in range(n):
    if i % skip:
        continue
    tmp = f'|{round(i * step, 3):<5}|'
    for pol in pool:
        tmp += f'{output(calc_poly(pol, i * step))}|'
    tmp += f'{output(y_euler[int(i)])}|'
    tmp += f'{output(y_runge_1[int(i)])}|'
    tmp += f'{output(y_runge_2[int(i)])}|'
    print(tmp)
print('+{text1:-^5}+{text2:-^12}+{text3:-^12}+{text4:-^12}+{text5:-^12}+{text6:-^12}+{text7:-^12}+{text8:-^12}+'
      .format(text1='-', text2='-', text3='-', text4='-', text5='-', text6='-', text7='-', text8='-'))

