#include <chrono>
#include <fstream>
#include <array>
#include <algorithm>
#include <unordered_map>

static constexpr int PAIR_AMOUNT = 1000;

int main() {
  std::array<std::int32_t, PAIR_AMOUNT> a, b;
  std::chrono::high_resolution_clock clock;
  std::uint64_t total_distance;
  std::uint64_t similarity_score;
  std::unordered_map<std::int32_t, std::int32_t> occurrence_count;

  std::println("[*] Total pair amount: {}", PAIR_AMOUNT);
  std::println("[*] Loading data...");

  std::ifstream input("input.txt");

  if (!input.is_open()) {
    std::println("[!] Failed to open input file!");
    exit(EXIT_FAILURE);
  }

  // Parsing data
  auto start = clock.now();

  for (std::uint32_t i = 0; i < PAIR_AMOUNT; ++i) {
    std::string tmp1, tmp2;
    input >> tmp1 >> tmp2;
    a[i] = std::stoi(tmp1);
    b[i] = std::stoi(tmp2);
    ++occurrence_count[b[i]];
  }

  auto end = clock.now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::println("[*] Parsed and counted second part in {}", duration);

  // Sorting data
  start = clock.now();

  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());

  end = clock.now();
  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::println("[*] Sorted data in {}", duration);

  // Searching for solution 1
  start = clock.now();

  for (std::uint32_t i = 0; i < PAIR_AMOUNT; ++i) {
    total_distance += std::labs(a[i] - b[i]);
  }

  end = clock.now();
  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::println("[*] Solution 1 found in {}", duration);
  
  std::println("[*] Solution 1: {}", total_distance);

  // Searching for solution 2
  start = clock.now();

  for (std::uint32_t i = 0; i < PAIR_AMOUNT; ++i) {
    if (!occurrence_count.contains(a[i])) continue;

    int& num = a[i];

    similarity_score += num * occurrence_count[num];
  }

  end = clock.now();
  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::println("[*] Solution 1 found in {}", duration);

  std::println("[*] Solution 2: {}", similarity_score);
}