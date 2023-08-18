//
// Created by Dingyi on 8/11/2023.
//

#pragma once
#include "prime.h"
#include <math.h>
#include <android/log.h>

using namespace prim_num_api;

PrimeNumbers::PrimeNumbers(int num_threads):
        max_prim_order_ { 0 },
        thread_pool_ { new ThreadPool(num_threads) },
        kNumericegexPattern { std::regex("[+-]?[0-9]+(\\.[0-9]+)?") },
        prim_list_ { std::make_unique<std::unordered_map<int, int>>() } {}

PrimeNumbers::~PrimeNumbers() {
    delete thread_pool_;
}

bool PrimeNumbers::IsPrime(int num) {
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

int PrimeNumbers::GetNthPrimeNumber(int n) {
    // The biggest prime in Integer range is `2,147,483,647` (2^31 - 1), its order equal to `105,097,565`.
    // But also considering the computation time, let `n <= kMaxPrimeOrder`.
    if (n > kMaxPrimeOrder) {
        return 0;
    }

    for (int i = 0, counter = 0; counter <= n; i++) {
        if (IsPrime(i)) {
            counter++;
            if (counter == n) {
                return i;
            }
        }
    }

    return 0;
}

std::string PrimeNumbers::GetPrimeList(std::string&& str) {
    mutex_.lock();

    std::vector<std::future<std::pair<int, int>>> results;
    int input_index = 0;
    std::sregex_iterator iterator(str.begin(), str.end(), kNumericegexPattern);
    std::sregex_iterator end;
    __android_log_print(ANDROID_LOG_DEBUG, "prime_native", "num threads: %d", thread_pool_->size());
    while (iterator != end) {
        std::smatch match = *iterator;
        __android_log_print(ANDROID_LOG_DEBUG, "prime_native", "input string: %s", match.str().c_str());
        int input = std::stof(match.str());
        __android_log_print(ANDROID_LOG_DEBUG, "prime_native", "input: %d", input);

        results.emplace_back(thread_pool_->enqueue([input_index, input, this] {
            __android_log_print(ANDROID_LOG_DEBUG, "prime_native", "thread input index: %d", input_index);
            return std::make_pair(input_index, this->GetNthPrimeNumber(input));
        }));
        ++iterator;
        ++input_index;
    }

    std::vector<std::pair<int, int>> pairs;
    pairs.reserve(results.size()); // pre-allocate memory to improve performance

    for (auto& result : results) {
        pairs.emplace_back(std::move(result.get()));
    }

    // Sort the prime numbers by its input order.
    std::sort(pairs.begin(), pairs.end(), [] (
            const std::pair<int, int>&a,
            const std::pair<int, int>& b) {
       return a.first < b.first;
    });

    std::string output;
    for (const auto& pair : pairs) {
        output += std::to_string(pair.second) + " ";
    }

    mutex_.unlock();
    return std::move(output);
}