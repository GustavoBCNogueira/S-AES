// Este arquivo demonstra a cifragem AES real (OpenSSL) em vários modos de operação (ECB, CBC, CFB, OFB, CTR).
// O código está comentado detalhadamente para fins didáticos e análise de segurança e desempenho.

#include <openssl/evp.h>      // Biblioteca OpenSSL para funções de cifragem
#include <openssl/rand.h>     // Para geração de números aleatórios (chave e IV)
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

// Função para codificar um vetor de bytes em base64 (para saída amigável)
string base64_encode(const vector<unsigned char>& data) {
    static const char* base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    string out;
    int val = 0, valb = -6;
    for (unsigned char c : data) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            out.push_back(base64_chars[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) out.push_back(base64_chars[((val << 8) >> (valb + 8)) & 0x3F]);
    while (out.size() % 4) out.push_back('=');
    return out;
}

// Função para cifrar um texto com AES real em um modo específico usando OpenSSL
// Recebe o modo (ECB, CBC, etc), o texto plano, a chave e o IV
void aes_encrypt(const string& mode, const vector<unsigned char>& plaintext, const vector<unsigned char>& key, const vector<unsigned char>& iv) {
    // Seleciona o modo de operação do AES
    const EVP_CIPHER* cipher = nullptr;
    if (mode == "ECB") cipher = EVP_aes_128_ecb();
    else if (mode == "CBC") cipher = EVP_aes_128_cbc();
    else if (mode == "CFB") cipher = EVP_aes_128_cfb128();
    else if (mode == "OFB") cipher = EVP_aes_128_ofb();
    else if (mode == "CTR") cipher = EVP_aes_128_ctr();
    else { cout << "Modo não suportado!" << endl; return; }

    // Cria o contexto de cifragem
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    // Vetor para armazenar o texto cifrado (pode ser maior que o texto original)
    vector<unsigned char> ciphertext(plaintext.size() + EVP_CIPHER_block_size(cipher));
    int len, ciphertext_len = 0;

    // Inicializa a cifragem com a chave e IV (ou NULL para ECB)
    EVP_EncryptInit_ex(ctx, cipher, nullptr, key.data(), (mode == "ECB" ? nullptr : iv.data()));
    // Cifra o texto plano
    EVP_EncryptUpdate(ctx, ciphertext.data(), &len, plaintext.data(), plaintext.size());
    ciphertext_len = len;
    // Finaliza a cifragem (preenche o bloco final, se necessário)
    EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len);
    ciphertext_len += len;
    // Libera o contexto
    EVP_CIPHER_CTX_free(ctx);

    ciphertext.resize(ciphertext_len); // Ajusta o tamanho do vetor para o texto cifrado real
    // Exibe o resultado em base64
    cout << "Modo " << mode << ":\nBase64: " << base64_encode(ciphertext) << endl;
}

int main() {
    // Entrada da mensagem a ser cifrada
    string mensagem;
    cout << "Digite a mensagem: ";
    getline(cin, mensagem);
    // Converte a mensagem para vetor de bytes
    vector<unsigned char> plaintext(mensagem.begin(), mensagem.end());

    // Gera chave e IV aleatórios de 128 bits (16 bytes)
    vector<unsigned char> key(16, 0x00); // chave 128 bits
    RAND_bytes(key.data(), key.size());
    vector<unsigned char> iv(16, 0x00);
    RAND_bytes(iv.data(), iv.size());

    // Exibe chave e IV em hexadecimal
    cout << "Chave (hex): ";
    for (auto c : key) cout << hex << setw(2) << setfill('0') << (int)c;
    cout << "\nIV (hex): ";
    for (auto c : iv) cout << hex << setw(2) << setfill('0') << (int)c;
    cout << endl;

    // Cifra a mensagem em todos os modos de operação AES
    aes_encrypt("ECB", plaintext, key, iv);
    aes_encrypt("CBC", plaintext, key, iv);
    aes_encrypt("CFB", plaintext, key, iv);
    aes_encrypt("OFB", plaintext, key, iv);
    aes_encrypt("CTR", plaintext, key, iv);
    return 0;
}
