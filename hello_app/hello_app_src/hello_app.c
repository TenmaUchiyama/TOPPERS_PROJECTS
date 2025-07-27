#include <kernel.h>
#include <t_syslog.h>
#include "hello_app.h"



/* メインタスク本体 */
void main_task(EXINF exinf) {
   
    while (1) {
     syslog(LOG_NOTICE , "Hello World! This is my third custom application");

     dly_tsk(1000000);
    };
};
