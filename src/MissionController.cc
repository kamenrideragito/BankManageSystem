// Author:     Hermit
// CreateTime: Mar 12, 2019 10:49 AM
// Eamil:      LasNoire23@gmail.com
// MyPage:     None

#include "MissionController.h"

namespace mission
{
void parsing (const dataPack &data, Receipt *result) {
    int err;
    if (data.operation ==
        static_cast<unsigned char>(OPERATION::SAVE)) {
        result->operation = 0;
        result->value = data.amount;
        if ((err = db::add("user",
                            data.cardid,
                            "amount",
                            data.amount)) < 0) {
            result->success = 0;
        }
        else {
            result->success = 1;
        }
    }
    else if (data.operation ==
             static_cast<unsigned char>(OPERATION::DRAW)) {
        result->operation = 1;
        result->value = data.amount;
        if (( err = db::minus("user",
                              data.cardid,
                              "amount",
                              data.amount)) < 0) {
            result->success = 0;
        }
        else {
            result->success = 1;
        }
    }
    else if (data.operation == 
             static_cast<unsigned char>(OPERATION::QUERY)) {
        result->operation = 2;
        Account *account = new Account;
        if (( err = db::query("user",
                              data.cardid,
                              account)) < 0) {
            result->success = 0;
        }
        else {
            result->success = 1;
            result->value = account->amount;
            strcpy(result->account.id, account->id);
            strcpy(result->account.password,
                   account->password);
            result->account.amount = account->amount;
            if (strcmp(result->account.id,
                       "no such user") == 0) {
                result->success = 0;
            }
        }
        delete account;
    }
    else if (data.operation ==
             static_cast<unsigned char>(OPERATION::CLOSE)) {
        char path[256];
        sprintf(path, "%s/fifo/%d.fifo", tool::getInstancePath(),
                                         data.sessionid);
        int err = remove(path);
        result->operation = static_cast<unsigned char>(OPERATION::CLOSE);
        if (err) {
            result->success = 0;
        } else {
            result->success = 1;
        }
    }
    //else if (data.operation ==
    //         static_cast<unsigned char>(OPERATION::CONNECT)) {
    //    char path[256];
    //    sprintf(path, "%s/fifo/%d.fifo", tool::getInstancePath(),
    //                                     data.sessionid);
    //    int err = mkfifo(path, S_IWUSR | S_IRUSR | S_IXUSR |
    //                     S_IWGRP | S_IRGRP | S_IXGRP |
    //                     S_IWOTH | S_IROTH | S_IXOTH);
    //    result->operation = static_cast<unsigned char>(OPERATION::CONNECT);
    //    if (err) {
    //        result->success = 0;
    //    } else {
    //        result->success = 1;
    //    }
    //}

    return ;
}

} // end of namespace mission
