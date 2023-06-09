/**
 * Copyright 2022 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 **/

/*
 * This is a mandatory include.
 * This has the ADD_CMD() macro
 */
#include "shell.h"
#include "unistd.h"
#include "platform.h"
#include "uart.h"
#include "mhu.h"

/*
 * There can be one or many function with same prototype, exposed as
 * a command on the shell. They can be in same or multiple files.
 */
int hello(int argc, char** argv) {
    volatile uint32_t id = get_cpu_id();
    printf("CoreID: %u: \t", id);

    for (int i = 0; i < argc; i++) {
        printf(argv[i]);
        printf(" ");
    }

    printf("\nPress ctrl + a, x to exit !\n");
    return 0;
}


/*
 * @brief Switch the prompt to run on other core.
 */
extern volatile uint32_t g_mhu_flag0;
extern volatile uint32_t g_mhu_flag1;

//read: https://en.wikipedia.org/wiki/Kho_kho
int kho(int argc, char** argv)
{

    volatile uint32_t id = get_cpu_id();

    if (id == CPU0_ID) {
        printf("Transferring control to core-1\n");
        g_mhu_flag0 = 0;
        mhu_send(MHU0_BASE, CPU1_ID);
    } else if (id == CPU1_ID) {
        printf("Transferring control to core-0\n");
        g_mhu_flag1 = 0;
        mhu_send(MHU0_BASE, CPU0_ID);
    } else {
        while(1);
    }

    return 0;
}

/*
 * One or many such can exist per file.
 * Description: ADD_CMD(command, help string, function to be exposed)
 */
ADD_CMD(hello, "Echoes the commandline\n\tusage: hello <any string>", hello);
ADD_CMD(kho, "Switch the prompt to run on other core.\n\tWord origin: https://en.wikipedia.org/wiki/Kho_kho", kho);
