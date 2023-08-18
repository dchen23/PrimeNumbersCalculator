#include <jni.h>
#include <string>
#include <regex>
#include <android/log.h>
#include "prime.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_prime_MainActivity_nativeGetStringOfPrimeNumbers(
        JNIEnv* env,
        jobject obj /* this */,
        jstring str) {

    const char* utfChars = env->GetStringUTFChars(str, nullptr);
    std::string input;
    input.assign(utfChars);
    env->ReleaseStringUTFChars(str, utfChars);

    prim_num_api::PrimeNumbers handle(8);
    std::string result = handle.GetPrimeList(std::move(input));

    return env->NewStringUTF( result.c_str() );
}