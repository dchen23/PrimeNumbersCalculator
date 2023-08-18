#include <jni.h>
#include <string>
#include <regex>
#include <android/log.h>
#include "prime.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_prime_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {

    std::string str = "-$abc-123456 16.7 ,, 8 9 -10 --== +22";
    std::regex regex_pattern("[+-]?[0-9]+\\.?[0-9]+");
    std::sregex_iterator iterator(str.begin(), str.end(), regex_pattern);
    std::sregex_iterator end;
    while (iterator != end) {
        std::smatch match = *iterator;
        __android_log_print(ANDROID_LOG_DEBUG, "prime_native", "input string: %s", match.str().c_str());
        int input = std::stof(match.str());
        __android_log_print(ANDROID_LOG_DEBUG, "prime_native", "input: %d", input);
        iterator++;
    }

    return env->NewStringUTF( std::to_string(GetNthPrimeNumber(500)).c_str());
}