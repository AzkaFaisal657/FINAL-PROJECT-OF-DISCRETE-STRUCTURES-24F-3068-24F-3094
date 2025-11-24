#include "Room.h"
#include <sstream>

Room::Room(const std::string& roomId, const std::string& type, int capacity, const std::string& status)
    : roomId(roomId), type(type), capacity(capacity), status(status) {}

std::string Room::getRoomId() const { return roomId; }
std::string Room::getType() const { return type; }
int Room::getCapacity() const { return capacity; }
std::string Room::getStatus() const { return status; }

void Room::setRoomId(const std::string& roomId) { this->roomId = roomId; }
void Room::setType(const std::string& type) { this->type = type; }
void Room::setCapacity(int capacity) { this->capacity = capacity; }
void Room::setStatus(const std::string& status) { this->status = status; }

std::string Room::toString() const {
    std::ostringstream oss;
    oss << roomId << " - " << type << " (Capacity: " << capacity << ", Status: " << status << ")";
    return oss.str();
}