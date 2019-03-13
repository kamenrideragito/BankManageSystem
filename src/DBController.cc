// Author:     Hermit
// CreateTime: Mar 12, 2019 11:24 AM
// Eamil:      LasNoire23@gmail.com
// MyPage:     None

#include <stdio.h>
#include <string.h>

#include "DBController.h"

namespace db
{

const char *database = tool::getDBPath();

int add(const char *table,
        const char *id,
        const char *column,
        int value) {
    sqlite3 *connector;
    int err = sqlite3_open(database, &connector);
    if (err) {
        sqlite3_close(connector);
        return -1;
    } 
    char SQL[1024]; 
    Account *account = new Account;
    err = db::query(table, id, account);
    if (err < 0) {
        sqlite3_close(connector);
        delete account;
        return -1;
    }
    int amount = account->amount;
    delete account;
    sprintf(SQL, "UPDATE %s SET %s = %d \
                 WHERE id = '%s';", table, column, amount+value, id);
    err = sqlite3_exec(connector, SQL, NULL, NULL, NULL);
    if (err) {
        sqlite3_close(connector);
        return -1;
    }
    sqlite3_close(connector);
    return 0;
}

int minus(const char *table,
          const char *id,
          const char *column,
          int value) {
    sqlite3 *connector;
    int err = sqlite3_open(database, &connector);
    if (err) {
        sqlite3_close(connector);
        return -1;
    } 
    char SQL[1024]; 
    Account *account = new Account;
    err = db::query(table, id, account);
    if (err < 0) {
        sqlite3_close(connector);
        delete account;
        return -1; 
    }
    int amount = account->amount;
    delete account;
    if (amount-value < 0) {
        sqlite3_close(connector);
        return -1;
    }
    sprintf(SQL, "UPDATE %s SET %s = %d \
                 WHERE id = '%s';", table, column, amount-value, id);
    err = sqlite3_exec(connector, SQL, NULL, NULL, NULL);
    if (err) {
        sqlite3_close(connector);
        return -1;
    }
    sqlite3_close(connector);
    return 0;
}

int getItem(void *item, int argc, char **argv, char **colName) {
    Account *account = reinterpret_cast<Account*>(item);
    for (int i = 0; i < argc; i++) {
        if (strcmp(colName[i], "amount") == 0) {
            account->amount = stoi(std::string(argv[i]));
        } 
        else if (strcmp(colName[i], "id") == 0) {
            strcpy(account->id, argv[i]);
        }
        else if (strcmp(colName[i], "password") == 0) {
            strcpy(account->password, argv[i]);
        }
    }
    return 0;
}

int query(const char *table,
          const char *id,
          Account *account) {
    sqlite3 *connector;
    int err = sqlite3_open(database, &connector);
    if (err) {
        sqlite3_close(connector);
        return -1;
    }
    strcpy(account->id, "no such user");
    char SQL[1024];
    sprintf(SQL, "SELECT * FROM %s \
                  WHERE id = '%s';", table, id);
    err = sqlite3_exec(connector, SQL, getItem, (void*)account, NULL);
    if (err) {
        sqlite3_close(connector);
        return -1;
    }
    sqlite3_close(connector);
    return 0;
}

} // end of namespace db
