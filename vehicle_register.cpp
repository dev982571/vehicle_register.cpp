#include <iostream>
using namespace std;

class Vehicle {
protected:
    int id, year;
    string company, model;
    static int totalVehicles;

public:
    Vehicle(int i=0,string c="",string m="",int y=0)
        : id(i), company(c), model(m), year(y) { totalVehicles++; }

    virtual ~Vehicle(){}

    int getId(){ return id; }
    void setId(int i){ id=i; }

    virtual void display(){
        cout<<"ID:"<<id<<" "<<company<<" "<<model<<" "<<year;
    }

    static void count(){
        cout<<"\nTotal Vehicles = "<<totalVehicles<<endl;
    }
};
int Vehicle::totalVehicles=0;

class Car : public Vehicle{
protected:
    string fuelType;
public:
    Car(int i=0,string c="",string m="",int y=0,string f="")
        : Vehicle(i,c,m,y), fuelType(f) {}

    void display() override{
        Vehicle::display();
        cout<<" Fuel:"<<fuelType;
    }
};

class ElectricCar : public Car{
protected:
    int battery;
public:
    ElectricCar(int i,string c,string m,int y,string f,int b)
        : Car(i,c,m,y,f), battery(b) {}

    void display() override{
        Car::display();
        cout<<" Battery:"<<battery;
    }
};

class Aircraft{
protected:
    int range;
public:
    Aircraft(int r=0):range(r){}
};

class FlyingCar : public Car, public Aircraft{
public:
    FlyingCar(int i,string c,string m,int y,string f,int r)
        : Car(i,c,m,y,f), Aircraft(r) {}

    void display(){
        Car::display();
        cout<<" Range:"<<range;
    }
};

class SportsCar : public ElectricCar{
    int topSpeed;
public:
    SportsCar(int i,string c,string m,int y,string f,int b,int s)
        : ElectricCar(i,c,m,y,f,b), topSpeed(s) {}

    void display() override{
        ElectricCar::display();
        cout<<" Speed:"<<topSpeed;
    }
};
class Sedan : public Car{
public:
    Sedan(int i,string c,string m,int y,string f)
        : Car(i,c,m,y,f) {}
};

class SUV : public Car{
public:
    SUV(int i,string c,string m,int y,string f)
        : Car(i,c,m,y,f) {}
};

class VehicleRegistry{
    Vehicle* v[10];
    int n=0;
public:
    void add(Vehicle* obj){ v[n++]=obj; }

    void show(){
        for(int i=0;i<n;i++){
            v[i]->display();
            cout<<endl;
        }
    }

    void search(int id){
        for(int i=0;i<n;i++)
            if(v[i]->getId()==id)
                v[i]->display();
    }
};

int main(){
    VehicleRegistry vr;

    vr.add(new Car(1,"Toyota","Corolla",2023,"Petrol"));
    vr.add(new ElectricCar(2,"Tesla","Model3",2024,"Electric",75));
    vr.add(new SportsCar(3,"Porsche","Taycan",2025,"Electric",90,300));

    vr.show();
    Vehicle::count();

    cout<<"\nSearch:\n";
    vr.search(2);

    return 0;
}