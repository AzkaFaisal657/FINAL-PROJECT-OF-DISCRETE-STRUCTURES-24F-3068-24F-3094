#include "Room.h"

Room::Room() : roomId(""), roomType(""), capacity(0), status("Available"), assignedCourse("") {}

Room::Room(string id, string type, int cap, string stat)
    : roomId(id), roomType(type), capacity(cap), status(stat), assignedCourse("") {
}

void Room::assignToCourse(string courseCode) {
    assignedCourse = courseCode;
    status = "Occupied";
}

void Room::releaseRoom() {
    assignedCourse = "";
    status = "Available";
}

void Room::setStatus(string stat) {
    status = stat;
}

string Room::getRoomId() const { return roomId; }
string Room::getRoomType() const { return roomType; }
int Room::getCapacity() const { return capacity; }
string Room::getStatus() const { return status; }
string Room::getAssignedCourse() const { return assignedCourse; }

bool Room::isAvailable() const {
    return status == "Available";
}

void Room::display() const {
    cout << "Room ID: " << roomId << endl;
    cout << "Type: " << roomType << endl;
    cout << "Capacity: " << capacity << " students" << endl;
    cout << "Status: " << status << endl;
    if (!assignedCourse.empty()) {
        cout << "Assigned to: " << assignedCourse << endl;
    }
}