//
// Created by chick on 8/17/2023.
//

#pragma once
#ifndef PRIMENUMBERS_PRIMENUMBERSAPI_H
#define PRIMENUMBERS_PRIMENUMBERSAPI_H

#include <string>

#ifdef __cplusplus
extern "C" {
#endif

typedef void* prim_num_api_handle;

prim_num_api_handle prim_num_api_Create();
void prim_num_api_Destroy(prim_num_api_handle);
std::string prim_num_api_Run(prim_num_api_handle, const char *);

#ifdef __cplusplus
}
#endif

#endif //PRIMENUMBERS_PRIMENUMBERSAPI_H
