# 정리
1. client는 product를 직접생성하지 않고 absFactory로부터 의존성주입받았다.

2. absFactoryd 역시 product를 직접생성하지 않고 concFactory로부터 의존성 주입을 받았다.
3. 이 떄 의존성 주입은 함수의 반환으로 이루어진다.

4. factory --> abstract factory + concrete factories 로 바꾸어 concrete factory로 생성을 위임했다는 것이 중요하다!
abstract factory로 concrete factory의 함수 호출로 product를 생성할 수 있다.

5. factorymethod로 사용하는 함수는 상속으로써 구현하는 것이 아니다.

```c++
class absFactory{
public:
    virtual product * factorymethod();
};

class concFactory1 : absFactory{
public :
    product * factorymethod() override{
        return new product1();
    }

};

class concFactory2 : absFactory{
public :
    product * factorymethod() override{
        return new product2();
    }
};

int main(){
    concFactory1 cF1;
    product * A = cF1.factorymethod();

}
```

- abstract factory는 인터페이스로서 역할하여 client가 사용한다.
- abstract factory는 product 와 느슨한 결합을 이룬다.
    - 대신 concrete factory가 product와 강한 결합을 이룬다.
    - 추상은 느슨한 결합으로, 구현부가 강한 결합이 되도록했다.


- product 군
```c++
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
```
#### case 1 parameter
- product 군을 생성하는 factory
    - 생성하려는 product 군의 개별 product를 concrete factory 하나에서 관리할 때
    - 장점 : null-채워넣기
    - 단점 : null-채워넣기
    - factorymethod pattern 임을 보는 방법
        1) virtual로 선언된 함수 --> factory method
            - parameter : type 포함
            - return : product 포함
        2) virtual로 선언된 함수를 호출 --> client에 제공되는 interface
            - parameter : type 포함
            - return : product 포함
```c++
class absFactory{
public:
    product * Icreate(string type){ //interface
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
```

```c++
int main(){
    concFactory factory;
    product1 * a = (product1 *)factory.Icreate("111");
    product2 * b = (product2 *)factory.Icreate("222");

    delete a;
    delete b;
}
```

#### case 2 class
- product 군을 생성하는 factory
    - 생성하려는 product 군의 개별 product마다 concrete factory 를 만들 때
    - 장점 : null-채워넣기
    - 단점 : null-채워넣기
    - factorymethod pattern 임을 보는 방법
        1) virtual로 선언된 함수 --> factory method
            - parameter : type 포함
            - return : product 포함
        2) product 종류만큼 factory가 있다.

```c++
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
```

```c++
int main(){
    concFactory1 factory1;
    concFactory2 factory2;
    product1 * a = (product1 *)factory1.createProduct();
    product2 * b = (product2 *)factory2.createProduct();

    delete a;
    delete b;
}
```
product 군이 2개 이상일 때 factorymetod 하나에 모두 포함할 수 있을까?
안될 것이다.
왜냐하면 abstract facatory에 product1,2 군을 모두 만든다고 가정하면
추상메서드인 factorymethod가 두개 필요하다.

이 때 concrete class도 두개 필요하게 되고
product1에 대한 concrete class에 product2의 factory method를 만들어야하고
product2에 대한 concrete class에 product1의 factory method를 만들어야한다.

정리하면 factory를 추상화한 abstract factory는 
여러 product 군에 대한 concrete factory를 
만들려는 다형성 측면에서 추상과 구현을 분리한 것이 아니라
말그대로 변하지 않는 추상과 수정이 필요한 구현을 구분한 OCP 를 달성하기 위한 분리이다.

