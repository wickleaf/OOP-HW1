#include <iostream>
#include <string>
#include <variant>

using namespace std;

// SAQIB REHMAN (sr10128)

// Constants
const int MAX_RIDES = 100;
const int MAX_DRIVERS = 50;
const int START_RIDE_ID = 100001;

// Struct Definition
struct Ride {
    string riderName;
    int rideID;
    string driverName;
    string pickupLocation;
    string dropoffLocation;
    double fare;
    string status;
    double distance; // "Ongoing", "Completed", "Cancelled"
};

// Global Variables
Ride rideDetails[MAX_RIDES];
int rideCount = 0; // Keeps track of total rides
string Drivers[MAX_DRIVERS];
int driverCount = 0; // Keeps track of total drivers
int rideID = 100001; //To use later on for assigning and incrementing
// ================= Function Definitions =================

int IsAvailable(string driverName, Ride rides[]){
    // TODO: Searches through the array 
    //       Checks if the given driverName has an Ongoing ride
    //       If the given driverName has an Ongoing ride returns 1, otherwise returns 0
    bool registered = false;
    for(int i=0; i<driverCount;i++){
        if(Drivers[i]==driverName){
            registered = true;
        }
    }
    bool ongoing = false;
    for (int i=0; i<driverCount; i++){
        if ((rides[i].driverName == driverName)&&(rideDetails[i].status == "Ongoing")){
            ongoing = true;
        } 
        else if(rides[i].driverName== driverName){
            //cout<<"works";
            ongoing = false;
        } //Finds driver and checks if they have an ongoing ride
    }
    if(ongoing==false){
        return 0;
    }
    else{
        return 1;
    }
    
    
}

int GetFare(int distance){
    //TODO: Calculate and return the fare based on the given scheme
    //      Distance < 2KM : 50 + (50 * distance)
    //      2KM < Distance < 5KM : 150 + (80 * (distance - 2)) 
    //      Distance > 5KM : 390 + (100 * (distance - 5))
    if (distance<2){
        double fare = 50+(50*distance);
        return fare;
    }
    else if (distance > 2 && distance < 5){
        double fare = 150+(80*(distance-2));
        return fare;
    }
    else{
        double fare = 390 + (100*(distance-5));
        return fare;
    }
    

 }
    

bool inStruct(Ride rides[],string toGet,const variant<int,string,double>&value){
    for(int i = 0; i<rideCount; i++){
        if(toGet=="rideID"){
            if(get<int>(value)==rides[i].rideID){
                return true;
            }   
        }
        else if(toGet=="fare"){
            if(get<double>(value)==rides[i].fare){
                return true;
            }   
        }
        if(toGet=="distance"){
            if(get<double>(value)==rides[i].distance){
                return true;
            }   
        }
        if(toGet=="driver"){
            if(get<string>(value)==rides[i].driverName){
                return true;
            }   
        }
        if(toGet=="rider"){
            if(get<string>(value)==rides[i].riderName){
                return true;
            }   
        }
        if(toGet=="status"){
            if(get<string>(value)==rides[i].status){
                return true;
            }   
        }
    }
    return false;
}

// Prompts user for ride details and returns a Ride struct
Ride BookRide(string name) {
    // TODO: Prompt user for pickup, drop-off, distance
    //       Displays all available drivers. Hint use the IsAvailable function and the Drivers array.
    //       Prompts the user to select a driver
    //       Calculates the fare by calling the GetFare function.
    //       Set ride status to "Ongoing" and generate Ride ID
    //       If there is no driver avaliable then output an error message, generate a Ride ID, set ride status to "Cancelled" and driverName to ""
    Ride newRide;
    string *ptr = Drivers;
    string pickup;
    string dropOff;
    double distance;

    if (rideCount==MAX_RIDES){
        cout << "Sorry you cannot book a ride :(";
        return newRide;
    }

    cout << "Enter pickup location: "; cin>> pickup; cout<<"Enter drop-off location: "; cin>> dropOff; 
    do{
        cout<<"Enter Distance: "; cin>>distance;
    }
    while(distance<0.0);
    bool riderAval = false;
    int avalDrivers[driverCount]; //Will use to validate user input through indexing
    int avalCount=0;
    for(int i=0; i<driverCount; i++, ++ptr){
        if (IsAvailable(*ptr, rideDetails)==0){
            riderAval=true;
            avalDrivers[avalCount]=avalCount+1;
            cout <<i<<") "<<*ptr<<endl;
            avalCount++;
        }
    }
    if(rideID==START_RIDE_ID){
            newRide.rideID=rideID;
        }
    else{
        newRide.rideID = ++rideID;
        }
    if(riderAval==false){
        cout << "No driver is available at the moment :("<<endl;
        newRide.status="Cancelled";
        newRide.driverName="";
        rideDetails[rideCount]=newRide;
        rideCount++;
        return newRide;
    }
    int driver;
    while(true){
        cout<<"Pick a driver: "; cin>> driver;
        if (driver >= avalDrivers[0] && driver <= avalDrivers[avalCount-1]) break;
        else{
            cout<<"Index out of range"<<endl;
        }

    }
    
    double fare = GetFare(distance);
    cout << "Your fare will be: "<<fare<< endl;

    newRide.status="Ongoing"; newRide.driverName= driver; newRide.distance=distance; 
    newRide.dropoffLocation=dropOff; newRide.pickupLocation=pickup; newRide.fare=fare; 
    newRide.riderName=name;

    rideDetails[rideCount]=newRide;
    rideCount++;

    return newRide;
}

