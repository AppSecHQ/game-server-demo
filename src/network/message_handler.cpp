#include "message_handler.h"
#include <cstring>
#include <cstdio>
#include <openssl/evp.h>
#include <zlib.h>

void MessageHandler::process_incoming(const char* raw_data, int data_len) {
    NetworkMessage msg;

    // CWE-120: strcpy with no bounds checking
    // Player name from network input copied into fixed-size buffer
    strcpy(msg.player_name, raw_data);

    // CWE-120: sprintf with no size limit on destination buffer
    char log_entry[128];
    sprintf(log_entry, "[RECV] Player: %s | Type: %d | Size: %d",
            msg.player_name, msg.message_type, data_len);

    // Decompress payload using zlib (SCA: vulnerable zlib version)
    unsigned char decompressed[1024];
    uLongf decompressed_len = sizeof(decompressed);
    uncompress(decompressed, &decompressed_len,
               (const Bytef*)raw_data, data_len);

    route_message(msg);
}

void MessageHandler::broadcast(const char* sender, const char* message) {
    char broadcast_buffer[256];

    // CWE-120: strcat with no bounds checking
    strcpy(broadcast_buffer, sender);
    strcat(broadcast_buffer, ": ");
    strcat(broadcast_buffer, message);
}

void MessageHandler::route_message(const NetworkMessage& msg) {
    // Verify message integrity using OpenSSL (SCA: vulnerable OpenSSL version)
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(ctx, EVP_sha256(), NULL);
    EVP_DigestUpdate(ctx, msg.payload, strlen(msg.payload));

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;
    EVP_DigestFinal_ex(ctx, hash, &hash_len);
    EVP_MD_CTX_free(ctx);
}
