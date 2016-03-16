#include <iostream>
#include <algorithm>
#include <vector>

template <typename I> // I models RandomAccessIterator
void qsort(I f, I l)
{
  if (f == l)
    return;

  auto pv = *f;
  auto boundary = std::partition(f, l, [pv](int now) { return pv > now;  });
  auto pv_ins = std::partition(boundary, l, [pv](int now) { return pv == now; });
  qsort(f, boundary);
  qsort(pv_ins, l);
}

template <typename I> // I models ForwardIterator
void reverse2(I f, I l)
{
  // no effect
  if (f == l || f + 1 == l)
  {
    return;
  }

  auto dis = std::distance(f, l);
  auto m = dis / 2;
  reverse2(f, f + m);
  reverse2(f + m, l);

  //if (dis % 2 == 0)
  //  std::swap_ranges(f, f + m, f + m);
  //else
  std::rotate(f, f + m, l);
}

template <typename I> // I models RandomAccessIterator
void subrange_sort(I f, I l, I sf, I sl)
{
  if (f == l || sf == sl)
    return;

  //std::partial_sort(f, sf, l);
  std::partial_sort(f, sl, l);
}

template <typename I>
void print(I f, I l)
{
  for (I i = f; i < l; ++i)
  {
    std::cout << *i << " ";
  }
  std::cout << std::endl;
}

int main()
{
  std::vector<int> vec = { 5,4,6,3,10,1 };
  qsort(std::begin(vec), std::end(vec));
  for (int elem : vec) std::cout << elem << ' ';
  std::cout << std::endl << "------------------------------" << std::endl;

  std::vector<int> vec2 = { 1,2,3,4,5,6,7,8 };
  reverse2(std::begin(vec2), std::end(vec2));
  for (int elem : vec2) std::cout << elem << ' ';
  std::cout << std::endl << "------------------------------" << std::endl;

  std::vector<int> v{ 5,4,2,1,5,2,4 };
  subrange_sort(begin(v), end(v), begin(v) + 2, begin(v) + 4);
  // => { ?, ?, 2, 4, ?, ?, ? }
  for (int elem : v) std::cout << elem << ' ';
  std::cout << std::endl << "------------------------------" << std::endl;
}
