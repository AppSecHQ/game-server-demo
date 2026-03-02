
#include "player_manager.h"
#include <cstring>
#include <cstdio>

int PlayerManager::register_player(const char* username, const char* display_name) {
    if (player_count >= MAX_PLAYERS) {
        return -1;
    }

    PlayerRecord& player = players[player_count];

    // Use strncpy to prevent buffer overflows when copying user input
    strncpy(player.username, username, sizeof(player.username) - 1);
    player.username[sizeof(player.username) - 1] = '\0'; // Ensure null-termination

    strncpy(player.display_name, display_name, sizeof(player.display_name) - 1);
    player.display_name[sizeof(player.display_name) - 1] = '\0'; // Ensure null-termination

    player.score = 0;
    player.level = 1;
    player_count++;

    return player_count - 1;
}

void PlayerManager::update_score(const char* username, int points) {
    for (int i = 0; i < player_count; i++) {
        if (strcmp(players[i].username, username) == 0) {
            players[i].score += points;

            // Use snprintf to prevent buffer overflows when building the notification string
            char notification[64];
            int result = snprintf(notification, sizeof(notification), "Player %s scored %d points! Total: %d",
                    players[i].display_name, points, players[i].score);

            if (result >= 0 && result < sizeof(notification)) {
                // Notification string was successfully built without truncation
            } else {
                // Handle truncation or error
            }

            break;
        }
    }
}

char* PlayerManager::get_leaderboard() {
    // Consider using a dynamically allocated buffer or a safer string building function
    char* cursor = leaderboard_cache;

    for (int i = 0; i < player_count; i++) {
        int result = snprintf(cursor, 1024, "%d. %s — Score: %d (Level %d)\n",
                          i + 1, players[i].display_name,
                          players[i].score, players[i].level);
        cursor += result;
    }

    return leaderboard_cache;
}
