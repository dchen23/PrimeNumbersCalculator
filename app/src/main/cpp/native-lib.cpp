#include <jni.h>
#include "PrimeNumbersAPI.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_prime_MainActivity_nativeGetStringOfPrimeNumbers(
        JNIEnv* env,
        jobject obj /* this */,
        jlong native_wrapper,
        jstring str) {

    const char* utfChars = env->GetStringUTFChars(str, nullptr);

    std::string result = prim_num_api_Run(
            reinterpret_cast<prim_num_api_handle>(native_wrapper), utfChars);

    env->ReleaseStringUTFChars(str, utfChars);

    return env->NewStringUTF( result.c_str() );
}

extern "C" JNIEXPORT jlong JNICALL
Java_com_example_prime_MainActivity_nativeCreatePrimeNumberHandle(
        JNIEnv* env,
        jobject obj /* this */) {
    return reinterpret_cast<jlong>(prim_num_api_Create());
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_prime_MainActivity_nativeDestroyPrimeNumberHandle(
        JNIEnv* env,
        jobject obj /* this */,
        jlong native_wrapper) {
    prim_num_api_Destroy(reinterpret_cast<prim_num_api_handle>(native_wrapper));
}