#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
using namespace std;

class Observer {
public:
    virtual void update(float temperature, float humidity, float pressure) = 0;
};

class WeatherStation {
private:
    vector<Observer*> observers;  
    float temperature;
    float humidity;
    float pressure;

public:

    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) {
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notifyObservers() {
        for (Observer* observer : observers) {
            observer->update(temperature, humidity, pressure);
        }
    }

    void setWeatherData(float temp, float hum, float press) {
        temperature = temp;
        humidity = hum;
        pressure = press;
        notifyObservers();
    }
};

class PhoneDisplay : public Observer {
public:
    void update(float temperature, float humidity, float pressure) override {
        cout << "Phone Display: Weather Update!" << endl;
        cout << "Temperature: " << temperature << "°C, Humidity: " << humidity << "%, Pressure: " << pressure << " hPa" << endl;
    }
};

class DesktopDisplay : public Observer {
public:
    void update(float temperature, float humidity, float pressure) override {
        cout << "Desktop Display: Weather Update!" << endl;
        cout << "Temperature: " << temperature << "°C, Humidity: " << humidity << "%, Pressure: " << pressure << " hPa" << endl;
    }
};

int main() {
    
    WeatherStation weatherStation;

    PhoneDisplay phoneDisplay;
    DesktopDisplay desktopDisplay;

    weatherStation.addObserver(&phoneDisplay);
    weatherStation.addObserver(&desktopDisplay);

    weatherStation.setWeatherData(22.5, 65.0, 1013.2);
    weatherStation.setWeatherData(23.0, 60.0, 1012.8);

    weatherStation.removeObserver(&desktopDisplay);

    weatherStation.setWeatherData(24.5, 55.0, 1010.0);

}
