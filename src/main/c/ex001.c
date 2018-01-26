#include <stdio.h>

void fahrCelsTable() {
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20; /* step size*/

    fahr = lower;
    printf("| F |    C  |\n");
    for(fahr = upper; fahr >= lower; fahr -= step) {
        celsius = (5.0 / 9.0) * (fahr - 32.0);
        printf("|%3.0f| %6.1f|\n", fahr, celsius);
    }

    lower = -30;
    upper = 150;
    step = 10;

    printf("\n");
    printf("| C |    F  |\n");
    for(celsius = upper; celsius >= lower; celsius -= step) {
        fahr = celsius / 5.0 * 9.0 + 32.0;
        printf("|%3.0f| %6.1f|\n", celsius, fahr);
    }
}

int main() {
    fahrCelsTable();
}