// Displays rides that match the given name (rider or driver)
void ViewRides(string name, Ride rides[], string status, string mode) {
    // TODO: Loop through the array and print rides where name matches riderName or driverName
    //       Displays all rides for that name regardless of status if status is ""
    //       Displays rides for that name and status if a status value was passed
    if(mode=="Driver"){
        if(status == ""){
            for(int i = 0; i<rideCount; i++){
                if(name == rides[i].driverName){
                    cout<<"Driver Name: "<< rides[i].driverName<<endl;
                    cout<<"Rider Name: "<< rides[i].riderName<<endl;
                    cout<<"Ride ID: "<< rides[i].rideID<<endl;
                    cout<<"Pickup Location: "<< rides[i].pickupLocation<<endl;
                    cout<<"Dropoff Location: "<< rides[i].dropoffLocation<<endl;
                    cout<<"Distance: "<< rides[i].distance<<endl;
                    cout<<"Fare: "<< rides[i].fare<<endl;
                    cout<<"Status: "<< rides[i].status<<endl;
                }
            }
        }
        else{
            for(int i = 0; i<rideCount; i++){
                if((name == rides[i].driverName)&& rides[i].status==status){
                    cout<<"Driver Name: "<< rides[i].driverName<<endl;
                    cout<<"Rider Name: "<< rides[i].riderName<<endl;
                    cout<<"Ride ID: "<< rides[i].rideID<<endl;
                    cout<<"Pickup Location: "<< rides[i].pickupLocation<<endl;
                    cout<<"Dropoff Location: "<< rides[i].dropoffLocation<<endl;
                    cout<<"Distance: "<< rides[i].distance<<endl;
                    cout<<"Fare: "<< rides[i].fare<<endl;
                    cout<<"Status: "<< rides[i].status<<endl;
                }
            }
        }
    }
    else{
        if(status == ""){
            for(int i = 0; i<rideCount; i++){
                if(name == rides[i].riderName){
                    cout<<"Driver Name: "<< rides[i].driverName<<endl;
                    cout<<"Rider Name: "<< rides[i].riderName<<endl;
                    cout<<"Ride ID: "<< rides[i].rideID<<endl;
                    cout<<"Pickup Location: "<< rides[i].pickupLocation<<endl;
                    cout<<"Dropoff Location: "<< rides[i].dropoffLocation<<endl;
                    cout<<"Distance: "<< rides[i].distance<<endl;
                    cout<<"Fare: "<< rides[i].fare<<endl;
                    cout<<"Status: "<< rides[i].status<<endl;
                }
            }
        }
        else{
            for(int i = 0; i<rideCount; i++){
                if((name == rides[i].riderName)&& rides[i].status==status){
                    cout<<"Driver Name: "<< rides[i].driverName<<endl;
                    cout<<"Rider Name: "<< rides[i].riderName<<endl;
                    cout<<"Ride ID: "<< rides[i].rideID<<endl;
                    cout<<"Pickup Location: "<< rides[i].pickupLocation<<endl;
                    cout<<"Dropoff Location: "<< rides[i].dropoffLocation<<endl;
                    cout<<"Distance: "<< rides[i].distance<<endl;
                    cout<<"Fare: "<< rides[i].fare<<endl;
                    cout<<"Status: "<< rides[i].status<<endl;
                }
            }
        }
    }
    
}

// Displays ongoing rides for the user, prompts for Ride ID, and returns it
int ChangeStatus(string name, Ride rides[], string mode) {
    // TODO: Show ongoing rides for the name. Hint: Call ViewRides and use the third parameter 
    //       Ask user to enter the Ride ID to update
    //       Return the Ride ID so status can be updated in main
    ViewRides(name,rides,"Ongoing",mode);
    int userRide;
    while(true){
        cout << "Enter ride ID to be updated: ";
        cin.ignore();
        cin >> userRide;
        if(inStruct(rides,"rideID",userRide)){
            return userRide;
        }
        else{
            cout << "Invalid rideID; please try again"<<endl;
            cin.clear();
        }
    }
    
    return -1; // Placeholder
}

// Sums up the fare of all rides assigned to a driver
double CalculateTotal(string driverName, Ride rides[]) {
    // TODO: Add up fares of rides where driverName matches and status is "Completed"
    double total =0 ;
    for(int i=0; i<rideCount; i++){
        if(rides[i].driverName==driverName || rides[i].status=="Completed"){
            total = rides[i].fare + total;
        }
    }
    return total;
}

// ================= Main Function =================

int main() {
    // TODO:
    // - Display main menu
    // - Ask the user if they are a Rider (1) or Driver (2)
    // - Prompt for name
    // - If the user is a Driver and the name is not in the Drivers list add it to the list
    // - Based on role, display the appropriate menu
    // - Use the provided functions to implement menu options
    // - Ensure ride count does not exceed MAX_RIDES
    // - Validate menu inputs
    bool returnMenu = true;
    do{
    cout<< "Welcome to the Ride Booking Simulation program! Are you a Rider (1) or a Driver (2)? Enter your role: ";
    int x;
    while(true){
        cin >> x;
        if(x<1 && x>2){
            cout << "Please input a valid role!"<<endl;
        }
        else{
            break;
        }
    }

    if(x==1){
        string userRider;
        cout << "Please enter your name: ";
        cin>> userRider;
        int userInput;
        BookRide(userRider);
        
    }
    else if(x==2){
        string userDriver;
        cout << "Please enter your name: ";
        cin >> userDriver;
        bool exists = false;
        for(int i =0; i<driverCount; i++){
            if (Drivers[i]== userDriver){
                exists = true;
            }
        }
        if (exists == false){
            Drivers[driverCount+1] = userDriver;
            //driverCount++;
        }
        int userInput;
        cin >> userInput;
        if(userInput == 1){
            returnMenu==true;
        }
    }
}while(returnMenu==true);
    
    
    return 0;
}
