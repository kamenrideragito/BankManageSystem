// Author:     Hermit
// CreateTime: Mar 12, 2019 10:49 AM
// Eamil:      LasNoire23@gmail.com
// MyPage:     None

#pragma once
#include <sys/types.h>
#include <sys/stat.h>

#include "DBController.h"
#include "Account.h"
#include "ProjectTool.h"
namespace mission
{
enum class OPERATION:unsigned char {
    SAVE = 'a',
    DRAW,
    QUERY,
    CLOSE,
    CREATE,
};
struct dataPack{
    char cardid[20];
    unsigned char operation;
    int amount;
    int sessionid;
    Account account;
}__attribute__((packed));

struct Receipt {
    unsigned char operation;
    unsigned char success;
    int value;
    Account account;
}__attribute__((packed));

void parsing(const dataPack &data, Receipt *result);
} // end of namespace mission
