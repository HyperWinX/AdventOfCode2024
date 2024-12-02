#include <chrono>
#include <fstream>
#include <array>
#include <algorithm>
#include <unordered_map>
#include <vector>

static constexpr int REPORT_COUNT = 1000;

enum class Direction {
  Decreasing,
  Increasing
};

struct RemovedElement {
  std::int16_t val;
  std::int16_t idx;
};

bool is_safe(std::int8_t& prev_num, std::vector<std::int16_t>& splitted, Direction direction, std::int8_t idx_to_skip = -1) {
  RemovedElement elem;
  if (idx_to_skip != -1) {
    elem = RemovedElement{splitted[idx_to_skip], idx_to_skip};
    splitted.erase(splitted.begin() + idx_to_skip);
  }

  prev_num = splitted[0];
  for (std::uint8_t i = 1; i < splitted.size(); ++i) {
    switch (direction) {
      case Direction::Increasing:
        if (splitted[i] - prev_num > 3 ||
            splitted[i] - prev_num < 0 ||
            splitted[i] == prev_num) {
              return false;
            }
        break;
      case Direction::Decreasing:
        if (prev_num - splitted[i] > 3 ||
            prev_num - splitted[i] < 0 ||
            splitted[i] == prev_num) {
              return false;
            }
        break;
    }
    prev_num = splitted[i];
  }

  splitted.insert(splitted.begin() + elem.idx, elem.val);
  return true;
}

int main() {
  std::chrono::high_resolution_clock clock;
  std::vector<std::int16_t> splitted;
  std::uint64_t safe_reports;
  std::stringstream ss;
  

  std::println("[*] Total report count: {}", REPORT_COUNT);
  std::println("[*] Loading data...");

  std::ifstream input("input.txt");

  if (!input.is_open()) {
    std::println("[!] Failed to open input file!");
    exit(EXIT_FAILURE);
  }

  // Parsing data and searching for a solution
  auto start = clock.now();

  for (std::uint32_t i = 0; i < REPORT_COUNT; ++i) {
    std::uint8_t problem_dampener_skip_idx;
    std::int8_t prev_num = -1;
    std::string tmp1, tmp2;
    Direction direction;

    std::getline(input, tmp1);

    // Splitting string
    for (char ch : tmp1) {
      if (ch == ' ') {
        splitted.push_back(std::stoi(tmp2));
        tmp2.clear();
      } else {
        tmp2 += ch;
      }
    }
    splitted.push_back(std::stoi(tmp2));

    // Checking if report is safe

    // Find direction
    if (splitted[1] < splitted[0]) {
      direction = Direction::Decreasing;
    } else if (splitted[1] > splitted[0]) {
      direction = Direction::Increasing;
    } else {
      continue;
    }

    if (is_safe(prev_num, splitted, direction)) {
      ++safe_reports;
      continue;
    }

    // Using Problem Dampener algorithm if report is not safe
    for (std::uint8_t i = 0; i < splitted.size(); ++i) {
      if (is_safe(prev_num, splitted, direction, problem_dampener_skip_idx++)) {
        ++safe_reports;
        break;
      }
    }
    splitted.clear();
  }

  auto end = clock.now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::println("[*] Parsed and found solution 1 in {}", duration);
  
  std::println("[*] Solution 1: {}", safe_reports);

}