#include <stdio.h>
#include <stdint.h>

/**
 * @brief Tong quan ve thuat toan RC4 
 * - La mot thuat toan ma dong duoc Ron Rivest vao nam 1987
 * - No su dung mot khoa bi mat de tao ra chuoi bit "pseudorandom" (gia ngau nhien) co do dai bat ky, 
 * sau do XOR chuoi nay voi du lieu goc de tao ra ban ma (ciphertext)
 */
static const char *KEY = "ABCDEFGH123";

//Khoi tao trang thai KSA (Key scheduling Algorithm) & hop S-box
void rc4_init(uint8_t *s, const uint8_t *key, int8_t key_length){
  for(int i = 0; i < 256; i++){
    s[i] = i;
  }

  int j, temp;
  //Tao key co do dai 256-bit 
  for(int i = 0; i < 256; i++){
    j = (j + s[i] + key[i % key_length]) % 256;
    temp = s[i];
    s[j] = s[i];
    s[j] = temp;
  }
}

//Khoi tao keystream su dung thuat toan tao gia ngau nhien (PRGA)
void rc4_keystream_gen(uint8_t *s, uint8_t *key_stream, int8_t length){
  int i = 0, j = 0, temp;
  for(int k = 0; k < length; k++){
    i = (i + 1) % 256;
    j = (j + s[i]) % 256;

    //swap
    temp = s[i];
    s[i] = s[j];
    s[j] = temp;

    key_stream[k] = s[(s[i] + s[j]) % 256];
  }
}

//XOR ban ro voi keystream de ra ban ma
void rc4_enrypt(const uint8_t *plain_text, uint8_t *cipher_text, uint8_t *key_stream, int8_t length){
  for(int i = 0; i < length; i++){
    cipher_text[i] = plain_text[i] ^ key_stream[i];
  }
}

void rc4_decrypt(const uint8_t *cipher_text, uint8_t *decrypted_text, uint8_t *key_stream, int8_t length){
  for(int i = 0; i < length; i++){
    decrypted_text[i] = cipher_text[i] ^ key_stream[i];
  }
}

int8_t strlen_func(const char *str){
  int8_t length;
  while(str[length] != '\0'){
    length++;
  }
  return length;
}

int main(void){
  const char *plain_text = "Hanoi University of Science and Technology";
  int8_t length = strlen_func(plain_text);
  uint8_t s[256], key_stream[length], cipher_text[length], decrypted_text[length];

  //Chuyen key thanh chuoi byte 
  uint8_t key[strlen_func(KEY)];
  for(int i = 0; KEY[i] != '\0'; i++){
    key[i] = KEY[i]; //Chuyen tung ky tu cua KEY thanh gia tri uint8_t 
  }
  int8_t key_length = strlen_func((char*)key);

  //Khoi tao S-box RC4
  rc4_init(s, key, key_length);

  //Khoi tao keystream
  rc4_keystream_gen(s, key_stream, length);

  //Ma hoa plain text
  rc4_enrypt(plain_text, cipher_text, key_stream, length);

  //In ra key stream
  printf("Key stream:");
  for(int i = 0; i < length; i++){
    printf("%02X", key_stream[i]);
  }
  printf("\n");

  //In ra cipher text
  printf("Cipher text:");
  for(int i = 0; i < length; i++){
    printf("%02x", cipher_text[i]);
  }
  printf("\n");

  //In ra ban giai ma 
  printf("Decrypted text:");
  for(int i = 0; i < length; i++){
    printf("%02x", decrypted_text[i]);
  }
  printf("\n");
}