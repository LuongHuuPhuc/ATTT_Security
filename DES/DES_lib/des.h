#ifndef DES_H
#define DES_H

#define DES_KEY_SIZE 8
#define ENCRYPTION_MODE 1
#define DECRYPTION_MODE 0

#pragma once

#ifdef __cplusplus
extern "C" {
#endif //C

typedef struct {
  unsigned char k[DES_KEY_SIZE];
  unsigned char c[4];
  unsigned char d[4];
} key_t;

//Dinh nghia bien thuc hien (action parameters)
static const char *DES_ENCRYPT = "-e";
static const char *DES_DECRYPT = "-d";  
static const char *GENERATE_KEY = "-g";

extern const int initial_key_permutation[];
extern const int initial_message_permutation[];
extern const int key_shift_sizes[];
extern const int sub_key_permutation[];
extern const int message_expansion[];
extern const int right_sub_message_permutation[];
extern const int final_message_permutation[];
extern const unsigned char S[8][4][16];

void print_char_as_binary(char input);

/**
 * @brief In ra khoa 
 */
void print_key_set(key_t key_set);

/**
 * @brief Ham tao khoa chinh (56-bit, 8-bit kiem tra chan le)
 */
void key_generate(unsigned char *key);

/**
 * @brief Ham tao khoa con (48-bit) tu khoa chinh
 */
void sub_keys_generate(unsigned char *main_key, key_t *key_sets);

/**
 * @brief Ham de ma hoa DES
 */
void process_encryption(unsigned char *plain_text, unsigned char *output_data, key_t *key_sets);

/**
 * @brief Ham de giai ma DES
 */
void process_decryption(unsigned char *encrypted_text, unsigned char *output_data, key_t *key_sets);

/**
 * @brief Ham tao S-box (Substitutuon Box)
 * 
 * @param input48 mang 48-bit dau vao sau khi XOR voi khoa sub-key
 * @param output32 mang 32-bit dau ra khi qua S-box
 * @note Chuoi dau ra la 32-bit, moi box la 8-bit, duoc luu vao ser
 */
void s_box(unsigned char *input48, unsigned char *output32);

#ifdef __cplusplus
}
#endif //C

#endif //DES_H