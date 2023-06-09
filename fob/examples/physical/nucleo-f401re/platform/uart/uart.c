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

#include "mmap.h"
#include "uart.h"

void uputc(char c) {
  while (!((USART_SR >> 7) & 1)) {
    // loop
  }

  USART_DR = c;
  if (c == '\n')
    uputc('\r');
}

int ugetc(void) {
  if ((USART_SR >> 5) & 1) return USART_DR;

  return -1;
}

void uart_init(void) {
  USART_CR1 &= ~(1 << 13);    // Disable UART
  USART_BRR = 0x8c;           // Set baud to 115200
  USART_CR1 |= (1<<3)|(1<<2); // Enable tx/rx
  USART_CR1 |= 1 << 13;       // Enable the uart
}
