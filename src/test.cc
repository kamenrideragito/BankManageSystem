#include "MissionController.h"

int main() {
    mission::dataPack *data = new mission::dataPack;
    strcpy(data->cardid, "0000000001");
    data->operation = char(2);
    data->amount = 0;

    while(1) {
        mission::Receipt *result = new mission::Receipt;
        mission::parsing(*data, result); 
        printf("success: %d\n", result->success);
        printf("%s\n", result->account.id);
        sleep(3);
        delete result;
    }

    return 0;
}
