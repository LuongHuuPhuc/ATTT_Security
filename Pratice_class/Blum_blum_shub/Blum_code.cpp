/**
 * @brief Thuat toan Blum Blum la bo tao so gia ngau nhien 
 * @param p  la so nguyen to va p % 4 = 3 (mod 4)
 * @param q la so nguyen to va q % 4 = 3 (mod 4)
 * 
 * Tinh modun n = q * p
 * @note Chon hat giong seed s sao cho gcd(s, n) = 1
 * Tao chuoi bit bang cong thuc x_(i+1) = x_i^2 mod(n)
 * Bit dau ra la LSB(x_i)
 * @result Sinh ra chuoi 1e6 (10^6)
 */
#include<iostream>
#include<stdint.h>
#include<fstream>

//Ham tim uoc chung lon nhat 
int gcd(int a, int b){
  while(b != 0){
    int temp = b; 
    b = a % b;
    a = temp;
  }
  return a;
}

/**
 * @note ham tao so blum blum shub
*/
void blumblum_shub(int p, int q, int seed, int bit_len, const char *filename){
  int n = p * q;
  int x = (seed * seed) % n;

  std::ofstream outFile(filename); 
  if(!outFile){
    std::cerr << "Khong the mo file !" << std::endl;
    return;
  }

  for(int i = 0; i < bit_len; i++){
    x = (x * x) % n; //Binh phuong modulo n 
    outFile << (x & 1); //Lay bit cuoi LSB
  }
  outFile.close();
  std::cout << "Chuoi ngau nhien da ghi vao file: " << filename << std::endl; 
}

int main(void){
  //Chon 2 so nguyen to p, q (p % 4 = 3, q % 4 = 3)
  int q = 1003;
  int p = 1019; //=> n = 1003 * 1019 = 1022057
  int seed = 54321; //hat giong la gdb(seed, p * q) = 1, la so le bat ky khong chia het cho q hoac p

  //Kiem tra xem seed co hop le khong 
  if(gcd(seed, p * q) != 1){
    std::cerr << "Hat giong khong hop le " << std::endl;
    return 1;
  }

  //Goi ham sinh chuoi ngau nhien 
  blumblum_shub(p, q, seed, 1e6, "C:/Users/ADMIN/Documents/Tai_Lieu_Chuyen_Nganh/ATTT/Pratice_class/Phuc.txt");
  return 0;
}