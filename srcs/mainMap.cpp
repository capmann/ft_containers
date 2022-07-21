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

	std::cout << cyan << "======= TESTING MAP FEATURES =======" << def << std::endl;

	std::cout << std::endl;

	std::cout << magenta << "======= Creating a map: Is map empty? =======" << def << std::endl;
	ft::map<char, int> map;

	if (map.empty())
		std::cout << green << "yes" << def << std::endl;
	else std::cout << red << "no" << def << std::endl;

	std::cout << magenta << "======= Inserting 25 new elements: Is map empty? =======" << def << std::endl;

	ft::map<char,int>::iterator itmap;

	map.insert(ft::pair<char, int>('b', 2));
	map.insert(ft::pair<char, int>('a', 1));

	if (map.empty())
		std::cout << green << "yes" << def << std::endl;
	else std::cout << red << "no" << def << std::endl;

	int inini = 2;
	for (char c = 'c'; c != 'z'; c++)
		map[c] = inini++;	

	std::cout << "Size of the map is " << map.size() << std::endl;

	std::cout << magenta << "======= Displaying all the objects =======" << def << std::endl;

	for (itmap = map.begin(); itmap!=map.end(); ++itmap)
    	std::cout << itmap->first << " => " << itmap->second << '\n';

	std::cout << magenta << "======= Check lower bound of b =======" << def << std::endl;

	itmap = map.lower_bound('b');
    std::cout << itmap->first << " => " << itmap->second << '\n';

	std::cout << magenta << "======= Check upper bound of b =======" << def << std::endl;

	itmap = map.upper_bound('b');
    std::cout << itmap->first << " => " << itmap->second << '\n';

	std::cout << magenta << "======= Creating a new map from tje previous one, without the a =======" << def << std::endl;

	ft::map<char, int> map_two;

	itmap = map.begin();
	++itmap;
	ft::map<char,int>::iterator ite;
	ite = map.end();

	map_two.insert(itmap, ite);

	for (itmap = map_two.begin(); itmap!=map_two.end(); ++itmap)
    	std::cout << itmap->first << " => " << itmap->second << '\n';

	std::cout << magenta << "======= Inserting a new element z =======" << def << std::endl;

	map_two.insert(ft::pair<char, int>('z', 26));

	for (itmap = map_two.begin(); itmap!=map_two.end(); ++itmap)
    	std::cout << itmap->first << " => " << itmap->second << '\n';

	std::cout << magenta << "======= Creating a new map to construct from iterators =======" << def << std::endl;

	itmap = map_two.begin();
	++itmap;
	ite = map_two.end();
	ft::map<char, int> map_three(itmap, ite);

  	for (itmap = map_three.begin(); itmap!=map_three.end(); ++itmap)
    	std::cout << itmap->first << " => " << itmap->second << '\n';

	std::cout << magenta << "======= Erasing e from the map =======" << def << std::endl;

	map_three.erase('e');

	std::cout << "Size of the map is " << map_three.size() << std::endl;

  	for (itmap = map_three.begin(); itmap!=map_three.end(); ++itmap)
    	std::cout << itmap->first << " => " << itmap->second << '\n';

	std::cout << magenta << "======= Erasing c to k from the map =======" << def << std::endl;

	map_three.erase(map_three.find('c'), map_three.find('k'));

	std::cout << "Size of the map is " << map_three.size() << std::endl;

  	for (itmap = map_three.begin(); itmap!=map_three.end(); ++itmap)
    	std::cout << itmap->first << " => " << itmap->second << '\n';

/*---------------------------------------------------------------------------------------------------------------------*/
	
	std::cout << std::endl;

	std::cout << cyan << "======= SUBJECT MAIN TESTS =======" << def << std::endl;

	std::cout << std::endl;	

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	ft::map<int, int> map_int;

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	ft::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
	
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
	}

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;
	
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;
	
	return 0;
}