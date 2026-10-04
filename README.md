# stream

Ultra-lightweight, zero-storage byte conduit and transport abstraction written in ANSI/ISO C99.

## Overview

The `stream` module provides an ultra-lightweight abstraction for bidirectional byte I/O across hardware peripherals (USART, USB CDC, SEGGER RTT, SPI, or network sockets) without coupling application modules to hardware registers.

### Key Highlights
- **Zero Dynamic Allocation**: 100% freestanding with zero heap requirements (`malloc`, `free`) per MISRA C:2012 Rule 21.3.
- **Zero Storage**: `Stream` owns no internal buffers and introduces no redundant memory copies.
- **Single Struct Design**: Direct bundling of context and callbacks (`write`, `read`, `flush`).
- **Value-Constructed `stream_init()`**: Constructs and returns a `Stream` instance by value.
- **Permits NULL Context**: Designed to support static global drivers (e.g., standard UART) cleanly.
- **Strict Compliance**: MISRA C:2012 compliant, deterministic $O(1)$ operations with defensive checks.

---

## API Summary

Declared in [`stream.h`](stream.h):

```c
#include "stream.h"

/* 1. Define driver callbacks */
static size_t my_uart_write(void* context, const uint8_t* buffer, size_t size)
{
    /* transmit bytes to hardware FIFO */
    return bytes_sent;
}

static size_t my_uart_read(void* context, uint8_t* buffer, size_t size)
{
    /* read bytes from hardware FIFO */
    return bytes_read;
}

static void my_uart_flush(void* context)
{
    /* wait for transmission to complete */
}

/* 2. Initialize stream by value */
Stream uart_stream = stream_init(&my_uart_device, my_uart_write, my_uart_read, my_uart_flush);

/* 3. Transmit and receive */
uint8_t payload[] = { 0x01, 0x02, 0x03 };
size_t written = stream_write(&uart_stream, payload, sizeof(payload));

uint8_t rx_buffer[16];
size_t received = stream_read(&uart_stream, rx_buffer, sizeof(rx_buffer));

/* 4. Flush */
stream_flush(&uart_stream);
```