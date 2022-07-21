
#include <iostream>
#include<algorithm>
#include <string>
#include <deque>
#include "../includes/colormod.hpp"
#include <unistd.h>

Color::Modifier		red(Color::FG_RED);
Color::Modifier		cyan(Color::FG_CYAN);
Color::Modifier		def(Color::FG_DEFAULT);
Color::Modifier		green(Color::FG_GREEN);
Color::Modifier		magenta(Color::FG_LIGHT_MAGENTA);

#if VERSION
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include "../includes/map.hpp"
	#include "../includes/stack.hpp"
	#include "../includes/vector.hpp"
	#include "../includes/red_black_tree.hpp"
	#include "../includes/map_utils.hpp"
#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

template <typename T>
void	print(T x) {
	std::cout << x << " ";
};

int main(int argc, char** argv) {
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	std::cout << std::endl;

	std::cout << cyan << "======= TESTING VECTOR FEATURES =======" << def << std::endl;

	std::cout << std::endl;
	
	std::cout << magenta << "======= Creating an empty vector =======" << def << std::endl;

	ft::vector<int> vector;
	std::cout << "Size of the vector is " << vector.size() << std::endl;
	std::cout << "Capacity of the vector is " << vector.capacity() << std::endl;
	std::cout << "Max size of the vector is " << vector.max_size() << std::endl;
	std::cout << "Is vector empty?" << std::endl;
	if (vector.empty() == true)
		std::cout << green << "yes" << def << std::endl;
	else
		std::cout << red << "no" << def << std::endl;

	std::cout << magenta << "======= Creating a vector with 10 elements of value 10 =======" << def << std::endl;

	ft::vector<int>	vec_plus_ultra(10, 10);
	std::cout << "Size of the vector is " << vec_plus_ultra.size() << std::endl;
	std::cout << "Max size of the vector is " << vec_plus_ultra.max_size() << std::endl;
	std::cout << "Is vector empty?" << std::endl;
	if (vec_plus_ultra.empty() == true)
		std::cout << green << "yes" << def << std::endl;
	else
		std::cout << red << "no" << def << std::endl;
	ft::vector<int>::iterator	it;
	size_t	i = 0;
	for (it = vec_plus_ultra.begin(); it < vec_plus_ultra.end(); it++)
		std::cout << "Vector[" << i++ << "] = " << *it << std::endl;

	std::cout << magenta << "======= Assigning new content of value 42 and size seed =======" << def << std::endl;

	vec_plus_ultra.assign(seed, 42);
	std::cout << "Size of the vector is now " << vec_plus_ultra.size() << std::endl;
	i = 0;
	for (it = vec_plus_ultra.begin(); it < vec_plus_ultra.end(); it++)
		std::cout << "Vector[" << i++ << "] = " << *it << std::endl;

	std::cout << magenta << "======= Reassigning new content of value 42 and size 20 =======" << def << std::endl;

	vec_plus_ultra.assign(20, 42);
	std::cout << "Size of the vector is now " << vec_plus_ultra.size() << std::endl;
	std::cout << "Value inside the vector is " << vec_plus_ultra.at(1) << std::endl;
	std::cout << "First value is " << vec_plus_ultra.front() << std::endl;
	std::cout << "Last value is " << vec_plus_ultra.back() << std::endl;
	i = 0;
	for (it = vec_plus_ultra.begin(); it < vec_plus_ultra.end(); it++)
		std::cout << "Vector[" << i++ << "] = " << *it << std::endl;

	std::cout << magenta << "======= Pushing number 5 on the back =======" << def << std::endl;

	vec_plus_ultra.push_back(5);
	std::cout << "Last value is now " << vec_plus_ultra.back() << std::endl;
	std::cout << "Size of the vector is now " << vec_plus_ultra.size() << std::endl;
	i = 0;
	for (it = vec_plus_ultra.begin(); it < vec_plus_ultra.end(); it++)
		std::cout << "Vector[" << i++ << "] = " << *it << std::endl;
	
	std::cout << magenta << "======= Popping number 5 out =======" << def << std::endl;

	vec_plus_ultra.pop_back();
	std::cout << "Last value is now " << vec_plus_ultra.back() << std::endl;
	std::cout << "Size of the vector is now " << vec_plus_ultra.size() << std::endl;
	i = 0;
	for (it = vec_plus_ultra.begin(); it < vec_plus_ultra.end(); it++)
		std::cout << "Vector[" << i++ << "] = " << *it << std::endl;

	std::cout << magenta << "======= Inserting number 5 at front =======" << def << std::endl;
	
	vec_plus_ultra.insert(vec_plus_ultra.begin(), 5);
	std::cout << "First value is now " << vec_plus_ultra.front() << std::endl;
	std::cout << "Size of the vector is now " << vec_plus_ultra.size() << std::endl;
	i = 0;
	for (it = vec_plus_ultra.begin(); it < vec_plus_ultra.end(); it++)
		std::cout << "Vector[" << i++ << "] = " << *it << std::endl;

	std::cout << magenta << "======= Removing number 5 at front =======" << def << std::endl;
	
	vec_plus_ultra.erase(vec_plus_ultra.begin());
	std::cout << "First value is now " << vec_plus_ultra.front() << std::endl;
	std::cout << "Size of the vector is now " << vec_plus_ultra.size() << std::endl;
	i = 0;
	for (it = vec_plus_ultra.begin(); it < vec_plus_ultra.end(); it++)
		std::cout << "Vector[" << i++ << "] = " << *it << std::endl;

	std::cout << magenta << "======= Inserting seed number 5 at position 5 =======" << def << std::endl;
	
	it = vec_plus_ultra.begin() + 5;
	vec_plus_ultra.insert(it, seed, 5);
	std::cout << "Size of the vector is now " << vec_plus_ultra.size() << std::endl;
	i = 0;
	for (it = vec_plus_ultra.begin(); it < vec_plus_ultra.end(); it++)
		std::cout << "Vector[" << i++ << "] = " << *it << std::endl;

	std::cout << magenta << "======= Erasing the all number 5 we created =======" << def << std::endl;
	
	it = vec_plus_ultra.begin() + 5;
	vec_plus_ultra.erase(it, it + seed);
	std::cout << "Size of the vector is now " << vec_plus_ultra.size() << std::endl;
	i = 0;
	for (it = vec_plus_ultra.begin(); it < vec_plus_ultra.end(); it++)
		std::cout << "Vector[" << i++ << "] = " << *it << std::endl;

	std::cout << magenta << "======= Create a new vector thanks to iterators =======" << def << std::endl;
	
	ft::vector<int>	vec_iter(vec_plus_ultra.begin(), vec_plus_ultra.end());
	std::cout << "Size of the vector is now " << vec_iter.size() << std::endl;
	std::cout << "First value is now " << vec_iter.front() << std::endl;
	std::cout << "Last value is now " << vec_iter.back() << std::endl;

	std::cout << magenta << "======= Inserting new elements without iterators =======" << def << std::endl;

	vec_iter.insert(vec_iter.begin() + 5, seed, 5);
	std::cout << "Size of the vector is now " << vec_iter.size() << std::endl;
	std::cout << "First value is now " << vec_iter.front() << std::endl;
	std::cout << "Last value is now " << vec_iter.back() << std::endl;

	i = 0;
	for (it = vec_iter.begin(); it < vec_iter.end(); it++)
		std::cout << "Vector[" << i++ << "] = " << *it << std::endl;


	std::cout << magenta << "======= Creating new vector and inserting new elements thanks to push back =======" << def << std::endl;

	ft::vector<int> vec_debug;
	i = 0;
	while ((int)i < seed)
		vec_debug.push_back(i++);
	
	i = 0;
	for (it = vec_debug.begin(); it < vec_debug.end(); it++)
		std::cout << "Vector[" << i++ << "] = " << *it << std::endl;


	std::cout << magenta << "======= Inserting new elements thanks to iterators =======" << def << std::endl;

	ft::vector<int> vec_test(10, 10);

	vec_debug.insert(vec_debug.begin() + 5, vec_test.begin(), vec_test.end());

	i = 0;
	for (it = vec_debug.begin(); it < vec_debug.end(); it++)
		std::cout << "Vector[" << i++ << "] = " << *it << std::endl;

	std::cout << magenta << "======= Erasing new elements thanks to iterators =======" << def << std::endl;

	vec_debug.erase(vec_debug.begin() + 5, vec_debug.begin() + 15);
	std::cout << "Size of the vector is now " << vec_debug.size() << std::endl;

	i = 0;
	for (it = vec_debug.begin(); it < vec_debug.end(); it++)
		std::cout << "Vector[" << i++ << "] = " << *it << std::endl;

	std::cout << magenta << "======= Erasing 1 element at position 2 =======" << def << std::endl;

	vec_debug.erase(vec_debug.begin() + 2);
	std::cout << "Size of the vector is now " << vec_debug.size() << std::endl;

	i = 0;
	for (it = vec_debug.begin(); it < vec_debug.end(); it++)
		std::cout << "Vector[" << i++ << "] = " << *it << std::endl;

	std::cout << magenta << "======= Erasing 3 element at position 3 =======" << def << std::endl;

	vec_debug.erase(vec_debug.begin() + 3, vec_debug.begin() + 6);
	std::cout << "Size of the vector is now " << vec_debug.size() << std::endl;

	i = 0;
	for (it = vec_debug.begin(); it < vec_debug.end(); it++)
		std::cout << "Vector[" << i++ << "] = " << *it << std::endl;


	std::cout << magenta << "======= Swapping the content of two vectors =======" << def << std::endl;

	ft::vector<int>	A(1, 1);
	ft::vector<int>	B(2, 2);

	i = 0;
	for (it = A.begin(); it < A.end(); it++)
		std::cout << "VectorA[" << i++ << "] = " << *it << std::endl;

	i = 0;
	for (it = B.begin(); it < B.end(); it++)
		std::cout << "VectorB[" << i++ << "] = " << *it << std::endl;

	A.swap(B);

	i = 0;
	for (it = A.begin(); it < A.end(); it++)
		std::cout << "VectorA[" << i++ << "] = " << *it << std::endl;

	i = 0;
	for (it = B.begin(); it < B.end(); it++)
		std::cout << "VectorB[" << i++ << "] = " << *it << std::endl;


	std::cout << std::endl;

	std::cout << cyan << "======= TRICKY TESTS =======" << def << std::endl;

	std::cout << std::endl;

	std::cout << magenta << "======= Inception test =======" << def << std::endl;

  	ft::vector<int>			test(3, 3);
  	ft::vector<ft::vector<int> >	BOB(5, test);
  	std::cout << "BOB SIZE IS " << BOB.size() << std::endl;
  	ft::vector<ft::vector<int> >	MIKE(BOB);

	std::cout << "MIKE SIZE IS " << MIKE.size() << std::endl;

	std::cout << magenta << "======= Algorithm test =======" << def << std::endl;

	ft::vector<int> myvector;

	for (size_t i = 0; i < 25; i++)
		myvector.push_back(i * i);

	ft::vector<int>::iterator italgo = std::find(myvector.begin(), myvector.begin() + 15, 4);
	if (italgo != myvector.end())
		std::cout << "find : " << *italgo << std::endl;
	else
		std::cout << "not find" << std::endl;
	std::cout << "for_each : ";
	std::for_each(myvector.begin(), myvector.end(), print<int>);
	std::cout << "\n";

	std::cout << "copy : ";
	ft::vector<int> copy_vector(myvector.size());
	std::copy(myvector.begin(), myvector.end(), copy_vector.begin());

	std::for_each(copy_vector.begin(), copy_vector.end(), print<int>);
	std::cout << "\n";

	std::fill (myvector.begin(),myvector.begin()+4,5);   // myvector: 5 5 5 5 0 0 0 0
	std::fill (myvector.begin()+3,myvector.end()-2,8);   // myvector: 5 5 5 8 8 8 0 0

	std::cout << "myvector contains:";
	for (ft::vector<int>::iterator italgo=myvector.begin(); italgo!=myvector.end(); ++italgo)
	std::cout << ' ' << *italgo;
	std::cout << '\n';

	std::sort (myvector.begin(), myvector.begin()+4);

	std::cout << "sort : ";
	std::for_each(myvector.begin(), myvector.end(), print<int>);
	std::cout << "\n";



	return (0);
}