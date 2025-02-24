#include<stdio.h>
#include<stdint.h>

#define SIZE 5

/** Ma tran 5x5 de luu ma hoa */
char keyMtrx[SIZE][SIZE];

/**Ham kiem tra xem ky tu da ton tai trong ma tran chua */
int is_char_exist(char matran[SIZE][SIZE], char ch){
  for(int i = 0; i < SIZE; i++){
    for(int j = 0; j < SIZE; j++){
      if(matran[i][i] == ch){
        return 1; //Khong co boolean u -.-
      }
    }
  }
  return 0;
}

/**Ham tao ma tran playfair tu tu khoa */
void matrix_create(const char *key){
  int i, j, k = 0;
  char kytu[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 
                'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}; //I voi J duoc tinh la 1 chu

  //Dien tu khoa vao ma tran 
  for(i = 0; i < SIZE; i++){
    for(j = 0; j < SIZE; j++){
      while(key[k] && is_char_exist(keyMtrx, key[k])) k++; //Khong co ky tu nao trung thi di tiep
        if(key[k]){
          keyMtrx[i][j] = key[k++];
        }else break;
    }
  }
  /**Dien not cac chu cai con lai */
  for(int ch = 0; ch < 25; ch++){
    if(!is_char_exist(keyMtrx, kytu[ch])){
      keyMtrx[i][j++] = kytu[ch];
      if(j == SIZE){
        i++;
        j = 0;
      }
    }
  }
}

/**Ham tim vi tri cua mot ky ty trong ma tran */
void find_pst(char ch, int *row, int *col){
  if(ch == 'J'){
    ch = 'I'; //Thay 'J' bang 'I' 
  }
  for(int i = 0; i < SIZE; i++){
    for(int j = 0; j < SIZE; j++){
      if(keyMtrx[i][j] == ch){
        *row = i;
        *col = j;
        return;
      }
    }
  }
}

//Ham ma hoa tung cap (2 ky tu 1 cap)
void encrypt_pair(char *a, char *b){
  int row1, row2, col1, col2;
  find_pst(*a, &row1, &col1);
  find_pst(*b, &row2, &col2);

  if(row1 == row2){ //Cung hang -> lay ben phai
    *a = keyMtrx[row1][(col1 + 1) % SIZE];
    *b = keyMtrx[row2][(col2 + 1) % SIZE];  
  }
  else if(col1 == col2){ //Cung cot -> lay xuong duoi 
    *a = keyMtrx[(row1 + 1) % SIZE][col1];
    *b = keyMtrx[(row2 + 1) % SIZE][col2];
  }
  else{
    *a = keyMtrx[row1][col2];
    *b = keyMtrx[row2][col1];
  }
}

/**Ham ma hoa van ban */
void encryt_text_playfair(const char *ban_ro, char *ban_ma){
  int i, length = 0;

  //Xu ly tung cap ky tu
  for(i = 0; ban_ro[i] != '\0'; i += 2){
    char a = ban_ro[i];
    char b = ban_ro[i + 1] ? ban_ro[i + 1] : 'X'; //Neu le chu, them X

    if(a == b){
      b = 'X'; //Neu trung thay 1 ky tu bang 'X'
    }

    encrypt_pair(&a, &b);
    ban_ma[length++] = a;
    ban_ma[length++] = b;
  }
  ban_ma[length] = '\0'; //Ket thuc chuoi
}

/*Ham in ra ma tran khoa*/
void print_matrix(){
  for(int i = 0; i < SIZE; i++){
    for(int j = 0; j < SIZE; j++){
      printf("%c ", keyMtrx[i][j]);
    }
    printf("\n");
  }
}

/**Ham in ra chuoi */
void print_string(const char *text){
  while(*text){
    putchar(*text++);
  }
  putchar('\n');
}

int main(){
  char key[] = "LY THUYET MAT MA KHO QUA";
  char ban_ro[] = "TOI THICH CHUONG TRINH IOT";
  char ban_ma[100];

  //Tao ma tran khoa tu key
  matrix_create(key);

  //Ma hoa
  encryt_text_playfair(ban_ro, ban_ma);

  printf(" <> Ma tran Playfair <> \n");
  print_matrix();
  printf("\n<> Van ban goc: ");
  print_string(ban_ro);
  printf("\n<> Ban da ma hoa: ");
  print_string(ban_ma);

  return 0;
}
