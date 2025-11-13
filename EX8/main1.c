// 整合版：HW3第1題 + CS8第43頁第1題
// Step 1: 產生 lotto.txt
// Step 2: 讀取 lotto.txt 並判斷輸入的三個號碼是否中獎

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *fp;
    int n;
    int lotto[5][7];
    int i, j, k, repeat;
    time_t now;
    struct tm *t;

    srand(2025); // 固定亂數種子

    printf("請輸入要購買的樂透組數 (1~5)：");
    scanf("%d", &n);
    if (n < 1 || n > 5) n = 5;

    // === 產生 lotto.txt ===
    fp = fopen("lotto.txt", "w");

    time(&now);
    t = localtime(&now);
    fprintf(fp, "========= lotto649 =========\n");
    fprintf(fp, "======= %04d/%02d/%02d %02d:%02d:%02d =======\n",
            t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
            t->tm_hour, t->tm_min, t->tm_sec);

    for (i = 0; i < 5; i++) {
        fprintf(fp, "[%d]: ", i + 1);
        if (i < n) {
            for (j = 0; j < 7; j++) {
                do {
                    lotto[i][j] = rand() % 69 + 1;
                    repeat = 0;
                    for (k = 0; k < j; k++) {
                        if (lotto[i][j] == lotto[i][k])
                            repeat = 1;
                    }
                } while (repeat);
            }
            // 排序
            for (j = 0; j < 6; j++) {
                for (k = j + 1; k < 7; k++) {
                    if (lotto[i][j] > lotto[i][k]) {
                        int tmp = lotto[i][j];
                        lotto[i][j] = lotto[i][k];
                        lotto[i][k] = tmp;
                    }
                }
            }
            for (j = 0; j < 7; j++)
                fprintf(fp, "%02d ", lotto[i][j]);
        } else {
            for (j = 0; j < 7; j++)
                fprintf(fp, "-- ");
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "========= csie@CGU =========\n");
    fclose(fp);

    printf("已產生 lotto.txt 完成。\n");

    // === 判斷中獎部分 ===
    int a, b, c;
    int num, found = 0;
    int countA, countB, countC;

    printf("輸入三個號碼: ");
    scanf("%d %d %d", &a, &b, &c);

    fp = fopen("lotto.txt", "r");
    if (fp != NULL) {
        char line[256];

        // 跳過前兩行標題
        fgets(line, sizeof(line), fp);
        fgets(line, sizeof(line), fp);

        // 逐行檢查五張彩券
        for (i = 0; i < 5; i++) {
            countA = countB = countC = 0;
            fscanf(fp, "%*[^:]:"); // 略過 [i]:

            for (j = 0; j < 7; j++) {
                char token[4];
                if (fscanf(fp, "%s", token) == 1) {
                    if (token[0] != '-') {
                        sscanf(token, "%d", &num);
                        if (num == a) countA = 1;
                        if (num == b) countB = 1;
                        if (num == c) countC = 1;
                    }
                }
            }
            if (countA && countB && countC) {
                found = 1;
                break;
            }
        }
        fclose(fp);
    }

    if (found)
        printf("恭喜中獎! 這三個號碼同時出現在同一張彩券上!\n");
    else
        printf("這三個號碼沒有同時出現在同一張彩券上。\n");

    return 0;
}
