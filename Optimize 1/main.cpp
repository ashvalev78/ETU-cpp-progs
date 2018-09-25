#include <iostream>
#include <cmath>

double f(double x) {
    return (x * x + 25 * x);
};

class Svenn1 {
private:
    double x1, xn, h, k;

public:
    double a = 0, b = 0;

    Svenn1(double startPoint, double step, int maxAmountOfSteps) {
        x1 = startPoint;
        xn = startPoint;
        h = step;
        k = maxAmountOfSteps;
    };



    void getInterval() {
        double lastX = x1;
        int steps = 1;
        a = x1;
        b = xn;
        if (f(x1 + h) < f(x1)) {
            a = x1 + h;
        } else if (f(x1 - h) < f(x1)){
            h = -h;
            a = x1 + h;
        } else {
            a = x1 - h;
            b = x1 + h;
            std::cout << "Interval is: [" << a << ", " << b << "]" << std::endl;
            return;
        }
        while (f(lastX) > f(a) && steps <= k) {
            steps++;
            h *= 2;
            lastX = a;
            a = a + h;
            b = a + h + 2*h;
        }

        if (steps > k) {
            std::cout << "Too many iterations" << std::endl;
            return;
        }

        if (lastX < b) {
            a = lastX;
        } else {
            a = b;
            b = lastX;
        }

        std::cout << "Interval is: [" << a << ", " << b << "]" << std::endl;
    };
};

class Diht {
private:
    double a, b, center, l, r, k, h, e;

public:
    double min = 0;

    Diht (double start, double end, int maxAmountOfSteps, double step, double epsilon) {
        a = start;
        b = end;
        center = (a + b) / 2;
        e = epsilon;
        k = maxAmountOfSteps;
        h = step;
        l = center - h;
        r = center + h;
    };

    void getMinimum() {
        int steps = 0;
        while (b - a > e && steps <= k) {
            steps++;
            center = (a + b) / 2;
            l = center - h;
            r = center + h;
            if (f(l) < f(r)) {
                b = r;
            } else if (f(l) > f(r)) {
                a = l;
            } else {
                min = center;
                std::cout << "Minimum is " << min << std::endl;
                return;
            }
        }
        if (steps > k) {
            std::cout << "Too many iterations" << std::endl;
            return;
        }
        min = (a + b) / 2;
        std::cout << "Minimum is " << min << std::endl;
    }
};

class Powell {
private:
    double a, b, c, k, e, d, fe;

    double form1() {
        return  0.5 *
                (f(a) * (b * b - c * c) + f(b) * (c * c - a * a) + f(c) * (a * a - b * b))
                        /
                (f(a) * (b - c) + f(b) * (c - a) + f(c) * (a - b));
    }

    double form2() {
        return  (a + b) / 2 + 0.5 *
                ((f(a) - f(b)) * (b - c) * (c - a))
                        /
                (f(a) * (b - c) + f(b) * (c - a) + f(c) * (a - b));
    }

    void takeClosest() {
        if (f(b) < f(d)) {
            if (d < b) {
                a = d;
            } else {
                c = d;
            }
        } else {
            if (b < d) {
                a = b;
            } else {
                c = b;
            }
        }
        b = (a + c) / 2;
    }

public:
    double minimum = 0;

    Powell(double start, double end,
           double epsilon, double maxAmountOfSteps, double fEpsilon) {

        a = start;
        c = end;
        b = (a + c) / 2;
        e = epsilon;
        k = maxAmountOfSteps;
        fe = fEpsilon;
    }

    void getMin() {
        int steps = 0;
        d = form1();
        double absDiff = d - b;
        if (absDiff < 0)
            absDiff = -absDiff;
        double absB = b;
        if (b < 0)
            absB = -b;
        double fABS = f(d) - f(b);
        if (fABS < 0) {
            fABS = -fABS;
        }
        double fbABS = f(b);
        if (f(b) < 0) {
            fbABS = - fbABS;
        }
        if (absDiff/absB <= e && fABS/fbABS <= fe) {
            minimum = (b + d) / 2;
            return;
        }

        steps++;

        while (!(absDiff/absB <= e && fABS/fbABS <= fe) && steps <= k) {
            takeClosest();

            d = form2();
            absDiff = d - b;
            if (absDiff < 0)
                absDiff = -absDiff;
            absB = b;
            if (b < 0)
                absB = -b;
            fABS = f(d) - f(b);
            if (fABS < 0) {
                fABS = -fABS;
            }
            fbABS = f(b);
            if (f(b) < 0) {
                fbABS = - fbABS;
            }
            steps++;
        }
        if (steps > k) {
            std::cout << "Too many iterations" << std::endl;
            return;
        }
        minimum = (b + d) / 2;

        std::cout << "Minimum is: " << minimum << std::endl;
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    Svenn1 A = Svenn1(0, 0.0001, 1000000);
    A.getInterval();
    Diht B = Diht(A.a, A.b, 1000000, 0.0001, 0.001);
    B.getMinimum();
    Powell C = Powell(A.a, A.b, 0.001, 100000, 0.001);
    C.getMin();
    return 0;
}