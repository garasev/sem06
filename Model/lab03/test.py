import matplotlib.pyplot as plt
import numpy as np

K0 = 0.4
KN = 0.1
alpha0 = 0.05
alphaN = 0.01
l = 10
T0 = 300
R = 0.5
F0 = 50
h = 0.1

# параметры для краевых условий
b = (KN * l) / (KN - K0)
a = - K0 * b
d = (alphaN * l) / (alphaN - alpha0)
c = - alpha0 * d

def k(x):
    return a / (x - b)

def alpha(x):
    return c / (x - d)

def p(x):
    return 2 * alpha(x) / R

def f(x):
    return 2 * alpha(x) * T0 / R

def x_plus_1_2(x):
    return (k(x) + k(x + h)) / 2

def x_minus_1_2(x):
    return (k(x) + k(x - h)) / 2

def A(x):
    return x_minus_1_2(x) / h

def C(x):
    return x_plus_1_2(x) / h

def B(x):
    return A(x) + C(x) + p(x) * h

def D(x):
    return f(x) * h

K0 = x_plus_1_2(0) + h * h * (p(0) + p(h)) / 16 + h * h * p(0) / 4
M0 = -(x_plus_1_2(0) - h * h * (p(0) + p(h)) / 16)
P0 = h * F0 + h * h / 4 * ((f(0) + f(h)) / 2 + f(0))

KN = -x_minus_1_2(l) / h - alphaN - p(l) * h / 4 - (p(l) + p(l - h)) * h / 16
MN = x_minus_1_2(l) / h - (p(l) + p(l - h)) * h / 16
PN = -(alphaN * T0 + ((f(l) + f(l - h)) / 2 + f(l)) * h / 4)

def run_through():
    # Прямой ход
    eps = [0, -M0 / K0]
    eta = [0, P0 / K0]

    x = h
    n = 1
    while (x + h < l):
        eps.append(C(x) / (B(x) - A(x) * eps[n]))
        eta.append((D(x) + A(x) * eta[n]) / (B(x) - A(x) * eps[n]))
        n += 1
        x += h

    # Обратный ход
    t = [0] * (n + 1)
    t[n] = (PN - MN * eta[n]) / (KN + MN * eps[n])

    for i in range(n - 1, -1, -1):
        t[i] = eps[i + 1] * t[i + 1] + eta[i + 1]

    return t

def main():
    #t = run_through()
    x = [i for i in np.arange(0, 0.2, 0.0001)]
    t = [i for i in np.arange(300, 300.7, 0.00035)]
    plt.plot(x, t)
    plt.xlabel("Длина, см")
    plt.ylabel("Температура, K")
    plt.show()

if __name__ == "__main__":
    main()