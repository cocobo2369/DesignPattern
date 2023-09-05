#include <iostream>
#include <string>
using namespace std;

class product{
public:
    product(){
        cout << "product" << endl;
    }
    ~product(){
        cout << "delete product" << endl;
    }
};

class product1 : public product{
public:
    product1(){
        cout << "product1" << endl;
    }
    ~product1(){
        cout << "delete product1" << endl;
    }
};

class product2 : public product{
public:
    product2(){
        cout << "product2" << endl;
    }
    ~product2(){
        cout << "delete product2" << endl;
    }
};

class absFactory{
public:
    virtual product * createProduct(); //factorymethod
};

class concFactory1 : public absFactory{
public :
    product * createProduct() override{
        cout << "specific process for product1" << endl;
        return new product1();
    }
};

class concFactory2 : public absFactory{
public :
    product * createProduct() override{
        cout << "specific process for product2" << endl;
        return new product2();
    }
};


int main(){
    concFactory1 factory1;
    concFactory2 factory2;
    cout << "====[make product1]====" << endl;
    product1 * a = (product1 *)factory1.createProduct();
    cout << "====[make product2]====" << endl;
    product2 * b = (product2 *)factory2.createProduct();

    cout << "====[delete product1]====" << endl;
    delete a;
    cout << "====[delete product2]====" << endl;
    delete b;
}