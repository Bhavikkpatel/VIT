#include <iostream>
#include <vector>
#include <omp.h>
#include <algorithm>
#include <cmath>
#include <climits>

bool is_prime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) return false;
    }
    return true;
}

int main() {
    int n, value;
    std::cout << "Enter the number of elements in the array: ";
    std::cin >> n;
    std::vector<int> arr(n);

    std::cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    std::cout << "Enter the value to add and multiply with each element: ";
    std::cin >> value;

    double start, end;

    // Task 1: Initialize and print the array elements
    std::cout << "Array elements: ";
    start = omp_get_wtime();
#pragma omp parallel for
    for (int i = 0; i < n; ++i) {
#pragma omp critical
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    end = omp_get_wtime();
    std::cout << "Initialization and printing time: " << (end - start) << " seconds" << std::endl;

    // Task 2: Add and multiply a value to each element and print the same
    start = omp_get_wtime();
#pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        arr[i] += value;
        arr[i] *= value;
    }
    std::cout << "Updated array elements: ";
#pragma omp parallel for
    for (int i = 0; i < n; ++i) {
#pragma omp critical
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    end = omp_get_wtime();
    std::cout << "Addition, multiplication, and printing time: " << (end - start) << " seconds" << std::endl;

    // Task 3: Find the sum, odd sum, even sum, and count odd and even elements
    int sum = 0, odd_sum = 0, even_sum = 0, odd_count = 0, even_count = 0;
    start = omp_get_wtime();
#pragma omp parallel for reduction(+:sum, odd_sum, even_sum, odd_count, even_count)
    for (int i = 0; i < n; ++i) {
        sum += arr[i];
        if (arr[i] % 2 == 0) {
            even_sum += arr[i];
            even_count++;
        } else {
            odd_sum += arr[i];
            odd_count++;
        }
    }
    end = omp_get_wtime();
    std::cout << "Sum: " << sum << ", Odd Sum: " << odd_sum << ", Even Sum: " << even_sum << std::endl;
    std::cout << "Odd Count: " << odd_count << ", Even Count: " << even_count << std::endl;
    std::cout << "Sum and count time: " << (end - start) << " seconds" << std::endl;

    // Task 4: Sum of squares, cubes, find max, min, second largest, and second smallest
    int sum_squares = 0, sum_cubes = 0, max_val = INT_MIN, min_val = INT_MAX;
    start = omp_get_wtime();
#pragma omp parallel for reduction(+:sum_squares, sum_cubes) reduction(max:max_val) reduction(min:min_val)
    for (int i = 0; i < n; ++i) {
        sum_squares += arr[i] * arr[i];
        sum_cubes += arr[i] * arr[i] * arr[i];
        if (arr[i] > max_val) max_val = arr[i];
        if (arr[i] < min_val) min_val = arr[i];
    }
    int second_max = INT_MIN, second_min = INT_MAX;
#pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        if (arr[i] > second_max && arr[i] < max_val) second_max = arr[i];
        if (arr[i] < second_min && arr[i] > min_val) second_min = arr[i];
    }
    end = omp_get_wtime();
    std::cout << "Sum of squares: " << sum_squares << ", Sum of cubes: " << sum_cubes << std::endl;
    std::cout << "Max: " << max_val << ", Min: " << min_val << std::endl;
    std::cout << "Second Max: " << second_max << ", Second Min: " << second_min << std::endl;
    std::cout << "Sum of squares, cubes, max, min, second max, second min time: " << (end - start) << " seconds" << std::endl;

    // Task 5: Print and count prime numbers and their sum
    int prime_sum = 0, prime_count = 0;
    start = omp_get_wtime();
#pragma omp parallel for reduction(+:prime_sum, prime_count)
    for (int i = 0; i < n; ++i) {
        if (is_prime(arr[i])) {
#pragma omp critical
            std::cout << arr[i] << " ";
            prime_sum += arr[i];
            prime_count++;
        }
    }
    std::cout << std::endl;
    end = omp_get_wtime();
    std::cout << "Prime Sum: " << prime_sum << ", Prime Count: " << prime_count << std::endl;
    std::cout << "Print, count primes, and prime sum time: " << (end - start) << " seconds" << std::endl;

    return 0;
}
