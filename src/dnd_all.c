#include "../headers/commonheaders.h"
static char *generateId(char *str, size_t size)
{
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ012456789";
    if (size)
    {
        --size;

        srand(time(0));
        for (size_t n = 0; n < size; n++)
        {
            int key = rand() % (int)(sizeof charset - 1);
            str[n] = charset[key];
        }
        str[size] = '\0';
    }
    return str;
}

Users *c, *f, *prev;

int registeruser(char name[], char mob[], char password[])
{
    char *uidgen = malloc(sizeof(char) * 6);
    generateId(uidgen, 6);
    printf("Your U-ID:%s. Please keep it copied", uidgen);
    User *object = malloc(sizeof(User));
    strcpy(object->name, name);
    strcpy(object->uid, uidgen);
    strcpy(object->mob, mob);
    strcpy(object->password, password);
    FILE *file = fopen("users", "ab");
    if (file != NULL)
    {
        fwrite(object, sizeof(User), 1, file);
        fclose(file);
    }
    int num = 0;
    FILE *fp = fopen("numusers.txt", "r");
    fscanf(fp, "%d", &num);
    fclose(fp);
    num = num + 1;

    FILE *fp_ = fopen("numusers.txt", "w");
    fprintf(fp_, "%d", num);
    fclose(fp_);

    char path[25] = "";
    char base[10] = "./status/";
    strcpy(path, base);
    strcat(path, uidgen);
    FILE *fpdnd = fopen(path, "ab");
    Selective dnd;
    dnd.status = 0;
    strcpy(dnd.uid, uidgen);
    fwrite(&dnd, sizeof(Selective), 1, fpdnd);
    fclose(fpdnd);

    printf("%s", path);

    return 0;
}

int loginuser(char uid[], char password[])
{
    c = (Users *)malloc(sizeof(Users));
    c->next = NULL;

    User object2;
    FILE *file = fopen("users", "rb");
    if (file != NULL)
    {
        while (fread(&object2, sizeof(User), 1, file))
        {
            c = (Users *)malloc(sizeof(Users));
            c->next = NULL;
            c->user = object2;

            if (f == NULL)
                f = c;
            else
                prev->next = c;
            prev = c;
        }
        fclose(file);
    }
    Users *usrs = f;
    // int flag = 0;
    while (usrs != NULL)
    {
        if ((strcmp(usrs->user.uid, uid) == 0 && strcmp(usrs->user.password, password) == 0))
        {
            printf("Logged In!!");
            return 1;
        }
        usrs = usrs->next;
    }
    return 0;
}

int globalDnd = 0;

void dndInit()
{
    FILE *fp = fopen("globaldnd", "r");
    fscanf(fp, "%d", &globalDnd);
    fclose(fp);

    User object2;
    FILE *file = fopen("users", "rb");
    if (file != NULL)
    {
        while (fread(&object2, sizeof(User), 1, file))
        {
            c = (Users *)malloc(sizeof(Users));
            c->next = NULL;
            c->user = object2;

            if (f == NULL)
                f = c;
            else
                prev->next = c;
            prev = c;
        }
        fclose(file);
    }
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
    Selective sel;
    fread(&sel, sizeof(Selective), 1, fp);
    if (sel.status == status)
    {
        printf("Couldn't change the status to itself\n");
        return -1;
    }
    fclose(fp);
    sel.status = status;
    FILE *fpdnd = fopen(path, "wb");
    fwrite(&sel, sizeof(Selective), 1, fpdnd);
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

        Selective f, t;

        char path[25] = "";
        char base[10] = "./status/";
        strcpy(path, base);
        strcat(path, f_uid);

        FILE *fp = fopen(path, "rb");
        fread(&f, sizeof(Selective), 1, fp);
        fclose(fp);

        strcpy(path, "");
        strcpy(path, base);
        strcat(path, t_uid);

        FILE *fp_ = fopen(path, "rb");
        fread(&t, sizeof(Selective), 1, fp_);
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

void showUsers()
{
    Users *usrs = f;
    while (usrs != NULL)
    {
        printf("%s\t\t%s\t\t%s\n", usrs->user.uid, usrs->user.mob, usrs->user.name);
        usrs = usrs->next;
    }
}

void doFree()
{
    free(f);
}