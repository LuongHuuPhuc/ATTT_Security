from Crypto.Cipher import DES
from Crypto.Util.Padding import pad, unpad
from Crypto.Random import get_random_bytes
import binascii

# Hàm mã hóa và giải mã DES
def des_encrypt():
    # Khóa DES (8 byte = 64 bit)
    key = b'12345678'  # Khóa DES phải có độ dài 8 byte

    # Dữ liệu cần mã hóa
    data = b'0123456789abcdef'  # Dữ liệu cần mã hóa

    # Tạo cipher object (chế độ CBC)
    cipher = DES.new(key, DES.MODE_CBC)

    # Tạo IV ngẫu nhiên (chế độ CBC yêu cầu IV)
    iv = cipher.iv

    # Mã hóa dữ liệu (dữ liệu phải được padding đúng cách)
    ciphertext = cipher.encrypt(pad(data, DES.block_size))  # Padding dữ liệu về độ dài block

    print(f'Original Data: {data.decode()}')
    print(f'Ciphertext (Hex): {binascii.hexlify(ciphertext)}')

# Gọi hàm mã hóa và giải mã
des_encrypt()
