#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define FILENAME "accounts.txt"
#define LIMIT 20

int count_donhang = 0; // Bien dem so luong don hang va de danh so don hang trong ngay//
int status = 0;
const char ma_giao_dich[100] = "xincamon";
const int MAX = 1000; // so luong don hang toi da 1 ngay//
int menu = 0;        // so luong mon an trong menu//
char mon[100][50];
int gia[100];
int trang_thai[100];


typedef struct Don_hang
{
    int ban;
    int mon[LIMIT];
    long so_luong[LIMIT];
    long tong;
    double khuyen_mai;
    double thanh_tien;
    int status;
    char staff[100];
} Don_hang;

Don_hang donhang[MAX];

void read_menu()
{
    menu = 0;
    int count = 0;
    FILE *file = fopen("menu.txt", "r");
    char tmp[100];
    while(fgets(tmp, 100, file))
    {
        int c = 0;
        char ten[100];
        char gia_mon[100];
        char *str = tmp;
        while(*str != ',')
        {
            ten[c] = *str;
            str++;
            c++;
        }
        ten[c] = '\0';
        strcpy(mon[menu], ten);
        c = 0;
        str += 2;
        while(*str != '\n')
        {
            gia_mon[c] = *str;
            str++;
            c++;
        }
        gia_mon[c] = '\0';
        gia[menu] = atol(gia_mon);
        trang_thai[menu] = 1;
        menu++;
    }
    fclose(file);
}

void sort(double A[], int B[])
{
    for (int i = 0; i <= menu - 2; i++)
    {
        double max = A[B[i]];
        int pos = i;
        for (int k = i + 1; k <= menu - 1; k++)
        {
            if (A[B[k]] > max)
            {
                max = A[B[k]];
                pos = k;
            }
        }
        int tmp = B[i];
        B[i] = B[pos];
        B[pos] = tmp;
    }
}

void fprint_border(FILE *file, int i)
{
    for (int k = 0; k < i; k++)
    {
        fprintf(file, "_");
    }
    fprintf(file, "\n\n");
}

void print_border(int i)
{
    for (int k = 0; k < i; k++)
    {
        printf("_");
    }
    printf("\n\n");
}

int is_num(char str[1000])
{
    if (strlen(str) == 0)
    {
        return 0;
    }
    for (int i = 0; i < strlen(str); i++)
    {
        if (!isdigit(str[i]))
        {
            return 0;
        }
    }
    return 1;
}

