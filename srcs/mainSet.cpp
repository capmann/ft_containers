#include <iostream>
#include<algorithm>
#include <string>
#include <deque>
#include "../includes/colormod.hpp"
#include <unistd.h>
#include "../includes/set.hpp"
#include "../includes/map.hpp"
#include "../includes/stack.hpp"
#include "../includes/vector.hpp"
#include "../includes/red_black_tree.hpp"
#include "../includes/map_utils.hpp"

int main ()
{
  ft::set<int> myset;

  for (int i=1; i<=5; i++) myset.insert(i*10);   // myset: 10 20 30 40 50

  ft::pair<ft::set<int>::const_iterator,ft::set<int>::const_iterator> ret;
  ret = myset.equal_range(30);

  std::cout << "the lower bound points to: " << *ret.first << '\n';
  std::cout << "the upper bound points to: " << *ret.second << '\n';

  return 0;
}
