#include <iostream>
#include <array>
#include <math.h>
#include <vector>

using namespace std;

void line(std::vector<int> &star, int size, int x0, int y0, int x1, int y1) {
    int steep = abs(y1 - y0) > abs(x1 - x0);
    int temp = 0;
    printf("%d\n", steep);
    if (steep) {
        temp = x0;
        x0 = y0;
        y0 = temp;
        temp = x1;
        x1 = y1;
        y1 = temp;
    }
    if (x0 > x1) {
        temp = x0;
        x0 = x1;
        x1 = temp;
        temp = y0;
        y0 = y1;
        y1 = temp;
    }
    int deltax = x1 - x0;
    int deltay = abs(y1 - y0);
    double error = 0.0;
    double deltaerr = (double) deltay / (double) deltax;
    int ystep = 0;
    int y = y0;
    if (y0 < y1) {
        ystep = 1;
    } else {
        ystep = -1;
    }

    printf("x0:%d, y0:%d, x1:%d, y1:%d, dx:%d, dy:%d, err:%f, derr:%f, ystep:%d\n", x0,y0,x1,y1, deltax, deltay, error, deltaerr, ystep);
    for (int x = x0; x <= x1; x++) {
        if (steep) {
            star[y * size + x] = 1;
        } else {
            star[x * size + y] = 1;
        }
        error = error + deltaerr;
        if (error >= 0.5) {
            y = y + ystep;
            error = error - 1.0;
        }
    }
}

int* build_star(int size) {
    std::vector<int> star (size*size, 0);

    printf("%d\n",star[399]);
    int points = 5;
    double r = ((double) size - 1) / 2;

    double tmp[points][2];
    for (int i = 0; i < points; ++i) {
        tmp[i][0] = floor(r * cos(M_PI * 2 / points * i) + size / 2);
        tmp[i][1] = floor(r * sin(M_PI * 2 / points * i) + size / 2);

    }

    for (int i = 0; i < points; ++i) {
        line(star, size, tmp[i][0], tmp[i][1], tmp[((i + 2) % points)][0], tmp[((i + 2) % points)][1]);
    }

    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            printf("%i ", star[i * 20 + j]);
        }
        cout << "\n";
    }
//    return star;
}

int main() {
    int *s = build_star(20);

}
