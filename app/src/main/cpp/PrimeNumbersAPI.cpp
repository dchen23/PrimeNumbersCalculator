//
// Created by chick on 8/17/2023.
//

#pragma once
#include "PrimeNumbersAPI.h"
#include "prime.h"

using namespace prim_num_api;

prim_num_api_handle prim_num_api_Create() {
    PrimeNumbers* handle = new PrimeNumbers(8);
    return handle;
}

void prim_num_api_Destroy(prim_num_api_handle handle) {
    delete static_cast<PrimeNumbers*>(handle);
}

void prim_num_api_Resume(prim_num_api_handle handle) {
    static_cast<PrimeNumbers*>(handle)->ResumeWorkers();
}

void prim_num_api_Pause(prim_num_api_handle handle) {
    static_cast<PrimeNumbers*>(handle)->PauseWorkers();
}

std::string prim_num_api_Run(prim_num_api_handle handle, const char* c_str) {
    std::string input;
    input.assign(c_str);
    return std::move(static_cast<PrimeNumbers*>(handle)->GetPrimeList(std::move(input)));
}