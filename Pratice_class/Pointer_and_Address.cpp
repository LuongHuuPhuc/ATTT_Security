#include<iostream>

using namespace std;

//Ham tim uoc chung lon nhat gcd 
//Thuat toan Eculid 
int GCD(int a, int b){
  while(b != 0){
    int temp = b; //Luu gia tri cu cua b
    b = a % b; //b thay doi thanh gia tri moi
    a = temp; //a luu gia tri cu cua b, roi lap lai vong lap neu b != 0
  }
  return a;
}
/**
 * @note Vi du tren, bien b thay doi nhung bien temp van giu nguyen gia tri cu
 * Ban chat cua viec gan int temp = b la bien temp sao chep gia tri cua b
 * chu 2 bien b va temp van nam trong 2 o nho doc lap, chung khong lien ket voi nhau 
 * ------------------------------------------------------------
 * -    Dia chi       -      Gia tri      -       Bien        -
 * -    0x100         -         18        -         b         -
 * -    0x104         -         18        -         temp      - 
 * ------------------------------------------------------------
 */
/**
 * @note Dung bien tham chieu
 * @note Gan dia chi cho con tro
 */

void reference_var(int a, int b){
  int &temp = b; //Temp la 1 bien tham chieu den b (bi danh cua b)
  cout << "Truoc khi thay doi b: " << b << ", temp: " << temp << ", dia chi: " << &temp << endl;

  b = a % b; //Thay doi ca gia tri bien tham chieu temp
  cout << "Sau khi thay doi b: " << b << ", temp: " << temp << ", dia chi: " << &temp << endl;
}

void pointer_to_address(int a, int b){
  int *temp = &b; //Con tro temp cho den dia chi cua d

  cout << "Truoc khi thay doi b: " << b << ", temp: " << *temp << ", dia chi: " << temp << endl;

  b = a % b;

  cout << "Sau khi thay doi b: " << b << ", temp: " << *temp << ", dia chi: " << temp << endl;
}

int main(){
  int a, b;
  cout << "Nhap so a: ";
  cin >> a;

  cout << "\nNhap so b: " ;
  cin >> b;

  cout << "\nUoc chung lon nhat cua " << a << " va " << b << " la: " << GCD(a, b) << endl;

  reference_var(a, b);
  pointer_to_address(a, b);
  return 0;
}