int get_data(char str[1000], int A[])
{
    int count = 0;
    int pos = 0, pos2 = 0;
    if (str[pos] == ' ')
    {
        while (str[pos] == ' ')
        {
            pos++;
        }
    }
    char tmp[100];
    while (1)
    {
        if (str[pos] != ' ' && str[pos] != '\0')
        {
            tmp[pos2] = str[pos];
            pos2++;
        }
        else
        {
            tmp[pos2] = '\0';
            if (is_num(tmp) == 0)
            {
                return 0;
            }
            A[count] = atoi(tmp);
            count++;
            pos2 = 0;
        }
        if (str[pos] == '\0')
        {
            break;
        }
        if (str[pos] == ' ')
        {
            while (str[pos] == ' ')
            {
                pos++;
            }
        }
        else
        {
            pos++;
        }
    }
    if (count == 2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void print_menu()
{
    print_border(100);
    setlocale(LC_NUMERIC, "");
    printf("\033[1;31m");
    printf("%20s\n", "MENU:");
    printf("%20s||%20s||%20s||\n", "ma so", "mon an", "gia");
    printf("\033[0m");
    for (int i = 0; i < menu; i++)
    {
        if (trang_thai[i] == 0)
        {
            continue;
        }
        printf("%20d||%20s||%'20d||\n", i + 1, mon[i], gia[i]);
    }
    printf("\n");
    printf("\033[1;31m");
    printf("******** Khuyen mai 25%% cho cac don co gia tri tu 2,000,000 tro len *********\n");
    printf("\033[0m");
    print_border(100);
}

int nhap_ma()
{
    char str[1000];
    if (status == 1)
    {
        printf("\033[1;35m");
        printf("\n---------------------------------------------------------------------");
        printf("\n|                   BANG HUONG DAN                                   |");
        printf("\n|  Phim bat ki            | goi mon                                  |");
        printf("\n|  e                      | sua mon da dat (Chi dung o buoc goi mon) |");
        printf("\n|  m                      | xem mon da dat (Chi dung o buoc goi mon) |");
        printf("\n|  menu                   | xem lai menu                             |");
        printf("\n|  0 0                    | dung goi mon                             |");
        printf("\n|  t                      | thanh toan                               |");
        printf("\n|Ban chon toi da %d mon, cu phap la ma mon an va so luong (Vd: 1 3)  |", LIMIT);
        printf("\n----------------------------------------------------------------------\n\n");
        printf("\033[0m");
    }
    printf("Moi ban nhap : ");
    fgets(str, 1000, stdin);
    str[strlen(str) - 1] = '\0';
    if (strcasecmp(str, "admin") == 0)
    {
        return 3;
    }
    if (strcmp(str, ma_giao_dich) == 0)
    {
        return 1;
    }
    if (strcasecmp(str, "t") == 0)
    {
        return 2;
    }
    return 0;
}

int tinh_hoa_don() // Tinh tong hoa don va giam gia va luu vao trong mang hoa don//
{
    char tmp[1000];
    setlocale(LC_NUMERIC, "");
    printf("\033[1;31m");
    printf("Ma hoa don: %03d\n\n", count_donhang + 1);
    printf("%20s||%20s||%20s||%20s||%20s\n", "Ma so", "Mon an", "Don gia", "So luong",
           "Thanh Tien");
    printf("\033[0m");
    for (int k = 0; k < LIMIT; k++)
    {
        if (donhang[count_donhang].mon[k] != -1)
        {
            printf("%20d||%20s||%'20d||%20ld||%'20ld||\n", donhang[count_donhang].mon[k] + 1,
                   mon[donhang[count_donhang].mon[k]], gia[donhang[count_donhang].mon[k]],
                   donhang[count_donhang].so_luong[k],
                   donhang[count_donhang].so_luong[k] * gia[donhang[count_donhang].mon[k]]);
        }
    }
    printf("\n%86s %'22ld\n", "Tong: ", donhang[count_donhang].tong);
    printf("%86s %'22.0lf\n", "Khuyen mai: ", donhang[count_donhang].khuyen_mai);
    printf("%86s %'22.0lf\n", "Thanh tien: ", donhang[count_donhang].thanh_tien);
    while (1)
    {
        printf("\033[1;34m");
        printf("Ban co muon thanh toan ngay khong? [Y/N]: ");
        printf("\033[m");
        fgets(tmp, 1000, stdin);
        tmp[strlen(tmp) - 1] = '\0';
        if (strcasecmp(tmp, "Y") == 0)
        {
            printf("Nhan vien thu tien: ");
            fgets(tmp, 1000, stdin);
            tmp[strlen(tmp) - 1] = '\0';
            strcpy(donhang[count_donhang].staff, tmp);
            donhang[count_donhang].status = 1;
            print_border(50);
            printf("\033[1;32m");
            printf("Ban da thanh toan don hang ma so %03d\n", count_donhang + 1);
            printf("\033[0m");
            print_border(50);
            break;
        }
        else if (strcasecmp(tmp, "N") == 0)
        {
            donhang[count_donhang].status = 0;
            print_border(50);
            printf("\033[1;31m");
            printf("Ban chua thanh toan don hang ma so %03d\n", count_donhang + 1);
            printf("\033[0m");
            print_border(50);
            break;
        }
    }
    return 0;
}

int nhap_don_hang() // Nhap ma so mon can mua va so luong ngay tren 1 dong, toi da 20 mon, dung lai
                    // neu nhap 0 0//
{
    char tmp[1000];
    while (1)
    {
        printf("Ban : ");
        fgets(tmp, 1000, stdin);
        tmp[strlen(tmp) - 1] = '\0';
        if (is_num(tmp))
        {
            donhang[count_donhang].ban = atoi(tmp);
            print_border(50);
            break;
        }
        else
        {
            printf("\033[1;31m");
            printf("Khong hop le\n");
            printf("\033[0m");
            print_border(50);
        }
    }
    for (int i = 0; i < LIMIT; i++)
    {
        donhang[count_donhang].mon[i] = -1;
    }
    donhang[count_donhang].tong = 0;
    int count = 0;
    int a[2];
    print_border(50);
    while (1)
    {
        int stt0 = 0;
        printf("So mon hien tai cua ban la %i: ",
               count);
        fgets(tmp, 1000, stdin);
        tmp[strlen(tmp) - 1] = '\0';
        if (strcmp(tmp, "0 0") == 0 && count == 0)
        {
            printf("\033[1;31m");
            printf("Ban chua dat mon an nao\n");
            printf("\033[0m");
            print_border(35);
            continue;
        }
        if (strcmp(tmp, "0 0") == 0)
        {
            print_border(35);
            break;
        }
        if (strcasecmp(tmp, "menu") == 0)
        {
            print_menu();
            continue;
        }
        if (strcasecmp(tmp, "e") == 0)
        {
            if (count == 0)
            {
                printf("\033[1;31m");
                printf("Ban chua co mon an nao\n");
                printf("\033[0m");
                continue;
            }
            int stt = 1;
            print_border(50);
            printf("\033[1;31m");
            printf("Don hang hien tai: \n");
            printf("%20s||%20s||%20s||%20s||%20s||%20s||\n", "STT", "Ma so", "Mon an", "Don gia",
                   "So luong", "Thanh Tien");
            printf("\033[0m");
            for (int k = 0; k < 5; k++)
            {
                if (donhang[count_donhang].mon[k] != -1)
                {
                    printf("%20d||%20d||%20s||%'20d||%20ld||%'20ld||\n", stt,
                           donhang[count_donhang].mon[k] + 1, mon[donhang[count_donhang].mon[k]],
                           gia[donhang[count_donhang].mon[k]], donhang[count_donhang].so_luong[k],
                           donhang[count_donhang].so_luong[k] * gia[donhang[count_donhang].mon[k]]);
                    stt++;
                }
            }
            printf("\033[1;35m");
            printf("Ban muon sua hoac xoa mon co STT: ");
            printf("\033[0m");
            char inp[1000];
            int stt2;
            do
            {
                int check = 0;
                fgets(inp, 1000, stdin);
                inp[strlen(inp) - 1] = '\0';
                if (is_num(inp))
                {
                    stt2 = atoi(inp);
                    if (stt2 < 1 || stt2 > count)
                    {
                        printf("\033[1;31m");
                        printf("STT khong dung \n");
                        printf("\033[0m");
                        continue;
                    }
                    stt = 1;
                    for (int i = 0; i < LIMIT; i++)
                    {
                        if (donhang[count_donhang].mon[i] != -1)
                        {
                            if (stt == stt2)
                            {
                                stt = i;
                                break;
                            }
                            stt++;
                        }
                    }
                    printf("\033[1;35m");
                    printf("Neu muon xoa hay bam \"d\" hoac bam nut bat ki de sua: ");
                    printf("\033[0m");
                    while (1)
                    {
                        fgets(inp, 1000, stdin);
                        inp[strlen(inp) - 1] = '\0';
                        if (strcasecmp(inp, "d") == 0)
                        {
                            donhang[count_donhang].tong -= gia[donhang[count_donhang].mon[stt]]*donhang[count_donhang].so_luong[stt];
                            donhang[count_donhang].mon[stt] = -1;
                            count--;
                            check = 1;
                            printf("\033[1;32m");
                            printf("Da xoa\n");
                            printf("\033[0m");
                            print_border(50);
                            break;
                        }
                        else
                        {
                            while (1)
                            {
                                printf("\033[1;35m");
                                printf("Nhap cu phap de goi mon moi: ");
                                printf("\033[0m");
                                fgets(inp, 1000, stdin);
                                inp[strlen(inp) - 1] = '\0';
                                if (get_data(inp, a) == 0)
                                {
                                    printf("\033[1;31m");
                                    printf("Ban nhap sai cu phap\n");
                                    printf("\033[0m");
                                    print_border(35);
                                    continue;
                                }
                                a[0]--;
                                if (a[0] < 0 || a[0] >= menu)
                                {
                                    printf("\033[1;31m");
                                    printf("Ma mon an khong dung\n");
                                    printf("\033[0m");
                                    print_border(35);
                                    continue;
                                }
                                if (a[1] <= 0)
                                {
                                    printf("\033[1;31m");
                                    printf("So luong khong hop le\n");
                                    printf("\033[0m");
                                    print_border(35);
                                    continue;
                                }
                                donhang[count_donhang].tong -= gia[donhang[count_donhang].mon[stt]]*donhang[count_donhang].so_luong[stt];
                                donhang[count_donhang].mon[stt] = a[0];
                                donhang[count_donhang].so_luong[stt] = a[1];
                                donhang[count_donhang].tong += a[1] * gia[a[0]];
                                printf("\033[1;35m");
                                printf("Ban da goi mon %s voi so luong la %d\n", mon[a[0]], a[1]);
                                printf("\033[0m");
                                print_border(50);
                                check = 1;
                                break;
                            }
                            break;
                        }
                    }
                }
                if (check == 1)
                {
                    break;
                }
            }
            while (1);
            continue;
        }
        if (strcasecmp(tmp, "m") == 0)
        {
            if (count == 0)
            {
                print_border(50);
                printf("\033[1;31m");
                printf("Ban chua dat mon an nao\n");
                printf("\033[0m");
                print_border(50);
                continue;
            }
            int stt = 1;
            print_border(50);
            printf("\033[1;31m");
            printf("Don hang hien tai: \n");
            printf("%20s||%20s||%20s||%20s||%20s||%20s||\n", "STT", "Ma so", "Mon an", "Don gia",
                   "So luong", "Thanh Tien");
            printf("\033[0m");
            for (int k = 0; k < LIMIT; k++)
            {
                if (donhang[count_donhang].mon[k] != -1)
                {
                    printf("%20d||%20d||%20s||%'20d||%20ld||%'20ld||\n", stt,
                           donhang[count_donhang].mon[k] + 1, mon[donhang[count_donhang].mon[k]],
                           gia[donhang[count_donhang].mon[k]], donhang[count_donhang].so_luong[k],
                           donhang[count_donhang].so_luong[k] * gia[donhang[count_donhang].mon[k]]);
                    stt++;
                }
            }
            print_border(50);
            continue;
        }
        if (count == LIMIT)
        {
            printf("So mon an da dat gioi han\n");
            print_border(35);
            continue;
        }
        if (get_data(tmp, a) == 0)
        {
            printf("\033[1;31m");
            printf("Ban nhap sai cu phap\n");
            printf("\033[0m");
            print_border(35);
            continue;
        }
        a[0]--;
        if (a[0] < 0 || a[0] >= menu || trang_thai[a[0]] == 0)
        {
            printf("\033[1;31m");
            printf("Ma mon an khong dung\n");
            printf("\033[0m");
            print_border(35);
            continue;
        }
        if (a[1] <= 0)
        {
            printf("\033[1;31m");
            printf("So luong khong hop le\n");
            printf("\033[0m");
            print_border(35);
            continue;
        }
        for (int i = 0; i < LIMIT; i++)
        {
            if (donhang[count_donhang].mon[i] == -1)
            {
                stt0 = i;
                break;
            }
        }
        donhang[count_donhang].mon[stt0] = a[0];
        donhang[count_donhang].so_luong[stt0] = a[1];
        donhang[count_donhang].tong += a[1] * gia[a[0]];
        printf("\033[1;32m");
        printf("Ban da goi mon %s voi so luong la %d\n", mon[a[0]], a[1]);
        printf("\033[0m");
        print_border(35);
        count++;
    }
    // them 1 buoc de tinh tong hoa don o day//
    if (donhang[count_donhang].tong >= 2000000)
    {
        donhang[count_donhang].khuyen_mai = donhang[count_donhang].tong * 0.25;
        donhang[count_donhang].thanh_tien =
            donhang[count_donhang].tong - donhang[count_donhang].khuyen_mai;
    }
    else
    {
        donhang[count_donhang].khuyen_mai = 0;
        donhang[count_donhang].thanh_tien = donhang[count_donhang].tong;
    }
    tinh_hoa_don();
    count_donhang++;
    printf("So don hang hien tai trong ngay: %d\n", count_donhang);
    print_border(100);
    return 0;
}

int luu_ngay()
{
    double A[menu];
    for (int i = 0; i < menu; i++)
    {
        A[i] = 0;
    }
    int B[menu];
    for (int i = 0; i < menu; i++)
    {
        B[i] = i;
    }
    unsigned long long int tong_da_thu = 0;
    unsigned long long int tong_chua_thu = 0;
    setlocale(LC_NUMERIC, "");
    char name[50];
    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(name, "Thang %d-%d.txt",tm.tm_mon + 1, tm.tm_year + 1900);
    FILE *file = fopen(name, "a");
    if (file == NULL)
    {
        fclose(file);
        return 0;
    }
    fprintf(file, "\n\n%2s %d-%d-%d\n", "Ngay", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    for (int i = 0; i < count_donhang; i++)
    {
        if(i==0)
            {
                fprintf(file, "%20s||%20s||%20s||%15s||%20s\n","Ma don hang","So ban","Thanh tien","Trang thai", "Nhan vien");
            }
        fprintf(file," %15s %03d||%20d||%'20.0lf||%15d||","\t", i + 1, donhang[i].ban,donhang[i].thanh_tien,donhang[i].status);
        if (donhang[i].status == 1)
        {
            fprintf(file, "%20s\n",donhang[i].staff);
        }
        else
        {
            fprintf(file, "\n");
        }
        if (donhang[i].status == 1)
        {
            tong_da_thu += donhang[i].thanh_tien;
        }
        else
        {
            tong_chua_thu += donhang[i].thanh_tien;
        }
        if(i==count_donhang) fprint_border(file, 80);
        for (int k = 0; k < LIMIT; k++)
        {
            if (donhang[i].mon[k] != -1)
            {
                A[donhang[i].mon[k]] += donhang[i].so_luong[k];
            }
        }
    }
    printf("\n");
    fprint_border(file, 80);
    sort(A, B);
    fprintf(file, "Bang xep hang theo muc do ban chay: \n");
    fprintf(file, "%20s||%20s\n", "Mon an", "Doanh so");
    for (int i = 0; i < menu; i++)
    {
        fprintf(file, "%20s||%20.0lf\n", mon[B[i]], A[B[i]]);
    }
    fprint_border(file, 80);
    fprintf(file, "%55s %'22llu\n", "So tien da thu: ", tong_da_thu);
    fprintf(file, "%55s %'22llu\n", "So tien chua thu: ", tong_chua_thu);
    fclose(file);
    return 0;
}
int authenticateFromFile(char username[], char password[]) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Khong the mo file.\n");
        return 0;
    }
    char correct_username[MAX_USERNAME_LENGTH];
    char correct_password[MAX_PASSWORD_LENGTH];
    int check = 0;

    while ((fscanf(file, "%49s %49s", correct_username, correct_password)) == 2) {
        check++;
        if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
            fclose(file);
            return (check == 1) ? 1 : 2;
        }
    }

    fclose(file);
    return 0;
}

