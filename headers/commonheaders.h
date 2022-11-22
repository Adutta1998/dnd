#if !defined(HEADERS)
#define HEADERS -1

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include <locale.h>
#include <sys/time.h>

void dndInit();
int updateGlobal(int status);
int updateSelective(char uid[], int status);
int connectuser(char f_uid[], char t_uid[]);
int registeruser(char name[], char mob[], char password[]);
int loginuser(char uid[], char password[]);
void showUsers();
void doFree();

typedef struct User
{
    char uid[10];
    char name[10];
    char password[10];
    char mob[10];
} User;

typedef struct Users
{
    User user;
    struct Users *next;
} Users;

typedef struct
{
    char uid[10];
    int status;
} Selective;

#endif // HEADERS
