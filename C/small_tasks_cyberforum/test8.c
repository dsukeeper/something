#include <stdio.h>
#include <stdlib.h>

int main()
{
  FILE * inptr = fopen( "1.txt" , "rb" );
  if (inptr == NULL)
  {
      fputs("Ошибка файла", stderr);
      return 1;
  }
  
    FILE *outptr = fopen("2.txt", "w");
    if (outptr == NULL)
    {
        fclose(outptr);
        fputs("Ошибка файла", stderr);
        return 2;
    }


  // определяем размер файла
  fseek(inptr , 0 , SEEK_END);                          // устанавливаем позицию в конец файла
  long lSize = ftell(inptr);                            // получаем размер в байтах
  rewind (inptr);                                       // устанавливаем указатель в конец файла

  char * buffer = (char*) malloc(sizeof(char) * lSize); // выделить память для хранения содержимого файла
  if (buffer == NULL)
  {
      fputs("Ошибка памяти", stderr);
      exit(2);
  }

  size_t result = fread(buffer, 1, lSize, inptr);       // считываем файл в буфер
  if (result != lSize)
  {
      fputs("Ошибка чтения", stderr);
      exit (3);
  }

  //содержимое файла теперь находится в буфере
  puts(buffer);
  int i=0;
//  for (int i=0;*(buffer+i-3)!='0'; i+=6){
    while (*(buffer+i-3)!='0'){
      if (atoi(buffer+i)>9){
        fwrite(buffer+i,sizeof(char),3,outptr);
        i+=6;
      }
      else {
        fwrite(buffer+i,sizeof(char),2,outptr);
        i+=6;
      }
      puts(buffer+i);
  }


  // завершение работы
  fclose(inptr);
  fclose(outptr);
  free (buffer);
  return 0;
}
