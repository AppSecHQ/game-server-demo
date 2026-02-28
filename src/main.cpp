#include "network/message_handler.h"
#include "player/player_manager.h"
#include "config/config_parser.h"
#include <cstdio>

int main(int argc, char* argv[]) {
    const char* config_path = (argc > 1) ? argv[1] : "server.xml";

    ConfigParser config_parser;
    ServerConfig config = config_parser.load(config_path);
    config_parser.dump(config);

    printf("Starting %s on %s:%d (max %d players)\n",
           config.server_name, config.bind_address,
           config.port, config.max_players);

    PlayerManager player_mgr;
    MessageHandler msg_handler;

    // Simulate incoming connections
    const char* test_data = "TestPlayer\0Hello World";
    msg_handler.process_incoming(test_data, 22);

    player_mgr.register_player("player1", "FragMaster9000");
    player_mgr.update_score("player1", 150);

    printf("%s", player_mgr.get_leaderboard());

    return 0;
}
