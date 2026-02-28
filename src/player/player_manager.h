#pragma once

#define MAX_PLAYERS 64

struct PlayerRecord {
    char username[32];
    char display_name[64];
    int score;
    int level;
};

class PlayerManager {
public:
    int register_player(const char* username, const char* display_name);
    void update_score(const char* username, int points);
    char* get_leaderboard();

private:
    PlayerRecord players[MAX_PLAYERS];
    int player_count = 0;
    char leaderboard_cache[4096];
};
