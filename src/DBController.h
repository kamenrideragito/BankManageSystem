// Author:     Hermit
// CreateTime: Mar 12, 2019 11:19 AM
// Eamil:      LasNoire23@gmail.com
// MyPage:     None

#pragma once
#include <string.h>
#include <string>
#include "sqlite3.h"
#include "Account.h"
#include "ProjectTool.h"

namespace db
{

int add(const char *table,
        const char *id,
        const char *column,
        int value);

int minus(const char *table,
          const char *id,
          const char *column,
          int value);

int query(const char *table,
          const char *id,
          Account *account);

int create(const char *table,
           const char *id,
           const char *password,
           const int amount);

}
