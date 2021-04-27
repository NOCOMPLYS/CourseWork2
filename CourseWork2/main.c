#include <stdio.h>


int nzchecker(const char path[100]){
    FILE *nz;
    int result;
    unsigned char type[2];
    nz = fopen(path, "rb");
    if (nz == NULL){
        printf("ERROR 4");
        return 4;
    }
    result = fread(type, sizeof(unsigned char), 2, nz);
    if (result != 2){
        printf("ERROR 5");
        fclose(nz);
        return 5;
    }
    if (type[0] != 'M' || type[1] != 'Z'){
        printf("File is safe.");
        fclose(nz);
        return 10;
    }
    fclose(nz);
    return 0;
}


int scanfile(const char path[100], long int offset, unsigned char signature[8]){
    FILE *check;
    int result;
    unsigned char sigscan[8];
    check = fopen(path, "rb");
    if (check == NULL){
        printf("ERROR 6");
        return 6;
    }
    result = fseek(check, offset, SEEK_SET);
    if (result != 0){
        printf("ERROR 7");
        fclose(check);
        return 7;
    }
    result = fread(sigscan, sizeof(unsigned char), 8, check);
    if (result != 8){
        printf("ERROR 8");
        fclose(check);
        return 8;
    }
    if (sigscan[0] != signature[0] || sigscan[1] != signature[1] || sigscan[2] != signature[2] ||
            sigscan[3] != signature[3] || sigscan[4] != signature[4] || sigscan[5] != signature[5] ||
            sigscan[6] != signature[6] || sigscan[7] != signature[7]){
        printf("File is safe.");
        fclose(check);
        return 0;
    }
    else{
        printf("File is infected!");
        fclose(check);
        return 0;
    }
    return 0;
}


int main()
{
    FILE *Database;
    int Result;
    long int offset;
    unsigned char signature[8];
    const char path[100];
    size_t i;
    Database = fopen("C:\\Users\\dom\\CLionProjects\\CourseWork2\\Signature.txt", "r");
    if (Database == NULL){
        printf("ERROR 1");
        return 1;
    }
    Result = fscanf(Database, "%hhd%hhd%hhd%hhd%hhd%hhd%hhd%hhd%ld", &signature[0], &signature[1],
                    &signature[2], &signature[3], &signature[4], &signature[5], &signature[6], &signature[7], &offset);
    if (Result != 9){
        printf("ERROR 2");
        return 2;
    }
    if (fclose(Database) != 0){
        printf("ERROR 3");
        return 3;
    }
    printf("Type in the adress of the file you want to check: ");
    scanf("%s", &path);
    if (nzchecker(path) != 0){
        return 0;
    }
    else{
        scanfile(path, offset, signature);
    }
    return 0;
}
