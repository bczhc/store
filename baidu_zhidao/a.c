#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct Employee {
    char name[17];
    int64_t num;
    int16_t age;
    char time[9];
    int32_t salary;
};

int getIntegerLen(const int x) {
    int n = x;
    int r = 0;
    while (1) {
        int b = n / 10;
        r++;
        n = b;
        if (!b) break;
    }
    return r;
}

int m_strlen(const char *s) {
    int i = 0;
    while (s[i] != '\0') ++i;
    return i;
}

int64_t m_pow(const int64_t base, const int64_t exponent) {
    int64_t r = 1LL;
    for (int i = 0; i < exponent; ++i) {
        r *= base;
    }
    return r;
}


int m_itoa(char **dest, const int i) {
    int I_L = getIntegerLen(i);
    *dest = (char *) malloc((size_t)(I_L + 1));
    int d_i = 0;
    for (int j = I_L - 1; j >= 0; --j) {
        (*dest)[d_i] = (int) (((int64_t) i) / ((int64_t) m_pow(10LL, j)) % 10) + 48;
        ++d_i;
    }
    (*dest)[d_i] = 0;
    return I_L;
}

int getLongLen(const int64_t x) {
    int64_t n = x;
    int r = 0;
    while (1) {
        int64_t b = n / 10;
        r++;
        n = b;
        if (!b) break;
    }
    return r;
}


int m_ltoa(char **dest, const int64_t i) {
    int I_L = getLongLen(i);
    *dest = (char *) malloc((size_t)(I_L + 1));
    int64_t d_i = 0;
    for (int64_t j = I_L - 1; j >= 0; --j) {
        (*dest)[d_i] = (int) (((int64_t) i) / ((int64_t) m_pow(10LL, j)) % 10) + 48;
        ++d_i;
    }
    (*dest)[d_i] = 0;
    return I_L;
}

static int32_t structSize = sizeof(struct Employee);

int write(struct Employee *employess) {
    FILE *fp1 = NULL;
    if ((fp1 = fopen("info.dat", "wb")) == NULL) {
        perror("fopen error");
        return 1;
    }
    FILE *fp2 = NULL;
    if ((fp2 = fopen("info.txt", "w")) == NULL) {
        perror("fopen error");
        return 1;
    }

    for (int i = 0; i < 3; ++i) {
        //binary write
        fwrite(&(employess[i]), 1, structSize, fp1);

        //text write
        char *name = employess[i].name;
        fwrite(name, 1, m_strlen(name), fp2);
        fputc('\t', fp2);
        char *numStr = NULL;
        int numStrSize = m_itoa(&numStr, employess[i].num);
        fwrite(numStr, 1, numStrSize, fp2);
        free(numStr);
        fputc('\t', fp2);
        char *ageStr = NULL;
        int ageStrSize = m_itoa(&ageStr, employess[i].age);
        fwrite(ageStr, 1, ageStrSize, fp2);
        free(ageStr);
        fputc('\t', fp2);
        fwrite(employess[i].time, 1, 8, fp2);
        fputc('\t', fp2);
        char *salaryStr = NULL;
        int salaryStrSize = m_ltoa(&salaryStr, employess[i].salary);
        fwrite(salaryStr, 1, salaryStrSize, fp2);
        free(salaryStr);
        fputc('\n', fp2);
    }

    fclose(fp1), fclose(fp2);
    return 0;
}


int main() {

    struct Employee employess[] = {
            {"张三", 1, 18, "20200101", 5000},
            {"王五", 2, 19, "20200102", 4000},
            {"李四", 3, 20, "20200103", 4500}};

    if (write(employess)) return 1;

    //----------------read--------------------
    FILE *fp1 = NULL;
    if ((fp1 = fopen("info.dat", "rb")) == NULL) {
        perror("fopen error");
        return 1;
    }
    FILE *fp2 = NULL;
    if ((fp2 = fopen("info.txt", "r")) == NULL) {
        perror("fopen error");
        return 1;
    }

    char buf[structSize];
    //binary read
    for (int i = 0; i < 3; ++i) {
        fread(buf, 1, structSize, fp1);
        struct Employee *read = ((struct Employee *) buf);
        printf("%s\t%li\t%i\t%s\t%i\n", read->name, read->num, read->age, read->time, read->salary);
    }

    printf("\n\n");
    //text read
    char c;
    while (fread(&c, 1, 1, fp2) > 0) {
        printf("%c", c);
    }

    fclose(fp1), fclose(fp2);
    return 0;
}
