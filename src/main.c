#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>

#define WRITE_REGKEY(parent_loc, sub_loc, key_name, value) \
write_regkey (#parent_loc, parent_loc, sub_loc, key_name, value)

#define MAX_BUF_SIZE 10

bool write_regkey(const char *parent_str, HKEY parent_loc, LPCSTR key_loc,
                   LPCSTR key_name, const char *value) {
  HKEY key;
  if (RegOpenKeyEx(parent_loc, key_loc, 0, KEY_SET_VALUE | KEY_WOW64_64KEY,
                   &key) !=
      ERROR_SUCCESS) {
    printf("[-] [write_regkey] error: %u\n", (unsigned int) GetLastError());
    return false;
  }

  if (RegSetValueEx(key, key_name, 0, REG_SZ, (LPBYTE) value,
                    MAX_BUF_SIZE) != ERROR_SUCCESS) {
    printf("[-] [write_regkey] error: %u\n", (unsigned int) GetLastError());
    RegCloseKey(key);
    return false;
  }

  printf("[+] %s written to %s\\%s\n", value, parent_str, key_loc);

  RegCloseKey(key);
  return true;
}

char *get_current_date() {
  char *buffer = malloc(sizeof(char) * MAX_BUF_SIZE);

  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  sprintf(buffer, "%02d/%d/%02d", tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900);

  return buffer;
}

void print_info() {
  printf("\tif you like typora, you should\n");
  printf("\talso support the developers.\n");
  printf("\tit is a one-time-payment of 15$.\n");
  printf("=> press enter to continue.\n");
  printf("\n");

  getchar();
}

int main() {
  printf("[+] typora license resetter\n");
  print_info();

  char *date = get_current_date();
  printf("[+] current date: %s\n\n", date);

  if (!WRITE_REGKEY(HKEY_CURRENT_USER, "SOFTWARE\\Typora", "IDate", date)) {
    printf("[-] write_regkey failed\n");
  } else {
    printf("\n => should be reset now :)\n");
  }

  free(date); // not sure if needed :c

  getchar();
  return 0;
}
