// cs8 第43頁 第一題
// 讀取 hw3 產生的 lotto.txt
// 與簡報輸出格式一致

#include <stdio.h>

int main() {
    FILE *fp = fopen("lotto.txt", "r");
    int a, b, c;
    int num;
    int found = 0;
    int countA, countB, countC;

    printf("輸入三個號碼: ");
    scanf("%d %d %d", &a, &b, &c);

    if (fp != NULL) {
        char line[256];

        // 跳過前兩行標題
        fgets(line, sizeof(line), fp);
        fgets(line, sizeof(line), fp);

        // 逐行檢查五張彩券
        for (int i = 0; i < 5; i++) {
            countA = countB = countC = 0;

            // 讀掉 "[i]:" 這部分
            fscanf(fp, "%*[^:]:");

            for (int j = 0; j < 7; j++) {
                char token[4];
                if (fscanf(fp, "%s", token) == 1) {
                    if (token[0] != '-') { // "--" 代表沒買
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
