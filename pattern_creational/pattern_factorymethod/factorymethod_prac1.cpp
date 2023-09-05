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
    product * Icreate(string type){
        return this->createProduct(type);
    }
private:
    virtual product * createProduct(string type); //factorymethod
};

class concFactory : public absFactory{
public :
    product * createProduct(string type) override{
        if(type == "111")
            return new product1();
        else if(type == "222")
            return new product2();
        else 
            return NULL;   
    }
};

int main(){
    concFactory factory;
    product1 * a = (product1 *)factory.Icreate("111");
    product2 * b = (product2 *)factory.Icreate("222");

    delete a;
    delete b;
}