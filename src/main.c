#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_BUF_SIZE 10

char *get_current_date() {
  char *buffer = malloc(sizeof(char) * MAX_BUF_SIZE);

  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  sprintf(buffer, "%02d/%d/%02d", tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900);

  return buffer;
}

int main() {
  printf("[+] typora license resetter\n");

  char *date = get_current_date();
  printf("[+] current date: %s\n\n", date);

  return 0;
}
