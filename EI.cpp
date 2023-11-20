#include <iostream>
#include <map>
#include <string>
using namespace std;

// Define the Smart Device classes
class Device {
public:
    int device_id;
    string device_type;
};

class Light : public Device {
public:
    string status;

    // Constructor for Light
    Light(int id, const string& type, const string& initialStatus)
        : Device{id, type}, status{initialStatus} {}
};

class Thermostat : public Device {
public:
    int temperature;

    // Constructor for Thermostat
    Thermostat(int id, const string& type, int initialTemperature)
        : Device{id, type}, temperature{initialTemperature} {}
};

class DoorLock : public Device {
public:
    string status;

    // Constructor for DoorLock
    DoorLock(int id, const string& type, const string& initialStatus)
        : Device{id, type}, status{initialStatus} {}
};

// Define the Smart Home Hub
class SmartHomeHub {
private:
    map<int, Device*> devices;

public:
    // Add a new device to the smart home system
    void addDevice(Device* device) {
        devices[device->device_id] = device;
    }

    // Remove a device from the smart home system
    void removeDevice(int device_id) {
        devices.erase(device_id);
    }

    // Turn on a light device
    void turnOn(int device_id) {
        // Check if the device exists and is a light
        if (devices.find(device_id) != devices.end() && devices[device_id]->device_type == "light") {
            Light* lightDevice = static_cast<Light*>(devices[device_id]);
            lightDevice->status = "on";
        }
    }

    // Turn off a light device
    void turnOff(int device_id) {
        // Check if the device exists and is a light
        if (devices.find(device_id) != devices.end() && devices[device_id]->device_type == "light") {
            Light* lightDevice = static_cast<Light*>(devices[device_id]);
            lightDevice->status = "off";
        }
    }

    // Set a schedule for a thermostat device
    void setSchedule(int device_id, string time, string action) {
        // Check if the device exists and is a thermostat
        if (devices.find(device_id) != devices.end() && devices[device_id]->device_type == "thermostat") {
            cout << "Scheduled " << action << " for thermostat " << device_id << " at " << time << "." << endl;
        }
    }

    // Add a trigger for the smart home system
    void addTrigger(string condition, string comparison, int value, string action) {
        cout << "Added trigger: If " << condition << " " << comparison << " " << value << ", then " << action << "." << endl;
    }

    // Print a status report for all devices in the smart home system
    void printStatusReport() {
        cout << "Status Report:" << endl;
        for (const auto& device : devices) {
            if (device.second->device_type == "light") {
                Light* lightDevice = static_cast<Light*>(device.second);
                cout << "Light " << device.first << " is " << lightDevice->status << "." << endl;
            } else if (device.second->device_type == "thermostat") {
                Thermostat* thermostatDevice = static_cast<Thermostat*>(device.second);
                cout << "Thermostat is set to " << thermostatDevice->temperature << " degrees." << endl;
            } else if (device.second->device_type == "door lock") {
                DoorLock* doorLockDevice = static_cast<DoorLock*>(device.second);
                cout << "Door is " << doorLockDevice->status << "." << endl;
            }
        }
    }
};

int main() {
    // Create instances of smart devices with initialization
    Light light1(1, "light", "off");
    Thermostat thermostat1(2, "thermostat", 70);
    DoorLock doorLock1(3, "door lock", "locked");

    // Initialize the Smart Home System
    SmartHomeHub smartHomeHub;
    smartHomeHub.addDevice(&light1);
    smartHomeHub.addDevice(&thermostat1);
    smartHomeHub.addDevice(&doorLock1);

    // Turn on the light
    smartHomeHub.turnOn(1);

    // Set a schedule for the thermostat
    smartHomeHub.setSchedule(2, "06:00", "Turn On");

    // Add a trigger for the thermostat
    smartHomeHub.addTrigger("temperature", ">", 75, "turnOff(1)");

    // Print status report
    smartHomeHub.printStatusReport();

    return 0;
}