#include <stdio.h>

void fahrCelsTable() {
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20; /* step size*/

    fahr = lower;
    printf("| F |    C  |\n");
    while(fahr <= upper) {
        celsius = (5.0 / 9.0) * (fahr - 32.0);
        printf("|%3.0f| %6.1f|\n", fahr, celsius);
        fahr += step;
    }

    lower = -30;
    upper = 150;
    step = 10;
    celsius = lower;
    printf("\n");
    printf("| C |    F  |\n");
    while(celsius <= upper) {
        fahr = celsius / 5.0 * 9.0 + 32.0;
        printf("|%3.0f| %6.1f|\n", celsius, fahr);
        celsius += step;
    }
}

int main() {
    fahrCelsTable();
}
