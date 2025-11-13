#include <stdio.h>

#include <stdlib.h>

int main(void) {

    int win1, win2, win3;

    int n;

    int tickets_data[5][7];

    int ticket_ids[5];

    int i, j, k;

    FILE *fp;

    /* --- Part 1: 產生樂透號碼 --- */

    printf("請輸入購買組數 (1-5)： ");

    scanf("%d", &n);

    srand(2025);

    fp = fopen("lotto.txt", "w");

    if (fp == NULL) {

        printf("無法開啟檔案 lotto.txt\n");

        return 1;

    }

    for (i = 0; i < n; i++) {

        ticket_ids[i] = i + 1;

        fprintf(fp, "[%d]:", ticket_ids[i]);

        for (j = 0; j < 7; j++) {

            int new_num;

            int is_duplicate;

            do {

                is_duplicate = 0;

                new_num = (rand() % 69) + 1;

                for (k = 0; k < j; k++) {

                    if (tickets_data[i][k] == new_num) {

                        is_duplicate = 1;

                        break;

                    }

                }

            } while (is_duplicate);

            // ====================================================

            // 

            //         !! 這 是 你 遺 失 的 關 鍵 一 行 !!

            //  

            //         它必須把號碼存到陣列(記憶體)中

            //

            tickets_data[i][j] = new_num;

            //

            // ====================================================

            // 寫入檔案

            fprintf(fp, " %02d", tickets_data[i][j]);

        }

        fprintf(fp, "\n");

    }

    fclose(fp);

    /* --- Part 2: 對獎 --- */

    printf("請輸入中獎號碼三個： ");

    scanf("%d %d %d", &win1, &win2, &win3);

    printf("輸入中獎號碼為： %02d %02d %02d\n", win1, win2, win3);

    printf("以下為中獎彩券：\n");

    // 這個迴圈會檢查 "記憶體" 中的 tickets_data 陣列

    for (i = 0; i < n; i++) {

        int match_found = 0;

        for (j = 0; j < 7; j++) {

            if (tickets_data[i][j] == win1 || tickets_data[i][j] == win2 || tickets_data[i][j] == win3) {

                match_found = 1;

                break;

            }

        }

        if (match_found == 1) {

            printf("售出時間： March 13 2025: [%d]:", ticket_ids[i]);

            for (k = 0; k < 7; k++) {

                printf(" %02d", tickets_data[i][k]);

            }

            printf("\n");

        }

    }

    return 0;

}
 
