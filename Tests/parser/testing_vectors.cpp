#include <iostream>
#include <vector>

template<typename T>
void print(T const & xs)
{
    std::cout << "[ ";
    for(auto const & x : xs) {
        std::cout << x << ' ';
    }
    std::cout << "]\n";
}

int main(int argc, char** argv) {
    std::vector<int> list;

    list.push_back(2);
    list.push_back(9);
    list.push_back(5);
    list.push_back(6);

    print(list);
    auto back = list.at(list.size()-1);
    list.pop_back();
    std::cout << back << std::endl;
    print(list);
}
