#include <bits/stdc++.h>

using namespace std;



class IObserver{
public:
    virtual ~IObserver(){
    }
    virtual void update() = 0;
};





class ISubject
{
protected:
    vector<IObserver*> observers;
public:

    virtual ~ISubject() = default;
    virtual void notifyObserver() = 0;
    void addObserver(IObserver &newOne){
        observers.push_back(&newOne);
    }
    void deleteObserver(IObserver &needToDelete){
         auto it = find(observers.begin(),observers.end(),&needToDelete);
         observers.erase(it);
    }
};




class WeatherStation : public ISubject
{
private:
    int temperatureValue;
    int averageTemperatureValue;

public:
    WeatherStation():temperatureValue(0),averageTemperatureValue(0){

    }
    void change()
    {
        temperatureValue =  rand() % 100;
        averageTemperatureValue =  rand() % 100;
        notifyObserver();
    }
    virtual void notifyObserver() override
    {
        for(auto x: observers){
            x->update();
        }
    }
    int getTemperatureValue(){
        return  temperatureValue;
    }
};

class WeatherPrint:public IObserver{
public:
    WeatherPrint(WeatherStation &parent):parent{parent}{
        parent.addObserver(*this);
    }
    virtual void update() override final{
        cout << "weather print update success : " << parent.getTemperatureValue() << endl;
    }
private:
    WeatherStation &parent;
};


int main()
{
    WeatherStation ws;
    WeatherPrint wp(ws);


    ws.change();
    ws.change();
    ws.change();
    ws.change();
    ws.change();
    cout << "***************" << endl;
    ws.deleteObserver(wp);
    ws.change();
    ws.change();



    return 0;
}
