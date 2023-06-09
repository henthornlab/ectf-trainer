#
# Copyright 2022 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

TOOLCHAIN_PREFIX = riscv64-linux-gnu-
OPTIMIZATION     = g
STARTUP          = riscv32

ROM_BASE_PHYSICAL = 0x20010000
ROM_SIZE          = 0x00010000
RAM_BASE_PHYSICAL = 0x80000000
RAM_SIZE          = 0x00004000

DEFINES   += -march=rv32imac -mabi=ilp32
ASM_FLAGS += -march=rv32imac -mabi=ilp32
LD_FLAGS  += -m elf32lriscv

# only 4kB of code memory. Hence, shell lite!
SHELL_LITE = 1

SHELL_ROOT=../../../shell
-include $(SHELL_ROOT)/Makefile

# ------------------------ User targets below this line ------------------------

OPENOCD = openocd
OPENOC_CONFIG_FILE = board/sifive-hifive1-revb.cfg

### upload: Uploads the binary to the board
upload: $(PROJECT).elf
	@echo -n "Uploading..."
	@sudo $(OPENOCD) -f $(OPENOC_CONFIG_FILE) -c "program $^ verify reset exit"
	@echo "Done :)"

### debug: Launches OpenOCD with gdb server. To be executed before 'make gdb'
debug: $(PROJECT).elf
	@echo "target extended-remote localhost:3333" > $(PROJECT).gdb
	@echo "monitor reset halt" >> $(PROJECT).gdb
	@echo "GDB server active..."
	@echo "Use Ctrl+c to close the server!"
	@sudo $(OPENOCD) -f $(OPENOC_CONFIG_FILE) 2>/dev/null

### gdb: Launches GDB and connects to the target. To be executed after 'make debug'
gdb: $(PROJECT).elf
	@gdb-multiarch -q $^ --command=$(PROJECT).gdb
