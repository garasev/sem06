import math
import matplotlib.pyplot as plt


def RungeKutta4(I, U, h):
    k1 = f1(I, U)
    q1 = f2(I)

    k2 = f1(I + h * k1 / 2, U + h * q1 / 2)
    q2 = f2(I + h * k1 / 2)

    k3 = f1(I + h * k2 / 2, U + h * q2 / 2)
    q3 = f2(I + h * k2 / 2)

    k4 = f1(I + h * k3, U + h * q3)
    q4 = f2(I + h * k3)

    I_res = I + h * (k1 + 2 * k2 + 2 * k3 + k4) / 6
    U_res = U + h * (q1 + 2 * q2 + 2 * q3 + q4) / 6
    return I_res, U_res


def f2(I):
    return -1 * I / Ck


def f1(I, U):
    a = (U - (Rk + calcR(I)) * I) / Lk
    # a = (U - 0.25 * I) / Lk
    return a


def calcR(I):
    r = l / (2 * math.pi * R * R * integral(I))
    R_list.append(r)
    RI_list.append(I * r)
    return r


def integral(I):
    return trapezoid(T, 0.01, 1, 10 ** -2, I)


def tab(name):
    with open(name, 'r') as file:
        tab1 = []
        for line in file:
            tmp = []
            line = line.split()
            for item in line:
                tmp.append(float(item))
            tab1.append(tmp)
    return tab1


def rebuild(tab):
    n = len(tab[0])
    res = []
    for i in range(n):
        res.append([])
    for line in tab:
        for i in range(n):
            res[i].append(line[i])
    return res


R = 0.35
l = 12
Lk = 187 * 10**-6
Ck = 268 * 10**-6
Rk = 0.25
Uco = 1400
Io1 = 3
Tw = 2000


def linear(x, y):
    def p(value):
        i = 1
        while value > x[i]:
            i += 1
        return y[i - 1] + (y[i] - y[i - 1]) / (x[i] - x[i - 1]) * (value - x[i - 1])
    return p


def newton(x, y):
    def delta(p, i):
        if p == 1:
            return y[i] - y[i - 1]
        return delta(p - 1, i) - delta(p - 1, i - 1)

    def cj(j):
        if j == 0:
            return y[0]
        return delta(j, j) / (math.factorial(j) * math.pow(dx, j))

    dx = x[1] - x[0]
    c = []

    for i in range(len(x)):
        c.append(cj(i))

    def p(value):
        tmp = 1
        sum = 0
        for i in range(len(x)):
            sum += c[i] * tmp
            tmp *= (value - x[i])
        return sum

    return p


def trapezoid(f, a, b, h, i):
    p = round((b - a) // h)
    s = 0
    for _ in range(p):
        s += (f(a, i) + f(a + h, i)) / 2 * h
        a += h
    return s


def T(z, i):
    return temp(f_t(i) + (Tw - f_t(i)) * z**f_m(f_t(i)))


if __name__ == '__main__':
    tab1 = rebuild(tab('table1.txt'))
    tab2 = rebuild(tab('table2.txt'))

    temp = newton(tab2[0], tab2[1])
    f_t = linear(tab1[0], tab1[1])
    f_m = linear(tab1[1], tab1[2])

    tmax = 800 * 10**-6
    t0 = 0
    dt = 10**-6
    I = Io1
    U = Uco
    I_list = [Io1]
    U_list = [Uco]
    T_list = [t0]
    R_list = []
    RI_list = []
    while t0 < tmax:
        I_1, U_1 = RungeKutta4(I, U, dt)
        I = I_1
        U = U_1
        t0 += dt
        I_list.append(I)
        U_list.append(U)
        T_list.append(t0)
    print(len(I_list), len(T_list), len(T_list))
    plt.plot(T_list, I_list)
    I_mid = 0.35 * max(I_list)
    t_start = 0
    t_end = 0
    i = 0
    while I_list[i] < I_mid:
        i += 1
    t_start = T_list[i]
    while I_list[i] > I_mid:
        i += 1
    t_end = T_list[i]
    print('Max:', max(I_list))
    print('0.35 I:', 0.35 * max(I_list))
    print('start:', t_start * 10**6)
    print('end:', t_end * 10**6)
    print('dt', (t_end - t_start) * 10**6)
    plt.plot(T_list, [0.35 * max(I_list)] * len(T_list))
    plt.show()
    # plt.plot(T_list, U_list)
    # plt.show()
    # if len(R_list) > 0:
    #     plt.plot(T_list[:-7], R_list[24::4])
    #     plt.show()
    #     plt.plot(T_list[:-7], RI_list[24::4])
    #     plt.show()
