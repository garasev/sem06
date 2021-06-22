import matplotlib.pyplot as plt

table1 = {
    'T': [300, 500, 800, 1100, 2000, 2400],
    'lambda': [1.36 * 10**-2, 1.63 * 10**-2, 1.81 * 10**-2, 1.92 * 10**-2, 2.5 * 10**-2, 2.74 * 10**-2],
}

table2 = {
    'T': [293, 1278, 1528, 1677, 2000, 2400],
    'k': [2 * 10**-2, 5 * 10**-2, 7.8 * 10**-2, 1 * 10**-1, 1.3 * 10**-1, 2 * 10**-1],
}

np = 1.4
l = 0.2
T0 = 300
T_CONST = 2400
siqma = 5.668 * 10**-12
F0 = 100
alpha = 0.05
h = 10**-4
E = 10**-6


def linear(x, y):
    def p(value):
        i = 1
        while value > x[i] and i < len(x) - 1:
            i += 1
        return y[i - 1] + (y[i] - y[i - 1]) / (x[i] - x[i - 1]) * (value - x[i - 1])
    return p


l_t = linear(table1['T'], table1['lambda'])
k_t = linear(table2['T'], table2['k'])


def T(x):
    # if x >= l / 2:
    #     return T0
    # else:
    #     return T_CONST
    # return T_CONST
    return T_CONST - (T_CONST - T0) * x / l


def lambda_x(n):
    return l_t(t[n])


# x + 1/2
def x2(n):
    return (lambda_x(n) + lambda_x(n + 1)) / 2


# x - 1/2
def _x2(n):
    return (lambda_x(n) + lambda_x(n - 1)) / 2


def p2(n):
    return (p(n) + p(n + 1)) / 2


def _p2(n):
    return (p(n) + p(n - 1)) / 2


def p(n):
    return 4 * np * np * siqma * k_t(t[n]) * t[n]**3


def f2(n):
    return (f(n) + f(n + 1)) / 2


def _f2(n):
    return (f(n) + f(n - 1)) / 2


def f(n):
    return 4 * np * np * siqma * k_t(t[n]) * T0**4


def a(n):
    return (l_t(t[n]) + l_t(t[n - 1])) / 2 / h


def b(n):
    return a(n) + c(n) + 4 * np * np * siqma * k_t(t[n]) * t[n]**3 * h


def c(n):
    return (l_t(t[n]) + l_t(t[n + 1])) / 2 / h


def d(n):
    return 4 * np * np * siqma * k_t(t[n]) * T0**4 * h


steps = int(l / h)
t = [2400 for i in range(steps + 1)]

# K0 = x2(0) + h**2 / 8 * p2(0) + h**2 / 4 * p(0)
# M0 = h**2 / 8 * p2(0) - x2(0)
# P0 = h * F0 + h**2 / 4 * (f2(0) + f(0))
#
# KN = - _x2(steps) / h - alpha - h * p(steps) / 4 - h * _p2(steps) / 8
# MN = _x2(steps) / h - h * _p2(steps) / 8
# PN = - (alpha * T0 + (_f2(steps) + f(steps)) / 4 * h)


print(t)
cnt = 0
while True:
    cnt += 1
    if cnt == 100:
        break
    # if max(ys) <= eps1 and max(fs) <= eps2:
    #     break

    K0 = x2(0) + h ** 2 / 8 * p2(0) + h ** 2 / 4 * p(0)
    M0 = h ** 2 / 8 * p2(0) - x2(0)
    P0 = h * F0 + h ** 2 / 4 * (f2(0) + f(0))

    KN = - _x2(steps) / h - alpha - h * p(steps) / 4 - h * _p2(steps) / 8
    MN = _x2(steps) / h - h * _p2(steps) / 8
    PN = - (alpha * T0 + (_f2(steps) + f(steps)) / 4 * h)

    eps = [0, -M0 / K0]
    eta = [0, P0 / K0]

    x = h
    n = 0
    while x + h < l:
        eps.append(c(n) / (b(n) - a(n) * eps[n]))
        eta.append((d(n) + a(n) * eta[n]) / (b(n) - a(n) * eps[n]))
        n += 1
        x += h

    t[n] = (PN - MN * eta[n]) / (KN + MN * eps[n])

    for k in range(n - 1, -1, -1):
        t[k] = eps[k + 1] * t[k + 1] + eta[k + 1]
    prev = t

plt.plot([i * h for i in range(len(t))][:-1], t[:-1])
plt.show()


