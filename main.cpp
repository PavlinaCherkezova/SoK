#include <iostream>
#include<queue>
#include<vector>

int main()
{
    std::cout << "Hello World!\n";

	class Compaer {
	public:
		bool operator () (int f, int s) {
			return f > s;
		}
	};
	std::priority_queue<int, std::vector<int>, Compaer> pq;
	pq.push(3);
	pq.push(15);
	pq.push(7);

	std::cout<<pq.top();
	 pq.pop();
	std::cout << pq.top();
}

