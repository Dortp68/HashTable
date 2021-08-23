#include "HashTable.h"
#include "HashTable.cpp"


int main()
{
    HashTable<int> test(10);

    test.Add("qwe", 100);
    test.Add("qwr", 101);
    test.Add("qwt", 102);
    test.Add("zx", 10);
    test.Info();
    std::cout << test["qwe"] << std::endl;
    test["qwe"] = 999;
    std::cout << test["qwe"] << std::endl;
    HashTable<int> copy;
    copy = test;
    copy.Info();
    HashTable<int> move_;
    move_ = std::move(copy);
    move_.Info();
    HashTable<int> move1 = std::move(move_);
    move1.Info();
    move_.Info();
    //move_.Getsize();
    copy.Info();
    //test.Clear();
    //copy.Info();
}
