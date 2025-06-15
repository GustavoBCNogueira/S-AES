#ifndef ECB_OP_MODE_H
#define ECB_OP_MODE_H

#include <vector>
#include <cstdint>

std::vector<uint16_t> encrypt_saes_ecb(const std::vector<uint16_t>& plaintext_blocks, uint16_t key);
std::vector<uint16_t> decrypt_saes_ecb(const std::vector<uint16_t>& ciphertext_blocks, uint16_t key);

#endif // ECB_OP_MODE_H
