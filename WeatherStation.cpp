#include <iostream>
#include <vector>
#include <string>

using namespace std;

    
//=========================================================================    
class Observer {
public:
	virtual void update(float temp, float humidity, float pressure) = 0;
};

//=========================================================================
class DisplayElement {
public:
	 virtual void display() = 0;
};

//=========================================================================
class Subject {
public:
	virtual void registerObserver(Observer* o) = 0;
	virtual void removeObserver(Observer* o) = 0;
	virtual void notifyObservers() = 0;
};

//=========================================================================
class WeatherData: public Subject {
private:
	vector<Observer*> observers;
	float temperature;
	float humidity;
	float pressure;
public:
	virtual void registerObserver(Observer* o) {
		observers.push_back(o);
	}

	virtual void removeObserver(Observer* o ) {
		vector<Observer*>::iterator iter = find(observers.begin(), observers.end(), o);
		if (iter != observers.end()) {
			observers.erase(iter);
		}
	}

	virtual void notifyObservers() {
		for (int i = 0; i < observers.size(); i++ ) {
			observers[i]->update(temperature, humidity, pressure);
		}
	}

	void measurementsChanged() {
		notifyObservers();
	}

	void setMeasurements(float temperature, float humidity, float pressure) {
		this->temperature = temperature;
		this->humidity = humidity;
		this->pressure = pressure;
		measurementsChanged();
	}
};


//=========================================================================
class CurrentConditionDisplay: public Observer, DisplayElement {
private:
	float temperature;
	float humidity;
	Subject *weatherData;

public:
	CurrentConditionDisplay(Subject *weatherData) {
		this->weatherData = weatherData;
		weatherData->registerObserver(this);
	}

	virtual void update(float temperature, float humidity, float pressure) {
		this->temperature = temperature;
		this->humidity = humidity;
		display();
	}

	virtual void display() {
		cout<<"Current conditions: " << temperature << "F degrees and" << humidity << "% humidity" << endl;
	}


};

//=========================================================================

class WeatherStation {
public:
	 void station() {
		WeatherData *weatherData = new WeatherData();
		CurrentConditionDisplay* currentConditionDiaplay = new CurrentConditionDisplay(weatherData);
		weatherData->setMeasurements(80, 65, 30.4f);
		weatherData->setMeasurements(82, 70, 29.2f);
		weatherData->setMeasurements(78, 90, 29.2f);
	}
};

//=========================================================================
 int main() {

 	WeatherStation* weatherStation = new WeatherStation();
 	weatherStation -> station();

 	return 0;
 }












