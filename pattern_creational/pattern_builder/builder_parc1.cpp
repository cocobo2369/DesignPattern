#include <iostream>
#include <string>
using namespace std;
class Result{
private :
    string partsA;
    string partsB;
    string partsC;
public:
    void setPartsA(const string& parts) {
        this->partsA = parts;
    }

    void setPartsB(const string& parts) {
        this->partsB = parts;
    }

    void setPartsC(const string& parts) {
        this->partsC = parts;
    }

    void show(){
        cout << partsA << partsB << partsC << endl;
    }
};
class BuilderInterface {
public:
    virtual void setPartsA(const string& parts) = 0;
    virtual void setPartsB(const string& parts) = 0;
    virtual void setPartsC(const string& parts) = 0;
    virtual Result * build() = 0;
};

class BuilderConcrete : public BuilderInterface {
private :
    Result * result;
public:
    BuilderConcrete(){
        result = new Result();
    }
    void setPartsA(const string& parts) override {
        result->setPartsA(parts);
    }

    void setPartsB(const string& parts) override {
        result->setPartsB(parts);
    }

    void setPartsC(const string& parts) override {
        result->setPartsC(parts);
    }

    Result * build() override{
        return result;
    }
};

class Director {
private:
    BuilderConcrete* builder;

public:
    Director(BuilderConcrete* b) : builder(b) {}

    Result* buildAA() {
        builder->setPartsA("Part A for AA");
        builder->setPartsC("Part C for AA");

        return builder->build();
    }

    Result* buildBB() {
        builder->setPartsC("Part C for BB");
        return builder->build();
    }
};

int main() {
    BuilderConcrete builder;
    Director director(&builder);

    Result * result = director.buildAA();
    result->show();
    return 0;
}