void Manager_check(int *result) {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("     Nhap ten tai khoan: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0' ;

    printf("     Nhap mat khau     : ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0';

    int auth_result = authenticateFromFile(username, password);

    system("cls");
    if (auth_result == 1 ) {
        printf("\033[1;34m\n\n             Dang nhap thanh cong voi vai tro quan li\n\033[0m");
        print_border(80);
        *result=auth_result;
        return ;
    }
    if (auth_result == 2) {
        printf("\033[1;34m\n\n             Dang nhap thanh cong voi vai tro nhan vien\n\033[0m");
        print_border(80);
        *result=auth_result;
        return ;
    }
    else {
        printf("\033[1;31m\n\n       Ten nguoi dung hoac mat khau khong chinh xac\n\033[0m");
        print_border(80);
        *result=auth_result;
        return;
    }
    *result=auth_result;
    return ;
}

void changePassword(char username[], char newPassword[]) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Khong the mo file.\n");
        return;
    }

    char tempFile[] = "temp.txt";
    FILE *temp = fopen(tempFile, "w");
    if (temp == NULL) {
        printf("Khong the tao file tam thoi.\n");
        fclose(file);
        return;
    }

    char correct_username[MAX_USERNAME_LENGTH];
    char correct_password[MAX_PASSWORD_LENGTH];
    int found = 0;

    while (fscanf(file, "%49s %49s", correct_username, correct_password) == 2) {
        if (strcmp(username, correct_username) == 0) {
            fprintf(temp, "%s %s\n", username, newPassword);
            found = 1;
        } else {
            fprintf(temp, "%s %s\n", correct_username, correct_password);
        }
    }

    fclose(file);
    fclose(temp);

    if (!found) {
        printf("Ten nguoi dung khong ton tai.\n");
        remove(tempFile);
        return;
    }

    if (remove(FILENAME) != 0) {
        printf("Khong the xoa file.\n");
        remove(tempFile);
        return;
    }

    if (rename(tempFile, FILENAME) != 0) {
        printf("Khong the doi ten file tam thoi.\n");
        remove(tempFile);
        return;
    }
    system("cls");
    printf("Doi mat khau thanh cong cho tai khoan '%s'.\n", username);
}

