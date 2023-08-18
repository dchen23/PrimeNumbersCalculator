//
// Created by Dingyi on 8/11/2023.
//

#include "prime.h"
#include <math.h>

bool isPrime(int num) {
    if (num < 2) return false;
    // Iterate through the numbers from 2 to n.
    for (int i = 2; i < num; i++) {
        // Check if the number is prime.
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

// The biggest prime in Integer range is `2,147,483,647` (2^31 - 1), its order equal to `105,097,565`.
// But also considering the computation time, let `n <= 50000`.
int GetNthPrimeNumber(int n) {

    if (n > 50000) {
        return 0;
    }

    for (int i = 0, counter = 0; counter <= n; i++) {
        if (isPrime(i)) {
            counter++;
            if (counter == n) {
                return i;
            }
        }
    }

    return 0;
}