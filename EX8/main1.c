#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_NUMBERS 7
#define MAX_LENGTH 100

typedef struct {
    int numbers[MAX_NUMBERS];
    char date[MAX_LENGTH];
    int index;
} LotteryTicket;

int main() {
    FILE *file = fopen("lotto.txt", "r");
    if (file == NULL) {
        printf("無法開啟檔案 lotto.txt\n");
        return 1;
    }

    LotteryTicket tickets[MAX_LINES];
    int ticket_count = 0;
    char line[MAX_LENGTH];
    int line_num = 0;

    // 讀取檔案內容
    while (fgets(line, sizeof(line), file) != NULL && ticket_count < MAX_LINES) {
        line_num++;
        
        // 跳過標題行和空白行
        if (line_num == 1 || line_num == 2 || line_num == 8 || line_num == 9) {
            continue;
        }

        // 解析彩票數據行
        if (line_num >= 3 && line_num <= 7) {
            char *token;
            int num_count = 0;
            
            // 複製一行以便處理
            char line_copy[MAX_LENGTH];
            strcpy(line_copy, line);
            
            // 解析 [n]: 格式
            token = strtok(line_copy, " :");
            if (token != NULL && token[0] == '[') {
                tickets[ticket_count].index = atoi(&token[1]);
                
                // 讀取數字
                while ((token = strtok(NULL, " ")) != NULL && num_count < MAX_NUMBERS) {
                    if (strlen(token) > 0) {
                        tickets[ticket_count].numbers[num_count] = atoi(token);
                        num_count++;
                    }
                }
                
                // 讀取日期（從前一行）
                strcpy(tickets[ticket_count].date, "March 13 2025");
                ticket_count++;
            }
        }
    }
    fclose(file);

    // 獲取用戶輸入的中獎號碼
    int win_numbers[3];
    printf("請輸入中獎號碼三個： ");
    scanf("%d %d %d", &win_numbers[0], &win_numbers[1], &win_numbers[2]);
    
    printf("輸入中獎號碼為：%02d %02d %02d\n", 
           win_numbers[0], win_numbers[1], win_numbers[2]);
    printf("以下為中獎彩卷：\n");

    // 檢查每張彩票是否包含所有中獎號碼
    int found_winner = 0;
    for (int i = 0; i < ticket_count; i++) {
        int match_count = 0;
        
        // 檢查每個中獎號碼是否在當前彩票中
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < MAX_NUMBERS; k++) {
                if (tickets[i].numbers[k] == win_numbers[j]) {
                    match_count++;
                    break;
                }
            }
        }
        
        // 如果三個號碼都匹配，則中獎
        if (match_count == 3) {
            printf("售出時間：%s: [%d]: ", tickets[i].date, tickets[i].index);
            for (int k = 0; k < MAX_NUMBERS; k++) {
                printf("%02d ", tickets[i].numbers[k]);
            }
            printf("\n");
            found_winner = 1;
        }
    }

    if (!found_winner) {
        printf("沒有中獎彩卷\n");
    }

    return 0;
}
