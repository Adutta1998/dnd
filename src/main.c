#include "../headers/auth.h"
#include "../headers/dnd.h"
void clrscr(void)
{
    system("clear");
}
int main(int argc, char const *argv[])
{
    int ch;

    printf("******************\n");
    printf("******Welcome*****\n");
    printf("******************\n");
    printf("*****Into DND*****\n\n");

    printf("Login\t\t(0)\n");
    printf("Register\t(1)\n\n");
    printf("Enter Your Choice:");
    scanf("%d", &ch);
    getchar();
    int status = 0;
    char loggedInUserId[10];

    if (ch == 0)
    {
        char uid[10];
        char pwd[10];
        printf("Enter USER-ID:");
        fgets(uid, sizeof(uid), stdin);
        uid[strlen(uid) - 1] = '\0';

        printf("Enter PASSWORD:");
        fgets(pwd, sizeof(pwd), stdin);
        pwd[strlen(pwd) - 1] = '\0';

        status = loginuser(uid, pwd);
        if (status == 1)
        {
            printf("Logged In\n");
            strcpy(loggedInUserId, uid);
        }
        else
            printf("Incorrect uid or password\n");
    }
    else if (ch == 1)
    {

        char uname[10];
        char pwd[10];
        char phone[15];

        printf("Enter NAME:");
        fgets(uname, sizeof(uname), stdin);
        uname[strlen(uname) - 1] = '\0';

        printf("Enter PASSWORD:");
        fgets(pwd, sizeof(pwd), stdin);
        pwd[strlen(pwd) - 1] = '\0';
    p:
        printf("Enter PHONE NO:");
        fgets(phone, sizeof(phone), stdin);
        phone[strlen(phone) - 1] = '\0';
        if (strlen(phone) != 10)
        {
            printf("Phone number should must be equal to 10 digits");
            goto p;
        }
        registeruser(uname, phone, pwd);
        exit(0);
    }
    else
    {
        printf("Wrong Option!!");
        exit(0);
    }

    dndInit();

    while (status == 1)
    {
        // clrscr();
        int c, sc;
        printf("\n\n******************\n");
        printf("***** Menu *******\n\n");
        printf("Toggle Global DND\t(1)\n");
        printf("Toggle Selective DND\t(2)\n");
        printf("Connect User\t\t(3)\n");
        printf("Quit\t\t\t(4)\n");
        printf("Choosen Option:");
        scanf("%d", &c);
        getchar();

        printf("\n\n");
        switch (c)
        {
        case 1:
            printf("Global DND\n");
            printf("\tTo turn ON\t(1)\n");
            printf("\tTo turn OFF\t(0)\n");
            printf("\tYour Choice:");
            scanf("%d", &sc);
            getchar();
            updateGlobal(sc);
            break;
        case 2:
            printf("Selective DND\n");
            printf("\tTo turn ON\t(1)\n");
            printf("\tTo turn OFF\t(0)\n");
            printf("\tYour Choice:");
            scanf("%d", &sc);
            getchar();
            updateSelective(loggedInUserId, sc);
            break;
        case 3:
            printf("Connect User\n");
            printf("\tEnter USER-ID:");
            char uid[10];
            fgets(uid, sizeof(uid), stdin);
            uid[strlen(uid) - 1] = '\0';
            connectuser(loggedInUserId, uid);
            break;

        default:
            if (c != 4)
                printf("Invalid Option!!\n");
            exit(0);
        }
    }
    return 0;
}
