//
// Created by Dingyi on 8/11/2023.
//

#ifndef PRIMENUMBERS_PRIME_H
#define PRIMENUMBERS_PRIME_H

#include <unordered_map>

class PrimeNumbers {
private:
    std::unordered_map<int, int> prim_list;
    int max_visited_prime_idx = 0;
public:
    int GetNthPrimeNumber(int n);
};

int GetNthPrimeNumber(int n);

extern "C" {

}


#endif //PRIMENUMBERS_PRIME_H
