#ifndef STREAM_H
#define STREAM_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Function pointer for stream write operations.
 *
 * @param context Driver or peripheral private context pointer (may be NULL).
 * @param buffer Pointer to source buffer containing bytes to transmit.
 * @param size Number of bytes to transmit.
 * @return Number of bytes actually written.
 */
typedef size_t (*StreamWriteFn)(void* context, const uint8_t* buffer, size_t size);

/**
 * @brief Function pointer for stream read operations.
 *
 * @param context Driver or peripheral private context pointer (may be NULL).
 * @param buffer Destination buffer to store received bytes.
 * @param size Maximum number of bytes to read into buffer.
 * @return Number of bytes actually read.
 */
typedef size_t (*StreamReadFn)(void* context, uint8_t* buffer, size_t size);

/**
 * @brief Function pointer for stream flush operations.
 *
 * @param context Driver or peripheral private context pointer (may be NULL).
 */
typedef void (*StreamFlushFn)(void* context);

/**
 * @brief Stream conduit instance representing an I/O endpoint.
 */
typedef struct Stream {
    void*         context;  /**< User, peripheral, or driver context pointer (may be NULL). */
    StreamWriteFn write;    /**< Callback to transmit bytes (may be NULL for RX-only). */
    StreamReadFn  read;     /**< Callback to receive bytes (may be NULL for TX-only). */
    StreamFlushFn flush;    /**< Optional flush callback (may be NULL). */
} Stream;

/**
 * @brief Constructs and returns an initialized Stream instance by value.
 *
 * @param context User/driver context pointer passed to callbacks (can be NULL).
 * @param write_fn Callback to transmit bytes (may be NULL for RX-only).
 * @param read_fn Callback to receive bytes (may be NULL for TX-only).
 * @param flush_fn Optional flush callback (may be NULL).
 * @return Initialized Stream struct.
 */
Stream stream_init(void* context,
                   StreamWriteFn write_fn,
                   StreamReadFn read_fn,
                   StreamFlushFn flush_fn);

/**
 * @brief Writes bytes to the stream endpoint.
 *
 * @param stream Pointer to Stream instance.
 * @param buffer Source buffer containing data to transmit.
 * @param size Number of bytes to transmit.
 * @return Number of bytes written, or 0 if arguments or callback are invalid.
 */
size_t stream_write(const Stream* stream, const uint8_t* buffer, size_t size);

/**
 * @brief Reads bytes from the stream endpoint.
 *
 * @param stream Pointer to Stream instance.
 * @param buffer Destination buffer to receive data.
 * @param size Maximum number of bytes to read.
 * @return Number of bytes read, or 0 if arguments or callback are invalid.
 */
size_t stream_read(const Stream* stream, uint8_t* buffer, size_t size);

/**
 * @brief Flushes any pending output in the underlying hardware/driver.
 *
 * @param stream Pointer to Stream instance.
 */
void stream_flush(const Stream* stream);

#ifdef __cplusplus
}
#endif

#endif /* STREAM_H */