void xoa_mon(int xoa)
{
    int c = 0;
    FILE *file = fopen("menu.txt", "r");
    FILE *file2 = fopen("tmp.txt", "w");
    char str[100];
    while(fgets(str, 100, file))
    {
        if (c == xoa)
        {
            c++;
            continue;
        }
        fwrite(str, 1, strlen(str), file2);
        c++;
    }
    fclose(file);
    fclose(file2);
    remove("menu.txt");
    rename("tmp.txt", "menu.txt");
}


void manager()
{
    int pointer;
    Manager_check(&pointer);
    print_border(75);
    if(pointer==0) return;
    if(pointer==1)
    {
    printf("1. Nhan phim \"a\" de them mon.\n");
    printf("2. Nhan phim \"b\" de thay doi gia cua cac mon.\n");
    printf("3. Nhan phim \"c\" de thay doi tinh trang cac mon an.\n");
    printf("4. Nhan phim \"d\" de xoa mon.\n");
    printf("5.Nhan phim \"m\" de xem menu hien tai.\n");
    printf("6.Nhan phim \"p\" de doi mat khau hien tai.\n");
    printf("7. Nhan phim \"0\" de ket thuc.\n");
    print_border(75);
    char tmp[1000];
    while (1)
    {
        print_border(50);
        printf("Tuy chon cua ban: ");
        fgets(tmp, 1000, stdin);
        tmp[strlen(tmp) - 1] = '\0';
        if (strcmp(tmp, "0") == 0)
        {
            print_border(75);
            system("cls");
            break;
        }
        if (strcasecmp(tmp, "d") == 0)
        {
            print_menu();
            int c = 0;
            int x;
            char xoa[100];
            while (1)
            {
                printf("Ban muon xoa mon co ma so: ");
                fgets(xoa, 100, stdin);
                xoa[strlen(xoa) - 1] = '\0';
                if (is_num(xoa))
                {
                    x = atoi(xoa);
                    x--;
                    if (x<0 || x >= menu)
                    {
                        continue;
                    }
                }
                break;
            }
            xoa_mon(x);
            read_menu();
            printf("\033[1;32m");
            printf("THANH CONG!\n");
            printf("\033[0m");
            print_border(50);
            continue;
        }
        if (strcasecmp(tmp, "m") == 0)
        {
            print_border(100);
            setlocale(LC_NUMERIC, "");
            printf("\033[1;31m");
            printf("%20s\n", "MENU:");
            printf("%20s||%20s||%20s||%20s\n", "ma so", "mon an", "gia", "trang thai");
            printf("\033[0m");
            for (int i = 0; i < menu; i++)
            {
                printf("%20d||%20s||%'20d||%20d\n", i + 1, mon[i], gia[i], trang_thai[i]);
            }
            printf("\n");
            printf(
                "******** Khuyen mai 25%% cho cac don co gia tri tu 2,000,000 tro len********\n");
            print_border(100);
            continue;
        }
        if (strcasecmp(tmp, "a") == 0)
        {
            FILE *file = fopen("menu.txt", "a");
            printf("Ten mon: ");
            fgets(tmp, 1000, stdin);
            tmp[strlen(tmp) - 1] = '\0';
            strcpy(mon[menu], tmp);
            fprintf(file, "%s, ", tmp);
            while (1)
            {
                printf("Gia: ");
                fgets(tmp, 1000, stdin);
                tmp[strlen(tmp) - 1] = '\0';
                if (is_num(tmp))
                {
                    gia[menu] = atoi(tmp);
                    fprintf(file, "%s\n", tmp);
                    break;
                }
                else
                {
                    printf("Khong hop le\n");
                }
            }
            trang_thai[menu] = 1;
            menu++;
            print_border(50);
            fclose(file);
            continue;
        }
        if (strcasecmp(tmp, "b") == 0)
        {
            print_menu();
            while (1)
            {
                printf("Ban muon thay doi gia cua mon co ma so: ");
                int check;
                int m;
                fgets(tmp, 1000, stdin);
                tmp[strlen(tmp) - 1] = '\0';
                if (is_num(tmp))
                {
                    m = atoi(tmp) - 1;
                }
                else
                {
                    printf("Khong hop le\n");
                    continue;
                }
                while (1)
                {
                    printf("Nhap gia muon thay doi: ");
                    fgets(tmp, 1000, stdin);
                    tmp[strlen(tmp) - 1] = '\0';
                    if (is_num(tmp))
                    {
                        gia[m] = atol(tmp);
                        check = 1;
                        break;
                    }
                    else
                    {
                        printf("Khong hop le\n");
                    }
                }
                if (check == 1)
                {
                    break;
                }
            }
            FILE *file = fopen("menu.txt", "w");
            for (int i = 0; i < menu; i++)
            {
                fprintf(file, "%s, %d\n", mon[i], gia[i]);
            }
            fclose(file);
            print_border(50);
            continue;
        }
        if (strcasecmp(tmp, "p") == 0)
        {
            system("cls");
            char username[MAX_USERNAME_LENGTH];
            char password[MAX_PASSWORD_LENGTH];
            printf("     Nhap ten tai khoan: ");
           fgets(username, MAX_USERNAME_LENGTH, stdin);
            username[strcspn(username, "\n")] = '\0';
            printf("     Nhap mat khau     : ");
            fgets(password, MAX_PASSWORD_LENGTH, stdin);
            password[strcspn(password, "\n")] = '\0';
            changePassword(username,password);
            print_border(50);
            break;
        }
        if (strcasecmp(tmp, "c") == 0)
        {
            print_border(100);
            setlocale(LC_NUMERIC, "");
            printf("\033[1;31m");
            printf("%20s\n", "MENU:");
            printf("%20s||%20s||%20s||%20s\n", "ma so", "mon an", "gia", "trang thai");
            printf("\033[0m");
            for (int i = 0; i < menu; i++)
            {
                printf("%20d||%20s||%'20d||%20d\n", i + 1, mon[i], gia[i], trang_thai[i]);
            }
            printf("\n");
            printf(
                "******** Khuyen mai 25%% cho cac don co gia tri tu 2,000,000 tro len********\n");
            print_border(100);
            while (1)
            {
                printf("Ban muon thay doi trang thai cua mon co ma so: ");
                int m;
                fgets(tmp, 1000, stdin);
                tmp[strlen(tmp) - 1] = '\0';
                if (is_num(tmp))
                {
                    m = atoi(tmp) - 1;
                }
                else
                {
                    printf("Khong hop le\n");
                    continue;
                }
                if (m >= menu || m < 0)
                {
                    printf("Khong co mon an do\n");
                    continue;
                }
                if (trang_thai[m] == 1)
                {
                    trang_thai[m] = 0;
                    break;
                }
                else
                {
                    trang_thai[m] = 1;
                    break;
                }
            }
            print_border(50);
            continue;
        }
    }
}
    else
    if(pointer==2)
    {
    printf("1. Nhan phim \"a\" de them mon.\n");
    printf("2. Nhan phim \"b\" de thay doi tinh trang cac mon an.\n");
    printf("3.Nhan phim \"m\" de xem menu hien tai.\n");
    printf("4.Nhan phim \"p\" de doi mat khau hien tai.\n");
    printf("5. Nhan phim \"0\" de ket thuc.\n");
    print_border(75);
    char tmp[1000];
    while (1)
    {
        print_border(50);
        printf("Tuy chon cua ban: ");
        fgets(tmp, 1000, stdin);
        tmp[strlen(tmp) - 1] = '\0';
        if (strcmp(tmp, "0") == 0)
        {
            print_border(75);
            system("cls");
            break;
        }
        if (strcasecmp(tmp, "m") == 0)
        {
            print_border(100);
            setlocale(LC_NUMERIC, "");
            printf("\033[1;31m");
            printf("%20s\n", "MENU:");
            printf("%20s||%20s||%20s||%20s\n", "ma so", "mon an", "gia", "trang thai");
            printf("\033[0m");
            for (int i = 0; i < menu; i++)
            {
                printf("%20d||%20s||%'20d||%20d\n", i + 1, mon[i], gia[i], trang_thai[i]);
            }
            printf("\n");
            printf(
                "******** Khuyen mai 25%% cho cac don co gia tri tu 2,000,000 tro len********\n");
            print_border(100);
            continue;
        }
        if (strcasecmp(tmp, "a") == 0)
        {
            FILE *file = fopen("menu.txt", "a");
            printf("Ten mon: ");
            fgets(tmp, 1000, stdin);
            tmp[strlen(tmp) - 1] = '\0';
            strcpy(mon[menu], tmp);
            fprintf(file, "%s, ", tmp);
            while (1)
            {
                printf("Gia: ");
                fgets(tmp, 1000, stdin);
                tmp[strlen(tmp) - 1] = '\0';
                if (is_num(tmp))
                {
                    gia[menu] = atoi(tmp);
                    fprintf(file, "%s\n", tmp);
                    break;
                }
                else
                {
                    printf("Khong hop le\n");
                }
            }
            trang_thai[menu] = 1;
            menu++;
            print_border(50);
            fclose(file);
            continue;
        }
         if (strcasecmp(tmp, "p") == 0)
        {
            system("cls");
            char username[MAX_USERNAME_LENGTH];
            char password[MAX_PASSWORD_LENGTH];
            printf("     Nhap ten tai khoan: ");
           fgets(username, MAX_USERNAME_LENGTH, stdin);
            username[strcspn(username, "\n")] = '\0';
            printf("     Nhap mat khau     : ");
            fgets(password, MAX_PASSWORD_LENGTH, stdin);
            password[strcspn(password, "\n")] = '\0';
            changePassword(username,password);
            print_border(50);
            break;
        }
        if (strcasecmp(tmp, "b") == 0)
        {
            print_border(100);
            setlocale(LC_NUMERIC, "");
            printf("\033[1;31m");
            printf("%20s\n", "MENU:");
            printf("%20s||%20s||%20s||%20s\n", "ma so", "mon an", "gia", "trang thai");
            printf("\033[0m");
            for (int i = 0; i < menu; i++)
            {
                printf("%20d||%20s||%'20d||%20d\n", i + 1, mon[i], gia[i], trang_thai[i]);
            }
            printf("\n");
            printf(
                "******** Khuyen mai 25%% cho cac don co gia tri tu 2,000,000 tro len********\n");
            print_border(100);
            while (1)
            {
                printf("Ban muon thay doi trang thai cua mon co ma so: ");
                int m;
                fgets(tmp, 1000, stdin);
                tmp[strlen(tmp) - 1] = '\0';
                if (is_num(tmp))
                {
                    m = atoi(tmp) - 1;
                }
                else
                {
                    printf("Khong hop le\n");
                    continue;
                }
                if (m >= menu || m < 0)
                {
                    printf("Khong co mon an do\n");
                    continue;
                }
                if (trang_thai[m] == 1)
                {
                    trang_thai[m] = 0;
                    break;
                }
                else
                {
                    trang_thai[m] = 1;
                    break;
                }
            }
            print_border(50);
            continue;
        }
    }
}
}
void luu_don_hang()
{
    char str[1000];
    print_border(100);
    printf(" %60s "," CAM ON QUY KHACH \n");
    print_border(100);
        while(1)
        {
                    printf("\033[1;34m");
                    printf("Ban co muon luu hoa don khong? [Y/N]: ");
                    printf("\033[0m");
                    fgets(str, 1000, stdin);
                    str[strlen(str)-1] = '\0';
                    if (strcasecmp(str, "Y") == 0)
                    {
                        luu_ngay();
                        system("cls");
                        printf("\033[1;32m");
                        printf(" \n %40s","  Da luu hoa don thanh cong \n");
                        printf("\033[0m");
                        print_border(50);
                        break;
                    }
                    else if (strcasecmp(str, "N") == 0)
                    {
                        system("cls");
                        printf("\033[1;31m");
                        printf("\n %40s","Don hang chua duoc luu \n");
                        printf("\033[0m");
                        print_border(50);
                        break;
                    }
            }
}
void print_hoadon()
{
    double A[menu];
    for (int i = 0; i < menu; i++)
    {
        A[i] = 0;
    }
    unsigned long long int tong_da_thu = 0;
    unsigned long long int tong_chua_thu = 0;
    printf("\n");
    print_border(100);
    for (int i = 0; i < count_donhang; i++)
    {
        printf( "      Ma hoa don: %03d\n", i+1);
        printf( "      %20s||%20s||%20s||%20s||\n", "Ma mon an", "Mon an", "So luong", "Thanh Tien");
        for (int k = 0; k < LIMIT; k++)
        {
            if (donhang[i].mon[k] != -1)
            {
                printf( "      %20d||%20s||%20ld||%'20ld||\n", donhang[i].mon[k]+1,mon[k], donhang[i].so_luong[k], donhang[i].so_luong[k]*gia[donhang[i].mon[k]]);
                A[donhang[i].mon[k]] += donhang[i].so_luong[k];
            }
        }
        printf( "%72s %'22ld\n", "Tong: ", donhang[i].tong);
        printf( "%72s %'22.0lf\n", "Khuyen mai: ", donhang[i].khuyen_mai);
        printf( "%72s %'22.0lf\n", "Thanh tien: ", donhang[i].thanh_tien);
        printf( "%83s ", "Trang Thai:            " );
        if(donhang[i].status==1) printf(" DA THANH TOAN \n\n");
        else printf(" CHUA THANH TOAN \n\n");
        if (donhang[i].status != 0)
        {
            printf("%80s %20s\n", "Nhan vien thu ngan: ", donhang[i].staff);
        }
        if (donhang[i].status == 1)
        {
            tong_da_thu += donhang[i].thanh_tien;
        }
        else
        {
            tong_chua_thu += donhang[i].thanh_tien;
        }
    }
}

