#ifndef __LOG_H_
#define __LOG_H_

// log print interface for debuging
#define LOG_LINE_LEVEL_ERROR 0
#define LOG_LINE_LEVEL_INFO 1
#define LOG_LINE_LEVEL_DEBUG 2

namespace thief_stl {

static int log_line_level = 0;

void set_log_level(int level) {
    log_line_level = level;
}

#define LOG_INFO_CONTENT(log_content)                                                                           \
    if (log_line_level >= LOG_LINE_LEVEL_INFO) {                                                                \
        fprintf(stderr, "info: [file:%s function:%s line:%d] %s\n", __FILE__, __func__, __LINE__, log_content); \
    }

#define LOG_INFO_LINE()                                                                         \
    if (log_line_level >= LOG_LINE_LEVEL_INFO) {                                                \
        fprintf(stderr, "info: [file:%s function:%s line:%d]\n", __FILE__, __func__, __LINE__); \
    }

#define LOG_ERROR_CONTENT(log_content)                                                                          \
    if (log_line_level >= LOG_LINE_LEVEL_ERROR) {                                                               \
        fprintf(stderr, "info: [file:%s function:%s line:%d] %s\n", __FILE__, __func__, __LINE__, log_content); \
    }

#define LOG_ERROR_LINE()                                                                        \
    if (log_line_level >= LOG_LINE_LEVEL_ERROR) {                                               \
        fprintf(stderr, "info: [file:%s function:%s line:%d]\n", __FILE__, __func__, __LINE__); \
    }

#define LOG_DEBUG_CONTENT(log_content)                                                                          \
    if (log_line_level >= LOG_LINE_LEVEL_DEBUG) {                                                               \
        fprintf(stderr, "info: [file:%s function:%s line:%d] %s\n", __FILE__, __func__, __LINE__, log_content); \
    }

#define LOG_DEBUG_LINE()                                                                        \
    if (log_line_level >= LOG_LINE_LEVEL_DEBUG) {                                               \
        fprintf(stderr, "info: [file:%s function:%s line:%d]\n", __FILE__, __func__, __LINE__); \
    }

}  // namespace thief_stl
#endif  // __LOG_H_
