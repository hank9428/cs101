// main2.c
// 每次執行：
// 1) 檢查 counter.bin（如無則建立並寫 0）
// 2) 讀取 counter (已賣出單數)
// 3) counter++，以此數字生成 lotto[NNNNN].txt（檔名 5 位數填零）
// 4) 產生一組彩卷（6 個不重複號碼，1..49），排序，輸出到檔案與同目錄下的 "lotto.txt"（可手動整合到 hw3）
// 5) 將新的 counter 寫回 counter.bin

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define COUNTER_FILE "counter.bin"
#define OUTPUT_PREFIX "lotto"
#define TICKET_NUM_PER_FILE 1    // 每個 lotto[xxxxx].txt 放多少組（可改）
#define NUM_PER_TICKET 6
#define MAX_BALL 49

// initialize counter.bin if not exists
void init_counter_if_needed(void) {
    FILE *f = fopen(COUNTER_FILE, "rb");
    if (!f) {
        // create with zero
        f = fopen(COUNTER_FILE, "wb");
        if (!f) { perror("建立 counter.bin 失敗"); exit(1); }
        int zero = 0;
        fwrite(&zero, sizeof(int), 1, f);
        fclose(f);
    } else {
        fclose(f);
    }
}

// read counter
int read_counter(void) {
    FILE *f = fopen(COUNTER_FILE, "rb");
    if (!f) { perror("讀 counter.bin 失敗"); exit(1); }
    int counter;
    if (fread(&counter, sizeof(int), 1, f) != 1) {
        fclose(f); perror("讀取 counter 失敗"); exit(1);
    }
    fclose(f);
    return counter;
}

// write counter
void write_counter(int c) {
    FILE *f = fopen(COUNTER_FILE, "wb");
    if (!f) { perror("寫 counter.bin 失敗"); exit(1); }
    if (fwrite(&c, sizeof(int), 1, f) != 1) { perror("寫入 counter 失敗"); fclose(f); exit(1); }
    fclose(f);
}

// check if value exists in array
int contains(int arr[], int n, int val) {
    for (int i=0;i<n;i++) if (arr[i]==val) return 1;
    return 0;
}

// generate one ticket (NUM_PER_TICKET numbers, unique), sorted ascending
void generate_ticket(int ticket[]) {
    int count = 0;
    while (count < NUM_PER_TICKET) {
        int v = (rand() % MAX_BALL) + 1; // 1..MAX_BALL
        if (!contains(ticket, count, v)) {
            ticket[count++] = v;
        }
    }
    // simple sort (NUM_PER_TICKET small)
    for (int i=0;i<NUM_PER_TICKET-1;i++) {
        for (int j=i+1;j<NUM_PER_TICKET;j++) {
            if (ticket[i] > ticket[j]) {
                int tmp = ticket[i]; ticket[i]=ticket[j]; ticket[j]=tmp;
            }
        }
    }
}

// format filename lotto[00001].txt
void make_filename(int counter, char *out, size_t outlen) {
    snprintf(out, outlen, "%s[%05d].txt", OUTPUT_PREFIX, counter);
}

int main(void) {
    srand((unsigned)time(NULL)); // 如果需要固定亂數改為 srand(1);

    init_counter_if_needed();
    int counter = read_counter(); // 讀取已賣出的數量
    counter++; // 本次賣出 -> 新的單號

    char fname[128];
    make_filename(counter, fname, sizeof(fname));

    FILE *f = fopen(fname, "w");
    if (!f) { perror("開檔失敗"); return 1; }

    // 寫入檔頭（與 hw3 類似格式）
    fprintf(f, "========= lotto649 =========\n");
    for (int t = 1; t <= TICKET_NUM_PER_FILE; ++t) {
        int ticket[NUM_PER_TICKET] = {0};
        generate_ticket(ticket);
        fprintf(f, "[%d]:", t);
        for (int i=0;i<NUM_PER_TICKET;i++) {
            fprintf(f, " %02d", ticket[i]);
        }
        fprintf(f, "\n");
    }
    fclose(f);

    // (選擇) 同步更新 / 產生一份總合的 lotto.txt（若 hw3 需要）
    FILE *master = fopen("lotto.txt", "w");
    if (master) {
        fprintf(master, "========= lotto649 =========\n");
        for (int t = 1; t <= TICKET_NUM_PER_FILE; ++t) {
            // 重新產生同樣格式輸出；要注意：若需與個別檔案完全一致，請改成從檔案讀回
            int ticket[NUM_PER_TICKET] = {0};
            generate_ticket(ticket);
            fprintf(master, "[%d]:", t);
            for (int i=0;i<NUM_PER_TICKET;i++) fprintf(master, " %02d", ticket[i]);
            fprintf(master, "\n");
        }
        fclose(master);
    } else {
        // not critical
    }

    // write back counter
    write_counter(counter);

    printf("已產生 %s （本次單號 %05d）。\n", fname, counter);
    printf("counter.bin 已更新為 %d。\n", counter);

    return 0;
}
