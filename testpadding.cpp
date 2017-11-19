#include <iostream>
using namespace std;

typedef struct Sa{
    int p;
    char r;
    int k;
}a;

typedef struct Sb{
    char m;
    char n;
    char o;
}b;

int main(){
    a oa;
    b ob;
    std::cout << "the size of a is " << sizeof(oa) << endl
                << "the size of b is " << sizeof(ob) << endl;
}