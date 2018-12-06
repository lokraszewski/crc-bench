/*
 * @Author: Lukasz
 * @Date:   06-12-2018
 * @Last Modified by:   Lukasz
 * @Last Modified time: 06-12-2018
 */
#include <algorithm>
#include <benchmark/benchmark.h>
#include <climits>
#include <functional>
#include <random>
#include <set>
#include <vector>

#include <crc/crc.h>
#define BM_LOWER_BYTE_COUNT 8
#define BM_UPPER_BYTE_COUNT (8 << 12)

static auto generate_test_data(const size_t num_bytes)
{
  using random_bytes_engine = std::independent_bits_engine<std::default_random_engine, CHAR_BIT, unsigned char>;
  static random_bytes_engine rbe;
  std::vector<uint8_t>       data(num_bytes);
  std::generate(begin(data), end(data), std::ref(rbe));
  return data;
}

static void BM_cpp_crc_ccitt_basic(benchmark::State &state)
{
  crc::basic::ccitt_t ccitt;
  auto                test_data = generate_test_data(state.range(0));

  while (state.KeepRunning())
  {
    benchmark::DoNotOptimize(ccitt.process_bytes(&test_data[0], test_data.size()));
  }
}
BENCHMARK(BM_cpp_crc_ccitt_basic)->RangeMultiplier(2)->Range(BM_LOWER_BYTE_COUNT, BM_UPPER_BYTE_COUNT);

static void BM_cpp_crc_ccitt_fast(benchmark::State &state)
{
  crc::fast::ccitt_t ccitt;
  auto               test_data = generate_test_data(state.range(0));

  while (state.KeepRunning())
  {
    benchmark::DoNotOptimize(ccitt.process_bytes(&test_data[0], test_data.size()));
  }
}
BENCHMARK(BM_cpp_crc_ccitt_fast)->RangeMultiplier(2)->Range(BM_LOWER_BYTE_COUNT, BM_UPPER_BYTE_COUNT);

//~~~~~~~~~~~~~~~~

BENCHMARK_MAIN();
