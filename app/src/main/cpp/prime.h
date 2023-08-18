//
// Created by Dingyi on 8/11/2023.
//

#ifndef PRIMENUMBERS_PRIME_H
#define PRIMENUMBERS_PRIME_H

#pragma once
#include <string>
#include <regex>
#include <unordered_map>
#include "threadpool.h"

namespace prim_num_api {

class PrimeNumbers {
private:
    std::unique_ptr<std::unordered_map<int, int>> prim_list_;
    int max_prim_order_;
    std::mutex mutex_;
    bool IsPrime(int);
    int GetNthPrimeNumber(int);
    ThreadPool* thread_pool_;
    std::regex kNumericegexPattern;
    static constexpr int kMaxPrimeOrder { 50000 }; // The boundary of the order is 50,000.

public:
    PrimeNumbers(const PrimeNumbers& pm) = delete;
    void operator= (const PrimeNumbers& pm) = delete;
    std::string GetPrimeList(std::string&&);
    PrimeNumbers(int num_threads = 4);
    ~PrimeNumbers();
};

}

#endif //PRIMENUMBERS_PRIME_H
