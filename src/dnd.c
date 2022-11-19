#include "../headers/dnd.h"

struct Selective
{
    char uid[10];
    int status;
};

struct User
{
    char uid[10];
    char name[10];
    char password[10];
    char mob[10];
};

int globalDnd = 0;

void dndInit()
{
    FILE *fp = fopen("globaldnd", "r");
    fscanf(fp, "%d", &globalDnd);
    fclose(fp);
}

int updateGlobal(int status)
{
    if (globalDnd == status)
    {
        printf("Couldn't change the status to itself");
        return -1;
    }
    FILE *fp = fopen("globaldnd", "w");
    fprintf(fp, "%d", status);
    fclose(fp);
    globalDnd = status;
    return 0;
}

int updateSelective(char uid[], int status)
{
    if (globalDnd == 1)
    {
        printf("Global DND is ON. couldnt Change Anything.\n");
        return -1;
    }
    char path[25] = "";
    char base[10] = "./status/";
    strcpy(path, base);
    strcat(path, uid);
    FILE *fp = fopen(path, "rb");
    struct Selective sel;
    fread(&sel, sizeof(struct Selective), 1, fp);
    if (sel.status == status)
    {
        printf("Couldn't change the status to itself\n");
        return -1;
    }
    fclose(fp);
    sel.status = status;
    FILE *fpdnd = fopen(path, "wb");
    fwrite(&sel, sizeof(struct Selective), 1, fpdnd);
    fclose(fpdnd);

    return 0;
}

int connectuser(char f_uid[], char t_uid[])
{
    if (globalDnd == 1)
    {
        printf("DND on Globally. Couldn't connect\n");
        return -1;
    }
    else
    {

        struct Selective f, t;

        char path[25] = "";
        char base[10] = "./status/";
        strcpy(path, base);
        strcat(path, f_uid);

        FILE *fp = fopen(path, "rb");
        fread(&f, sizeof(struct Selective), 1, fp);
        fclose(fp);

        strcpy(path, "");
        strcpy(path, base);
        strcat(path, t_uid);

        FILE *fp_ = fopen(path, "rb");
        fread(&t, sizeof(struct Selective), 1, fp_);
        fclose(fp_);

        if (f.status == 1)
        {
            printf("Your DND is ON. Couldn't connect.\n");
            return -1;
        }
        else if (t.status == 1)
        {
            printf("Receivers DND is ON. Couldn't connect.\n");
            return -1;
        }
        else
        {
            printf("Connection Estblished\n");
        }
    }
    return 0;
}