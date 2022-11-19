#include "../headers/auth.h"

struct User
{
    char uid[10];
    char name[10];
    char password[10];
    char mob[10];
};

struct Selective
{
    char uid[10];
    int status;
};

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

int registeruser(char name[], char mob[], char password[])
{
    char *uidgen = malloc(sizeof(char) * 6);
    generateId(uidgen, 6);
    printf("Your U-ID:%s. Please keep it copied", uidgen);
    struct User *object = malloc(sizeof(struct User));
    strcpy(object->name, name);
    strcpy(object->uid, uidgen);
    strcpy(object->mob, mob);
    strcpy(object->password, password);
    FILE *file = fopen("users", "ab");
    if (file != NULL)
    {
        fwrite(object, sizeof(struct User), 1, file);
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
    struct Selective dnd;
    dnd.status = 0;
    strcpy(dnd.uid, uidgen);
    fwrite(&dnd, sizeof(struct Selective), 1, fpdnd);
    fclose(fpdnd);

    printf("%s", path);

    return 0;
}

int loginuser(char uid[], char password[])
{
    /*
    Getting number of registered users from numusers.txt file
    */
    int num = 0;
    FILE *fp = fopen("numusers.txt", "r");
    fscanf(fp, "%d", &num);
    fclose(fp);
    struct User users[num];

    /*
        read all users data from users file and save it into an array for operations;
    */
    struct User object2;
    FILE *file = fopen("users", "rb");
    if (file != NULL)
    {
        int p = 0;
        while (fread(&object2, sizeof(struct User), 1, file))
        {
            users[p++] = object2;
            // printf("%s/%s/%s\n", object2.uid, object2.name, object2.mob);
        }
        fclose(file);
    }

    /*
    Search User(Linear search)
    */
    for (int i = 0; i < num; i++)
    {
        // printf("%s/%s/%d\t%s/%s/%d\n", users[i].uid, uid, strcmp(users[i].uid, uid), users[i].password, password, strcmp(users[i].password, password));
        if ((strcmp(users[i].uid, uid) == 0) && (strcmp(users[i].password, password) == 0))
            return 1;
    }

    return 0;
}