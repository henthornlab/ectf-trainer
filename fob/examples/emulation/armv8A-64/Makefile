#
# Copyright 2021 Google LLC
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

TOOLCHAIN_PREFIX = aarch64-linux-gnu-
OPTIMIZATION     = g
STARTUP    		 = aarch64

# MANDATORY:
#     These 3 parameters are needed for every port
#     Provide all values in hex
RAM_BASE_PHYSICAL  = 0x40000000
RAM_SIZE           = 0x4000

LD_FLAGS = --no-warn-rwx-segments

# MANDATORY:
#     Provide relative path to shell/ from current directory
#     Only Variable should be set above this line
SHELL_ROOT=../../../shell
-include $(SHELL_ROOT)/Makefile
# ^^ Do not move the above line. All user targets to be defined below this line!

# ------------------------ User targets below this line ------------------------
### run: Launches QEMU and loads the project binary on it
run: $(PROJECT).elf
	@echo "Use Ctrl+A X to exit Qemu"
	@qemu-system-aarch64 -M virt,secure=on,virtualization=on \
	 -cpu cortex-a72 -nographic \
	 -kernel $(PROJECT).elf

### debug: Qemu with GDB server. To be executed before 'make gdb'
debug:
	@echo Please use \"make gdb\" in another terminal to attach gdb.
	@echo Use \"cltr+a,x\" to quit qemu debug
	@qemu-system-aarch64 -S -M virt,secure=on,virtualization=on \
	 -cpu cortex-a72 -nographic -kernel \
	 $(PROJECT).elf -gdb tcp::1234

### gdb: Launches GDB and connects to qemu. To be executed after 'make debug'
gdb:
	@gdb-multiarch shell.elf -ex "target remote localhost:1234"

