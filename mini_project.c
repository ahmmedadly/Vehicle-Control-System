/*************************************************************************************************************
 =============================================================================================================
 Name        :  mini_project 1
 Author      :  AHMED ADLY
 date        :  27/12/2023
 Description :  Vehicle Control system project
 =============================================================================================================
 *************************************************************************************************************/
#include <stdio.h>

// Enumeration for ON/OFF states
typedef enum {
    OFF,
	ON
} State;

// Structure to hold the vehicle info
typedef struct {
    State engine;                       // Engine state
    State ac;                           // AC state
    int vehicleSpeed;                   // Vehicle speed
    int roomTemperature;                // Room temperature
    State engineTemperatureController;  // Engine Temperature Controller state
    int engineTemperature;              // Engine temperature
} Vehicle;

// Define to conditionally compile engine temperature controller
#define WITH_ENGINE_TEMP_CONTROLLER 1

// Function to display the current state of the vehicle
void displayVehicleState(const Vehicle *vehicle) {
    printf("\n\nCurrent Vehicle State:\n\n");
    printf("Engine state: %s\n", vehicle->engine ? "ON" : "OFF");
    printf("AC: %s\n", vehicle->ac ? "ON" : "OFF");
    printf("Vehicle Speed: %d km/hr\n", vehicle->vehicleSpeed);
    printf("Room Temperature: %d\n", vehicle->roomTemperature);
    printf("Engine Temperature Controller State: %s\n", vehicle->engineTemperatureController ? "ON" : "OFF");
    printf("Engine Temperature: %d\n\n", vehicle->engineTemperature);
}

int main() {

    Vehicle vehicle = {OFF, OFF, 0, 25, OFF, 90};

    char choice;
    char trafficLight;
    int roomTempSensor, engineTempSensor;

    // Main loop for vehicle control system
    while (1) {
    	 // Welcome message and main loop for the system options
        printf("\n\n================================== WELCOME ==================================\n\n");
        printf("\nMenu:\n");
        printf("a. Turn on the vehicle engine\n");
        printf("b. Turn off the vehicle engine\n");
        printf("c. Quit the system\n");
        printf("Please enter your choice: ");
        fflush(stdout);
        scanf(" %c", &choice);

        switch (choice) { // Switch based on the choice made from the system options menu
            case 'a':
                vehicle.engine = ON; // Turning on the vehicle engine
                printf("\nSensors set menu\n\n");
                while (vehicle.engine) { // Loop while the engine is ON
                    char choice_on;
                    printf("a. Turn off the engine \n");
                    printf("b. Set the traffic light color. \n");
                    printf("c. Set the room temperature (Temperature Sensor) \n");
                    printf("d. Set the engine temperature (Engine Temperature Sensor)\n\n");
                    printf("Please enter your choice: ");
                    fflush(stdout);
                    scanf(" %c", &choice_on); // Taking input to set the sensor options

                    switch (choice_on) {
                        case 'a':
                            vehicle.engine = OFF; // Turning off the vehicle engine
                            break;

                        case 'b':
                            // Handling traffic light sensor input
                            printf("Set the traffic light color. \n");
                            fflush(stdout);
                            scanf(" %c", &trafficLight);
                            if (trafficLight == 'G' || trafficLight == 'g') {
                                vehicle.vehicleSpeed = 100; // Set vehicle speed for green traffic light
                            } else if (trafficLight == 'O' || trafficLight == 'o') {
                                vehicle.vehicleSpeed = 30; // Set vehicle speed for orange traffic light
        #ifdef WITH_ENGINE_TEMP_CONTROLLER
                                // Updating temperatures if WITH_ENGINE_TEMP_CONTROLLER is defined
                                vehicle.engineTemperatureController = ON;
                                vehicle.ac = ON;
                                vehicle.roomTemperature = vehicle.roomTemperature * (5.0 / 4) + 1; // set room temperature
                                vehicle.engineTemperature = vehicle.engineTemperature * (5.0 / 4) + 1; // set engine temperature
        #endif
                            } else if (trafficLight == 'R' || trafficLight == 'r') {
                                vehicle.vehicleSpeed = 0; // Stop vehicle for red traffic light
                            }
                            break;

                        case 'c':
                            // Handle room temperature sensor input
                            printf("Set the room temperature (Temperature Sensor) . \n");
                            fflush(stdout);
                            scanf("%d", &roomTempSensor);
                            if (roomTempSensor < 10) {
                                vehicle.ac = ON;
                                vehicle.roomTemperature = 20; // set the room temperature if it low
                            } else if (roomTempSensor > 30) {
                                vehicle.ac = ON;
                                vehicle.roomTemperature = 20; // set the room temperature if it high
                            } else {
                                vehicle.ac = OFF; // Turning off AC otherwise(the temperature is in normal range)
                            }
                            break;

                        case 'd':
        #ifdef WITH_ENGINE_TEMP_CONTROLLER
                            // set the engine temperature sensor input
                            printf("Set the engine temperature (Engine Temperature Sensor). \n");
                            fflush(stdout);
                            scanf("%d", &engineTempSensor);
                            if (engineTempSensor < 100) {
                                vehicle.engineTemperatureController = ON;
                                vehicle.engineTemperature = 125; // set engine temperature if too low
                            } else if (engineTempSensor > 150) {
                                vehicle.engineTemperatureController = ON;
                                vehicle.engineTemperature = 125; // set engine temperature if too high
                            } else {
                                vehicle.engineTemperatureController = OFF; // set off Engine Temperature Controller
                            }
        #endif
                            break;

                        default:
                            printf("Invalid choice. Please try again.\n");
                            break;
                    }

                    // Displaying the updated vehicle state
                    displayVehicleState(&vehicle);
                }
                break;


            case 'b':
                vehicle.engine = OFF; //Turning off the engine
                break;

            case 'c':
                printf("Exiting the system.\n");//exiting the system
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}
