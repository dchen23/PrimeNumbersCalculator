# PrimeNumbersCalculator

 A cross-platform library and an Android app that can calculate the N:th prime number based on user input.

## Environment
- Android Studio Hedgehog | 2023.1.1 Canary 16
  - NDK 25.1.8937393
  - cmake 3.22.1
- Test Device: OnePlus 7 Pro (Android 11)
 
## Usage
1. Type anything you like inside `INPUT` text box;
   > NOTE: Only intergers in range **(0, 50000]** will return proper result, non-calculable input will always return **`0`** !
3. Click the `RUN` button to calculate all prime numbers;
4. If input sequence has large value (like 20,000), the process will take longer, and all button will be unclickable. Just wait for few seconds;
5. The result of N:th prime numbers will display on the `OUTPUT` textview;
6. Click the `CLR` buttorn, both the `INPUT` text box and `OUTPUT` textview will reset;
7. Start forn 1st step.



<details>
<summary>The Examples of <b>Input/Ouput</b> </summary>

- Sample Input #1
  ```
  Hello 2, 4, 7.5
  ```
- Sample Output #1
  ```
  3, 7, 17
  ```
- Sample Input #2
  ```
  0 1 -10 +34.5 12000
  ```
- Sample Output #2
  ```
  0, 2, 0, 139, 128189
  ```
- Sample Input #3
  ```
  -+abc123 #$-345 7 "!$+50000 50001
  ```
- Sample Output #3
  ```
  677, 0, 17, 611953, 0
  ```

</details>


## Documentation

The core cross-plarform library can be delievered as .so/.h files:
- PrimeNumbersAPI.so: [PrimeNumbersAPI.cpp](app/src/main/cpp/PrimeNumbersAPI.cpp), [prime.cpp](app/src/main/cpp/prime.cpp), [prime.h](app/src/main/cpp/prime.h), [threadpool.h](app/src/main/cpp/threadpool.h)
- PrimeNumbersAPI.h: [PrimeNumbersAPI.h](app/src/main/cpp/PrimeNumbersAPI.h).

The functionality can be divided into four main parts:
1. **Numeric Sequence Pharser:** Use regex to find all matched numeric inputs
2. **Prime Calculator:** A brute force approaching to find N:th prime number is less than or equal to 50,000 in order
3. **C-style API Wrapper:** A C API layer provides better compatibility and interoperability, while also avoiding C++ feature conflicts and ensuring API stability
4. **Thread Pool Utility:** A thread pool manages a fixed set of threads, improving resource utilizaion and enbaling efficient concurrent task execution
5. **Hybird Lifetime Control:** An objects and resources manager for both Kotlin and C++ languages, considering their distinct memory management and lifetime paradigms within a single application
6. **Android App:** A Kotlin frontend can communicate with native libraries using the Java Native Interface (JNI).

## Achievements

- [X] Application responsiveness & edge cases
- [X] Cross platform compatibility
- [X] Multithreading support
- [X] Memory management
- [X] Library API design
- [X] Code readability
- [X] Threads/resources should be properly terminated/released after UI has been closed.

## Screenshots

## TODO
- [ ] Utilize a hash table to store calculated `order, prime_number` pairs
- [ ] Apply less time-consuming prime number calculation algorithm, like [Sieve of Eratosthenes](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes) or [Sieve of Atkin](https://en.wikipedia.org/wiki/Sieve_of_Atkin)
- [ ] Support more numeric input format, such as *scientific notation*, *arithmetic calculation* and so on
- [ ] Change application frontend to compose UI framework.
