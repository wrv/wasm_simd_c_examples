extern int total_sum(int* in_a, int* in_b);

int total_sum_wrapper(int* in_a, int* in_b) {
  return total_sum(in_a, in_b);
}