void thanh_toan()
{
    while (1)
    {
        printf("\n----------------------------------- Danh sach cac don chua thanh toan: --------------------------------\n");
        {
            printf("%20s||%20s||%20s\n", "Ma so", "Ban", "Thanh tien");
            for (int i = 0; i < count_donhang; i++)
            {
                if (donhang[i].status == 0)
                {
                    printf("%17s%03d||%20d||%'20ld\n", "", i+1, donhang[i].ban, donhang[i].tong);
                }
            }
        }
        printf("\033[1;36m");
        printf("Nhap ma don hang ban muon thanh toan hoac nhan phim \"0\" de quay lai goi mon: ");
        printf("\033[0m");
        char str[1000];
        fgets(str, 1000, stdin);
        str[strlen(str)-1] = '\0';
        if (strcmp(str, "0") == 0)
        {
            print_border(100);
            break;
        }
        if (is_num(str))
        {
            int ma_don = atoi(str);
            if (ma_don >= (count_donhang+1) || (ma_don) <= 0)
            {
                printf("\033[1;31m");
                printf("Khong co don hang ban tim\n");
                printf("\033[0m");
                continue;
            }
            else
            {
                if (donhang[ma_don-1].status == 1)
                {
                    printf("\033[1;34m");
                    printf("Don hang da duoc thanh toan\n");
                    printf("\033[0m");
                    print_border(100);
                }
                else
                {
                    int count = 0;
                    print_border(50);
                    printf("\033[1;31m");
                    printf("Ma hoa don: %03d\n\n", ma_don);
                    printf("%20s||%20s||%20s||\n", "Ma so", "So luong", "Thanh Tien");
                    printf("\033[0m");
                    for (int k = 0; k < LIMIT; k++)
                    {
                        if (donhang[ma_don-1].mon[k] != -1)
                        {
                            printf("%20d||%20ld||%'20ld||\n", donhang[ma_don-1].mon[k]+1, donhang[ma_don-1].so_luong[k], donhang[ma_don-1].so_luong[k]*gia[donhang[ma_don-1].mon[k]]);
                            count++;
                        }
                    }
                    printf("\n%43s %'22ld\n", "Tong: ", donhang[ma_don-1].tong);
                    printf("%43s %'22.0lf\n", "Khuyen mai: ", donhang[ma_don-1].khuyen_mai);
                    printf("%43s %'22.0lf\n\n", "Thanh tien: ", donhang[ma_don-1].thanh_tien);
                    print_border(50);
                    printf("\033[1;34m");
                    printf("Ban co muon sua khong? [Y/N]: ");
                    printf("\033[0m");
                    fgets(str, 1000, stdin);
                    str[strlen(str)-1] = '\0';
                    if (strcasecmp(str, "Y") == 0)
                    {
                        char tmp[1000];
                        int a[2];
                        printf("\033[1;35m");
                        printf("Ban duoc chon toi da %d mon, cu phap la ma mon an va so luong (VD:1 1), nhap \"0 0\" neu muon dung goi mon\n", LIMIT);
                        printf("\033[0m");
                        print_border(50);
                        while (1)
                        {
                            int stt0 = 0;
                            printf("So mon hien tai cua ban la %i (nhap \"e\" neu ban muon xoa hoac sua mon an hoac nhap \"m\" neu ban muon xem cac mon ban da dat): ",count);
                            fgets(tmp, 1000, stdin);
                            tmp[strlen(tmp) - 1] = '\0';
                            if (strcmp(tmp, "0 0") == 0 && count == 0)
                            {
                                printf("\033[1;31m");
                                printf("Ban chua dat mon an nao\n");
                                printf("\033[0m");
                                print_border(35);
                                continue;
                            }
                            if (strcasecmp(tmp, "menu") == 0)
                            {
                                print_menu();
                                continue;
                            }
                            if (strcmp(tmp, "0 0") == 0)
                            {
                                print_border(35);
                                break;
                            }
                            if (strcasecmp(tmp, "e") == 0)
                            {
                                if (count == 0)
                                {
                                    printf("\033[1;31m");
                                    printf("Ban chua co mon an nao\n");
                                    printf("\033[0m");
                                    continue;
                                }
                                int stt = 1;
                                print_border(50);
                                printf("\033[1;31m");
                                printf("Don hang hien tai: \n");
                                printf("%20s||%20s||%20s||%20s||%20s||%20s||\n", "STT", "Ma so", "Mon an", "Don gia", "So luong", "Thanh Tien");
                                printf("\033[0m");
                                for (int k = 0; k < LIMIT; k++)
                                {
                                    if (donhang[ma_don-1].mon[k] != -1)
                                    {
                                        printf("%20d||%20d||%20s||%'20d||%20ld||%'20ld||\n", stt,
                                            donhang[ma_don-1].mon[k] + 1, mon[donhang[ma_don-1].mon[k]],
                                            gia[donhang[ma_don-1].mon[k]], donhang[ma_don-1].so_luong[k],
                                            donhang[ma_don-1].so_luong[k] * gia[donhang[ma_don-1].mon[k]]);
                                        stt++;
                                    }
                                }
                                printf("\033[1;35m");
                                printf("Ban muon sua hoac xoa mon co STT: ");
                                printf("\033[0m");
                                char inp[1000];
                                int stt2;
                                do
                                {
                                    int check = 0;
                                    fgets(inp, 1000, stdin);
                                    inp[strlen(inp) - 1] = '\0';
                                    if (is_num(inp))
                                    {
                                        stt2 = atoi(inp);
                                        if (stt2 < 1 || stt2 > count)
                                        {
                                            printf("\033[1;31m");
                                            printf("STT khong dung \n");
                                            printf("\033[0m");
                                            continue;
                                        }
                                        stt = 1;
                                        for (int i = 0; i < LIMIT; i++)
                                        {
                                            if (donhang[ma_don-1].mon[i] != -1)
                                            {
                                                if (stt == stt2)
                                                {
                                                    stt = i;
                                                    break;
                                                }
                                                stt++;
                                            }
                                        }
                                        printf("\033[1;35m");
                                        printf("Neu muon xoa hay bam \"d\" hoac bam nut bat ki de sua: ");
                                        printf("\033[0m");
                                        while (1)
                                        {
                                            fgets(inp, 1000, stdin);
                                            inp[strlen(inp) - 1] = '\0';
                                            if (strcasecmp(inp, "d") == 0)
                                            {
                                                donhang[ma_don-1].tong -= gia[donhang[ma_don-1].mon[stt]] * donhang[ma_don-1].so_luong[stt];
                                                donhang[ma_don-1].mon[stt] = -1;
                                                donhang[ma_don-1].mon[stt] = -1;
                                                count--;
                                                check = 1;
                                                printf("\033[1;32m");
                                                printf("Da xoa\n");
                                                printf("\033[0m");
                                                print_border(50);
                                                break;
                                            }
                                            else
                                            {
                                                while (1)
                                                {
                                                    printf("\033[1;35m");
                                                    printf("Nhap cu phap de goi mon moi: ");
                                                    printf("\033[0m");
                                                    fgets(inp, 1000, stdin);
                                                    inp[strlen(inp) - 1] = '\0';
                                                    if (get_data(inp, a) == 0)
                                                    {
                                                        printf("\033[1;31m");
                                                        printf("Ban nhap sai cu phap\n");
                                                        printf("\033[0m");
                                                        print_border(35);
                                                        continue;
                                                    }
                                                    a[0]--;
                                                    if (a[0] < 0 || a[0] >= menu || trang_thai[a[0]] == 0)
                                                    {
                                                        printf("\033[1;31m");
                                                        printf("Ma mon an khong dung\n");
                                                        printf("\033[0m");
                                                        print_border(35);
                                                        continue;
                                                    }
                                                    if (a[1] <= 0)
                                                    {
                                                        printf("\033[1;31m");
                                                        printf("So luong khong hop le\n");
                                                        printf("\033[0m");
                                                        print_border(35);
                                                        continue;
                                                    }
                                                    donhang[ma_don-1].tong -= gia[donhang[ma_don-1].mon[stt]] * donhang[ma_don-1].so_luong[stt];
                                                    donhang[ma_don-1].mon[stt] = a[0];
                                                    donhang[ma_don-1].so_luong[stt] = a[1];
                                                    donhang[ma_don-1].tong += a[1] * gia[a[0]];
                                                    printf("\033[1;35m");
                                                    printf("Ban da goi mon %s voi so luong la %d\n", mon[a[0]], a[1]);
                                                    printf("\033[0m");
                                                    print_border(50);
                                                    check = 1;
                                                    break;
                                                }
                                                break;
                                            }
                                        }
                                    }
                                    if (check == 1)
                                    {
                                        break;
                                    }
                                }
                                while (1);
                                continue;
                            }
                            if (strcasecmp(tmp, "m") == 0)
                            {
                                if (count == 0)
                                {
                                    print_border(50);
                                    printf("\033[1;31m");
                                    printf("Ban chua dat mon an nao\n");
                                    printf("\033[0m");
                                    print_border(50);
                                    continue;
                                }
                                int stt = 1;
                                print_border(50);
                                printf("\033[1;31m");
                                printf("Don hang hien tai: \n");
                                printf("%20s||%20s||%20s||%20s||%20s||%20s||\n", "STT", "Ma so", "Mon an", "Don gia", "So luong", "Thanh Tien");
                                printf("\033[0m");
                                for (int k = 0; k < LIMIT; k++)
                                {
                                    if (donhang[ma_don-1].mon[k] != -1)
                                    {
                                        printf("%20d||%20d||%20s||%'20d||%20ld||%'20ld||\n", stt,
                                            donhang[ma_don-1].mon[k] + 1, mon[donhang[ma_don-1].mon[k]],
                                            gia[donhang[ma_don-1].mon[k]], donhang[ma_don-1].so_luong[k],
                                            donhang[ma_don-1].so_luong[k] * gia[donhang[ma_don-1].mon[k]]);
                                            stt++;
                                    }
                                }
                                print_border(50);
                                continue;
                            }
                            if (count == LIMIT)
                            {
                                printf("So mon an da dat gioi han\n");
                                print_border(35);
                                continue;
                            }
                            if (get_data(tmp, a) == 0)
                            {
                                printf("\033[1;31m");
                                printf("Ban nhap sai cu phap\n");
                                printf("\033[0m");
                                print_border(35);
                                continue;
                            }
                            a[0]--;
                            if (a[0] < 0 || a[0] >= menu || trang_thai[a[0]] == 0)
                            {
                                printf("\033[1;31m");
                                printf("Ma mon an khong dung\n");
                                printf("\033[0m");
                                print_border(35);
                                continue;
                            }
                            if (a[1] <= 0)
                            {
                                printf("\033[1;31m");
                                printf("So luong khong hop le\n");
                                printf("\033[0m");
                                print_border(35);
                                continue;
                            }
                            for (int i = 0; i < LIMIT; i++)
                            {
                                if (donhang[ma_don-1].mon[i] == -1)
                                {
                                    stt0 = i;
                                    break;
                                }
                            }
                            donhang[ma_don-1].mon[stt0] = a[0];
                            donhang[ma_don-1].so_luong[stt0] = a[1];
                            donhang[ma_don-1].tong += a[1] * gia[a[0]];
                            printf("\033[1;32m");
                            printf("Ban da goi mon %s voi so luong la %d\n", mon[a[0]], a[1]);
                            printf("\033[0m");
                            print_border(35);
                            count++;
                        }
                        // them 1 buoc de tinh tong hoa don o day//
                        if (donhang[ma_don-1].tong >= 2000000)
                        {
                            donhang[ma_don-1].khuyen_mai = donhang[ma_don-1].tong * 0.25;
                            donhang[ma_don-1].thanh_tien = donhang[ma_don-1].tong - donhang[ma_don-1].khuyen_mai;
                        }
                        else
                        {
                            donhang[ma_don-1].khuyen_mai = 0;
                            donhang[ma_don-1].thanh_tien = donhang[ma_don-1].tong;
                        }
                    }
                    print_border(50);
                    printf("\033[1;31m");
                    printf("Ma hoa don: %03d\n\n", ma_don);
                    printf("%20s||%20s||%20s||\n", "Ma so", "So luong", "Thanh Tien");
                    printf("\033[0m");
                    for (int k = 0; k < LIMIT; k++)
                    {
                        if (donhang[ma_don-1].mon[k] != -1)
                        {
                            printf("%20d||%20ld||%'20ld||\n", donhang[ma_don-1].mon[k]+1, donhang[ma_don-1].so_luong[k], donhang[ma_don-1].so_luong[k]*gia[donhang[ma_don-1].mon[k]]);
                            count++;
                        }
                    }
                    printf("\n%43s %'22ld\n", "Tong: ", donhang[ma_don-1].tong);
                    printf("%43s %'22.0lf\n", "Khuyen mai: ", donhang[ma_don-1].khuyen_mai);
                    printf("%43s %'22.0lf\n\n", "Thanh tien: ", donhang[ma_don-1].thanh_tien);
                    print_border(50);
                    printf("\033[1;34m");
                    printf("Ban co muon thanh toan khong? [Y/N]: ");
                    printf("\033[0m");
                    fgets(str, 1000, stdin);
                    str[strlen(str)-1] = '\0';
                    if (strcasecmp(str, "Y") == 0)
                    {
                        printf("Nhan vien thu tien: ");
                        fgets(str, 1000, stdin);
                        str[strlen(str) - 1] = '\0';
                        strcpy(donhang[ma_don-1].staff, str);
                        donhang[ma_don-1].status = 1;
                        printf("\033[1;32m");
                        printf("Ban da thanh toan don hang ma so %03d\n", ma_don);
                        printf("\033[0m");
                        print_border(50);
                        break;
                    }
                    else if (strcasecmp(str, "N") == 0)
                    {
                        donhang[ma_don-1].status = 0;
                        printf("\033[1;31m");
                        printf("Ban chua thanh toan don hang ma so %03d\n", ma_don);
                        printf("\033[0m");
                        print_border(50);
                        break;
                    }
                }
            }
        }
    }
}

int main(void)
{
    read_menu();
    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);
    while (1)
    {
        int check = nhap_ma();
        if (check == 3)
        {
            printf("\n*********************** Ban da mo tuy chon danh cho quan li: "
                   "***********************\n");
            manager();
            continue;
        }
        if (check == 1 && status == 1)
        {
            system("cls");
            printf("Ket thuc 1 ngay :%d-%d-%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
            print_hoadon();
            luu_don_hang();
            printf("\n");
            break;
        }
        if (check == 1 && status == 0)
        {
            system("cls");
            printf("Ngay moi bat dau : %d-%d-%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
            printf("\n");
            print_border(50);
            status = 1;
            continue;
        }
        if (status == 1 && check == 2)
        {
            thanh_toan();
        }
        else if (status == 1)
        {
            print_menu();
            nhap_don_hang();
        }
    }
    return 0;
}
