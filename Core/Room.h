#pragma once
#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <iostream>
using namespace std;

class Room {
private:
    string roomId;
    string roomType;
    int capacity;
    string status;
    string assignedCourse;

public:
    Room();
    Room(string id, string type, int cap, string stat);

    void assignToCourse(string courseCode);
    void releaseRoom();
    void setStatus(string stat);

    string getRoomId() const;
    string getRoomType() const;
    int getCapacity() const;
    string getStatus() const;
    string getAssignedCourse() const;
    bool isAvailable() const;

    void display() const;
};

#endif