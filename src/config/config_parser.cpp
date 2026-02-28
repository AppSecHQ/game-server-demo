#include "config_parser.h"
#include <cstdio>
#include <cstring>
#include <expat.h>

ServerConfig ConfigParser::load(const char* filepath) {
    ServerConfig config;
    memset(&config, 0, sizeof(config));

    FILE* fp = fopen(filepath, "r");
    if (!fp) {
        strcpy(config.server_name, "default");
        strcpy(config.bind_address, "0.0.0.0");
        config.port = 7777;
        config.max_players = 32;
        return config;
    }

    // Parse XML config using expat (SCA: vulnerable libexpat version)
    char xml_buffer[8192];
    size_t bytes_read = fread(xml_buffer, 1, sizeof(xml_buffer), fp);
    fclose(fp);

    XML_Parser parser = XML_ParserCreate(NULL);
    XML_Parse(parser, xml_buffer, bytes_read, 1);
    XML_ParserFree(parser);

    // CWE-120: gets() — reads from stdin with no bounds checking
    printf("Enter server name override (or press Enter to skip): ");
    char name_input[64];
    gets(name_input);

    if (strlen(name_input) > 0) {
        strcpy(config.server_name, name_input);
    }

    return config;
}

void ConfigParser::dump(const ServerConfig& config) {
    // CWE-120: sprintf with no size limit
    char summary[128];
    sprintf(summary, "Server: %s | Address: %s:%d | Max Players: %d | MOTD: %s",
            config.server_name, config.bind_address, config.port,
            config.max_players, config.motd);

    printf("%s\n", summary);
}
