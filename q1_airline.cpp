#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Passenger class to store passenger details
class Passenger {
public:
    string name;
    Passenger(string name) {
        this->name = name;
    }
};

// Flight class to store flight details and passengers
class Flight {
public:
    string number;
    int capacity;
    vector<Passenger*> passengers;

    Flight(string number, int capacity) {
        this->number = number;
        this->capacity = capacity;
    }

    // Add a passenger to the flight
    void addPassenger(Passenger* passenger) {
        if (passengers.size() >= capacity) {
            cout << "Sorry, this flight is full.\n";
            return;
        }
        passengers.push_back(passenger);
        cout << "Passenger " << passenger->name << " added to flight " << number << ".\n";
    }

    // Check if a passenger is on the flight
    bool hasPassenger(string name) {
        for (int i = 0; i < passengers.size(); i++) {
            if (passengers[i]->name == name) {
                return true;
            }
        }
        return false;
    }

    // Display all passengers on the flight
    void displayPassengers() {
        cout << "Passengers on flight " << number << ":\n";
        for (int i = 0; i < passengers.size(); i++) {
            cout << "- " << passengers[i]->name << endl;
        }
    }
};

// Airline class to manage flights and passengers
class Airline {
public:
    vector<Flight*> flights;

    // Add a flight to the airline
    void addFlight(string number, int capacity) {
        Flight* flight = new Flight(number, capacity);
        flights.push_back(flight);
        cout << "Flight " << number << " added with capacity " << capacity << ".\n";
    }

    // Get a flight by number
    Flight* getFlight(string number) {
        for (int i = 0; i < flights.size(); i++) {
            if (flights[i]->number == number) {
                return flights[i];
            }
        }
        return nullptr;
    }

    // Reserve a seat on a flight for a passenger
    void reserveSeat(string flightNumber, string passengerName) {
        Flight* flight = getFlight(flightNumber);
        if (flight == nullptr) {
            cout << "Flight " << flightNumber << " not found.\n";
            return;
        }
        if (flight->hasPassenger(passengerName)) {
            cout << "Passenger " << passengerName << " already on flight " << flightNumber << ".\n";
            return;
        }
        Passenger* passenger = new Passenger(passengerName);
        flight->addPassenger(passenger);
    }

    
    // Cancel a reservation for a passenger on a flight
void cancelReservation(string flightNumber, string passengerName) {
    Flight* flight = getFlight(flightNumber);
    if (flight == nullptr) {
        cout << "Flight " << flightNumber << " not found.\n";
        return;
    }
    for (int i = 0; i < flight->passengers.size(); i++) {
        if (flight->passengers[i]->name == passengerName) {
            delete flight->passengers[i];
            flight->passengers.erase(flight->passengers.begin() + i);
            cout << "Reservation for passenger " << passengerName << " on flight " << flightNumber << " cancelled.\n";
            return;
        }
    }
    cout << "Passenger " << passengerName << " not found on flight " << flightNumber << ".\n";
}

// Check if a flight has seats available
bool hasSeatsAvailable(string flightNumber){
    Flight* flight = getFlight(flightNumber);
    if (flight == nullptr) {
        cout << "Flight " << flightNumber << " not found.\n";
        return false;
    }
    return flight->passengers.size() < flight->capacity;
}

void displayFlights()
{
    for(auto x: flights)
    {
        cout<<"Flight :"<<x -> number<<" with seat :"<<x -> capacity<<endl;
    }
}

void displayFlightInfo(string flightNumber)
{
    Flight* flight = getFlight(flightNumber);
    if (flight == nullptr) {
        cout << "Flight " << flightNumber << " not found.\n";
        return;
    }
    
    cout<<"Flight "<<flightNumber<<" has :"<< flight->capacity - flight->passengers.size() <<" seats.\n";
    if(flight->passengers.size() == 0)
    return;
    cout<<"Flight "<<flightNumber<<" has reservations by: \n";
    
    for(auto x: flight->passengers)
    {
        cout<<x->name<<endl;
    }
}

void checkTicket(string flightNumber, string passengerName)
{
     Flight* flight = getFlight(flightNumber);
    if (flight == nullptr) {
        cout << "Flight " << flightNumber << " not found.\n";
        return;
    }
    for (int i = 0; i < flight->passengers.size(); i++) {
        if (flight->passengers[i]->name == passengerName) {
            cout<<"Ticket for "<<passengerName<<" is reserved. \n";
            return;
        }
    }
    cout << "Passenger " << passengerName << " not found on flight " << flightNumber << ".\n";
}
};


int main() {
    Airline airline;

    // Add some flights
    int choice = 0;
    while (choice != 7) {
        // Display menu options
        cout<<"\n";
        cout<<"Please select an option:\n";
        cout<<"1. Add Flight\n";
        cout<<"2. Reserve a seat\n";
        cout<<"3. Cancel a reservation\n";
        cout<<"4. Check flight availability\n";
        cout<<"5. Display all flights\n";
        cout<<"6. Display flight information\n";
        cout<<"7. Check reservation\n";
        cout<<"8. Quit\n";
        cout<<"Your choice: ";
        cin>>choice;

        switch (choice) {
            case 1: {
                    //Add Flight
                    cout<<"Enter flight number: ";
                    string number;
                    cin>>number;
                    cout<<"Enter flight capacity: ";
                    int cap;
                    cin>>cap;
                    airline.addFlight(number, cap);
                    break;
            }
            case 2: {
                // Reserve a seat
                string flightNumber, passengerName;
                cout<<"Enter flight number: ";
                cin>>flightNumber;
                cout<<"Enter passenger name: ";
                cin>>passengerName;
                airline.reserveSeat(flightNumber, passengerName);
                break;
            }

            case 3: {
                    //Cancel Reservation
                    string flightNumber, passengerName;
                    cout<<"Enter flight number: ";
                    cin>>flightNumber;
                    cout<<"Enter passenger name: ";
                    cin>>passengerName;
                    airline.cancelReservation(flightNumber, passengerName);
                    break;
            }

            case 4: {
                    //Check if seats are avaiable
                    string flightNumber;
                    cout << "Enter flight number: ";
                    cin >> flightNumber;

                    if (airline.hasSeatsAvailable(flightNumber)) {
                        cout << "Seats are available.\n";
                    } else{
                        cout << "Sorry, the flight is not available.\n";
                    }
                    break;
            }

            case 5: {
                // Display flight information
                airline.displayFlights();
                break;
            }

            case 6:{
                    //Display specific flight information
                    string flightNumber;
                    cout<<"Enter Flight Number to be checked: ";
                    cin>>flightNumber;
                    airline.displayFlightInfo(flightNumber);
                    break;
            }

            case 7:{
                    //Checking reservation
                    string flightNumber, passengerName;
                    cout<<"Enter flight number : ";
                    cin>>flightNumber;
                    cout<<"Enter passenger name: ";
                    cin>>passengerName;
                    airline.checkTicket(flightNumber, passengerName);
                    break;
            }

            case 8: cout << "Exitting...\n";
                    break;
           

            default: cout << "Invalid.\n";
                     break;
            
        }
    }

    return 0;
}


