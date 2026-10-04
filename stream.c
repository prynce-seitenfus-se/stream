#include "stream.h"

inline Stream stream_init(void* context,
                          StreamWriteFn write_fn,
                          StreamReadFn read_fn,
                          StreamFlushFn flush_fn)
{
    Stream stream;
    stream.context = context;
    stream.write   = write_fn;
    stream.read    = read_fn;
    stream.flush   = flush_fn;
    return stream;
}

inline size_t stream_write(const Stream* stream, const uint8_t* buffer, size_t size)
{
    if ((stream == NULL) || (stream->write == NULL) || (buffer == NULL) || (size == 0U)) {
        return 0U;
    }
    return stream->write(stream->context, buffer, size);
}

inline size_t stream_read(const Stream* stream, uint8_t* buffer, size_t size)
{
    if ((stream == NULL) || (stream->read == NULL) || (buffer == NULL) || (size == 0U)) {
        return 0U;
    }
    return stream->read(stream->context, buffer, size);
}

inline void stream_flush(const Stream* stream)
{
    if ((stream != NULL) && (stream->flush != NULL)) {
        stream->flush(stream->context);
    }
}
