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
	(void)argc;

	std::cout << cyan << "======= TESTING STACK FEATURES =======" << def << std::endl;

	std::cout << std::endl;

	std::cout << magenta << "======= Creating a stack with 2 numbers: 42 and 12 =======" << def << std::endl;

	ft::stack<int> stack;

	stack.push(42);
	stack.push(12);
	

	std::cout << "Size of the stack is " << stack.size() << std::endl;
	std::cout << "Number at the top of the stack is " << stack.top() << std::endl;

	std::cout << magenta << "======= Popping top number out =======" << def << std::endl;
	
	stack.pop();
	std::cout << "Size of the stack is " << stack.size() << std::endl;
	std::cout << "Number at the top of the stack is " << stack.top() << std::endl;

	std::cout << magenta << "======= Pushing new numbers of the stack =======" << def << std::endl;

	for (int i = 0; i != seed; i++)
		stack.push(seed + i);

	std::cout << "Size of the stack is " << stack.size() << std::endl;
	std::cout << "Number at the top of the stack is " << stack.top() << std::endl;

	std::cout << magenta << "======= Popping top number out =======" << def << std::endl;
	stack.pop();
	std::cout << "Size of the stack is " << stack.size() << std::endl;
	std::cout << "Number at the top of the stack is " << stack.top() << std::endl;

	return 0;
}