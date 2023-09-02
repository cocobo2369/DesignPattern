#include <iostream>
#include <vector>

using namespace std;
struct Observer;

struct Subject{
public:
    virtual void notify()=0;
    virtual void subscribe(Observer * ob)=0;
    //virtual void unsubscribe();
};

struct Observer{
    virtual void update(bool order);
};



struct Subject_Cafe : public Subject{
    void notify() override;
    void subscribe(Observer* ob) override;
    //void unsubscribe() override;
    void set_order(bool order){
        this->order = order;
    }
private:
    bool order;
    vector<Observer*> oblist;
};

void Subject_Cafe::subscribe(Observer * ob){
    oblist.push_back(ob);
}

void Subject_Cafe::notify(){
    for(auto index : oblist){
        index->update(order);
    }
}

struct Observer_Customer : public Observer{
    void update(bool order) override;
};

void Observer_Customer::update(bool order){
    if(order == true){
        cout << "주문하신 커피 나왔습니다." << endl;
    }
    else{
        cout << "주문하신 커피 아직이요." << endl;
    }
}

int main(){
    Subject_Cafe cafe;
    Observer_Customer c1;

    cafe.subscribe(&c1);
    cafe.set_order(false);
    cafe.notify();

    cafe.set_order(true);
    cafe.notify();
}