from Crypto.Cipher import DES
from Crypto.Util.Padding import unpad
import binascii

# Hàm giải mã DES từ ciphertext đã mã hóa và khóa
def des_decrypt(ciphertext_hex, key):
    # Chuyển ciphertext từ hex về dạng bytes
    ciphertext = bytes.fromhex(ciphertext_hex)

    # Chế độ CBC yêu cầu IV, giả sử bạn có IV đã được lưu trữ hoặc truyền theo cùng
    # Ví dụ IV có thể được lưu ở đầu ciphertext hoặc được cung cấp riêng
    # Trong trường hợp này, chúng ta giả sử IV nằm ở đầu ciphertext (8 byte đầu).
    iv = ciphertext[:8]  # IV là 8 byte đầu của ciphertext
    ciphertext = ciphertext[8:]  # Phần còn lại là ciphertext

    # Khởi tạo đối tượng cipher với khóa và IV
    cipher = DES.new(key, DES.MODE_CBC, iv)

    # Giải mã dữ liệu và loại bỏ padding
    try:
        plaintext = unpad(cipher.decrypt(ciphertext), DES.block_size)
        print(f'Decrypted Data: {plaintext.decode()}')
    except ValueError as e:
        print(f"Error: {e}")

# Ví dụ về dữ liệu mã hóa (ciphertext hex) và khóa
ciphertext_hex = '9a98f8e13c6c745af8c0bc60fdc6e251'  # Dữ liệu đã mã hóa dưới dạng hex
key = b'12345678'  # Khóa DES phải có độ dài 8 byte

# Gọi hàm giải mã
des_decrypt(ciphertext_hex, key)
