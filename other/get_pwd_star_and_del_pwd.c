#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

char get_char_from_terminal(void)
{
  char chr = 0;
  int ret = 0;
  struct termios org_opts, new_opts;
  
  ret = tcgetattr(STDIN_FILENO, &org_opts); //获取与终端相关的参数
  if(ret == -1)
  {
    printf("tcgetattr error! Error code: %d, Error message: %s\n", errno, strerror(errno));
    chr = '\n';
    return chr;
  }
  
  memcpy(&new_opts, &org_opts, sizeof(new_opts));
  new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
  
  ret = tcsetattr(STDIN_FILENO, TCSANOW, &new_opts); //设置与终端相关的参数
  if(ret == -1)
  {
    printf("tcsetattr error! Error code: %d, Error message: %s\n", errno, strerror(errno));
    chr = '\n';
    return chr;
  }
  
  chr = getchar();
  ret = tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);
  if(ret == -1)
  {
    printf("tcsetattr error! Error code: %d, Error message: %s\n", errno, strerror(errno));
    chr = '\n';
    return chr;
  }
  return chr;
}

char* get_password_from_stdin(const char echo_char)
{
  static char strPassword[128];
  unsigned char chr;
  int i = 0;
  
  memset(strPassword, 0, sizeof(strPassword));
  while((chr = get_char_from_terminal()) != '\n')
  {
    if((i < sizeof(strPassword)) && isprint(chr))
    {
      strPassword[i++] = chr;
      putchar(echo_char); //echo char
    }
    else if((i > 0) && ((chr == 0x7F) || (chr == 0x08))) //chr: 127/0x7F --> Backspace Key ==> '\b'; 8/0x08 --> Delete Key
    {
      --i;
      putchar('\b');
      putchar(' ');
      putchar('\b');
    }
  }
  strPassword[i] = 0; //'\0';
  return strPassword;
}

int main(int argc, char** argv)
{
  char* strPwd = NULL;
  printf("Please Enter Password: ");
  printf("\nPassword You Entered is %s\n", get_password_from_stdin(argv[1] ? argv[1][0] : '*'));
  return 0;
}
