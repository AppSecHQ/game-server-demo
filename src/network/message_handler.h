#pragma once

#define MAX_MESSAGE_SIZE 256
#define MAX_PLAYER_NAME 32

struct NetworkMessage {
    char player_name[MAX_PLAYER_NAME];
    char payload[MAX_MESSAGE_SIZE];
    int message_type;
};

class MessageHandler {
public:
    void process_incoming(const char* raw_data, int data_len);
    void broadcast(const char* sender, const char* message);

private:
    void route_message(const NetworkMessage& msg);
};
