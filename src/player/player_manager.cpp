#include "player_manager.h"
#include <cstring>
#include <cstdio>

int PlayerManager::register_player(const char* username, const char* display_name) {
    if (player_count >= MAX_PLAYERS) {
        return -1;
    }

    PlayerRecord& player = players[player_count];

    // CWE-120: strcpy — username from client copied without bounds check
    strcpy(player.username, username);
    strcpy(player.display_name, display_name);

    player.score = 0;
    player.level = 1;
    player_count++;

    return player_count - 1;
}

void PlayerManager::update_score(const char* username, int points) {
    for (int i = 0; i < player_count; i++) {
        if (strcmp(players[i].username, username) == 0) {
            players[i].score += points;

            // CWE-120: sprintf into fixed buffer with player-controlled data
            char notification[64];
            sprintf(notification, "Player %s scored %d points! Total: %d",
                    players[i].display_name, points, players[i].score);
            break;
        }
    }
}

char* PlayerManager::get_leaderboard() {
    // CWE-120: Building string with sprintf, no size tracking
    char* cursor = leaderboard_cache;

    for (int i = 0; i < player_count; i++) {
        cursor += sprintf(cursor, "%d. %s — Score: %d (Level %d)\n",
                          i + 1, players[i].display_name,
                          players[i].score, players[i].level);
    }

    return leaderboard_cache;
}
