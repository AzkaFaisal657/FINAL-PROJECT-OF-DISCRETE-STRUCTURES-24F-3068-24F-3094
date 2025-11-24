#pragma once
#include <string>

class Room {
private:
    std::string roomId;
    std::string type;
    int capacity;
    std::string status;

public:
    Room(const std::string& roomId, const std::string& type, int capacity, const std::string& status);

    // Getters
    std::string getRoomId() const;
    std::string getType() const;
    int getCapacity() const;
    std::string getStatus() const;

    // Setters
    void setRoomId(const std::string& roomId);
    void setType(const std::string& type);
    void setCapacity(int capacity);
    void setStatus(const std::string& status);

    std::string toString() const;
};