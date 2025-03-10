from Crypto.Cipher import DES3, DES
from Crypto.Util.Padding import pad, unpad
import binascii
import random 

def des_encrypt_decrypt(input_data, key, mode):
    cipher = DES.new(key, DES.MODE_ECB)
    
    if mode == 'encrypt':
        # Mã hóa
        ciphertext = cipher.encrypt(pad(input_data, DES.block_size))
        print(f'DES Encryption: {binascii.hexlify(ciphertext)}')
        return ciphertext
    elif mode == 'decrypt':
        # Giải mã
        plaintext = unpad(cipher.decrypt(input_data), DES.block_size)
        print(f'DES Decryption: {plaintext.hex()}')
        return plaintext

def triple_des_encrypt_decrypt(input_data, keys, mode):
    # Kết hợp ba khóa 64-bit thành một khóa 192-bit (24 byte)
    key_3des = bytes.fromhex(f'{keys[0]:016x}{keys[1]:016x}{keys[2]:016x}')
    
    cipher = DES3.new(key_3des, DES3.MODE_ECB)
    
    if mode == 'encrypt':
        # Mã hóa 3DES
        ciphertext = cipher.encrypt(pad(input_data, DES.block_size))
        print(f'3DES Encryption: {binascii.hexlify(ciphertext)}')
        return ciphertext
    elif mode == 'decrypt':
        # Giải mã 3DES
        plaintext = unpad(cipher.decrypt(input_data), DES.block_size)
        print(f'3DES Decryption: {plaintext.hex()}')
        return plaintext

#Ham kiem tra tinh ngau nhien cua khoa 
#Dem cac bit 1 trong key va tinh toan phan tram xuat hien 
def check_random_key(key):
    #Kiem tra bit 1 va bit 0 trong khoa
    bit_count = bin(int.from_bytes(key, byteorder='big')).count('1')
    total_bits = len(key) * 8 

    #In ra ty le bit 1
    print(f'Bit 1 count in key: {bit_count}/{total_bits} = {bit_count/total_bits:.2f}')

    #Kiem tra phan phoi bit 1 va 0 co deu khong
    if 0.45 <= bit_count / total_bits <= 0.55:
        print("=>Key nay co so bit phan bo tot ~")
    else:
        print("=>Key nay co so bit phan bo khong tot ~")


# Các tham số cho DES và 3DES
input_data = bytes.fromhex('0123456789ABCDEF')  # Dữ liệu đầu vào (64-bit)
key_des = bytes.fromhex('0123456789ABCDEF')  # Khóa DES 64-bit
key_3des = [0x0123456789ABCDEF, 0x9474B8E8C73BCA7C, 0x9474B8E8C73BC97D]  # Khóa 3DES 192-bit (3 khóa DES 64-bit)

#Kiem tra tinh ngau nhien cua khoa DES
print("\n===Testing key randomness for DES===")
check_random_key(key_des)

# Kiểm tra mã hóa và giải mã DES
print("\nTesting DES...")
encrypted_data = des_encrypt_decrypt(input_data, key_des, 'encrypt')
des_encrypt_decrypt(encrypted_data, key_des, 'decrypt')

#Kiem tra tinh ngau nhien cua khoa 3DES
print("\n===Testing key randomness for 3DES===")
for i,key in enumerate(key_3des, start=1):
    print(f"Checking randomness of 3DES key {i}:")
    check_random_key(bytes.fromhex(f'{key:016x}'))

# Kiểm tra mã hóa và giải mã 3DES
print("\nTesting 3DES...")
encrypted_3des_data = triple_des_encrypt_decrypt(input_data, key_3des, 'encrypt')
triple_des_encrypt_decrypt(encrypted_3des_data, key_3des, 'decrypt')
