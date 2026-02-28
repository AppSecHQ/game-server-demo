#pragma once

struct ServerConfig {
    char server_name[64];
    char bind_address[32];
    int port;
    int max_players;
    char motd[256];
};

class ConfigParser {
public:
    ServerConfig load(const char* filepath);
    void dump(const ServerConfig& config);
};
