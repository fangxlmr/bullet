/*
 * 字符串解析库fstring的代码实现
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "fstring.h"

int fstr_isalnum(const char *s) {
    char *walk;

    walk = (char *) s;

    /*
     * 空指针字符串，返回0
     */
    if (!walk || *walk == 0) {
        return 0;
    }
    while (*walk != '\0') {
        /*
         * 判断是否为数字、字母
         */
        if (!isalnum(*walk)) {
            return 0;
        }
        ++walk;
    }
    return 1;
}

int fstr_isalpha(const char *s) {
    char *walk;

    walk = (char *) s;

    if (!walk || *walk == '\0') {
        return 0;
    }
    while (*walk != '\0') {
        if (!isalnum(*walk)) {
            return 0;
        }
        ++walk;
    }
    return 1;
}

int fstr_isdigit(const char *s) {
    char *walk;

    walk = (char *) s;

    if (!walk || *walk == '\0') {
        return 0;
    }
    while (*walk != '\0') {
        if (!isdigit(*walk)) {
            return 0;
        }
        ++walk;
    }
    return 1;
}

int fstr_islower(const char *s) {
    char *walk;

    walk = (char *) s;

    if (!walk || *walk == '\0') {
        return 0;
    }
    while (*walk != '\0') {
        if (!islower(*walk)) {
            return 0;
        }
        ++walk;
    }
    return 1;
}

int fstr_isupper(const char *s) {
    char *walk;

    walk = (char *)s;

    if (!walk || *walk == '\0') {
        return 0;
    }
    while (*walk != '\0') {
        if (!isupper(*walk)) {
            return 0;
        }
        ++walk;
    }
    return 1;
}

void fstr_tolower(char *s) {
    char *walk;

    walk = s;

    if (!walk) {
        return;
    }
    while (*walk != '\0') {
        *walk = (char) tolower(*walk);
    }
}

void fstr_toupper(char *s) {
    char *walk;

    walk = s;

    if (!walk) {
        return;
    }
    while (*walk != '\0') {
        *walk = (char) toupper(*walk);
    }
}

void fstr_swapcase(char *s) {
    char *walk;

    walk = s;

    if (!walk) {
        return;
    }

    /*
     * 转换大小写
     */
    while (*walk != '\0') {
        *walk = (char) (islower(*walk) ? toupper(*walk) : tolower(*walk));
        ++walk;
    }
}

int fstr_startswith(const char *s, const char *start) {
    int i;

    i = 0;
    /*
     * 判断s是否以start开头
     */
    while (s[i] != '\0' && start[i] != '\0' && start[i] == s[i]) {
        ++i;
    }
    if (start[i] == '\0') { /* 是 */
        return 1;
    } else {        /* 否 */
        return 0;
    }
}

int fstr_endswith(const char *s, const char *end) {
    int s_len;
    int end_len;

    s_len = strlen(s);
    end_len = strlen(end);

    /*
     * 判断s是否以end结尾
     */
    while (s_len >= 0 && end_len >= 0
           && s[s_len] == end[end_len]) {
        --s_len;
        --end_len;
    }
    if (end_len < 0) { /* 是 */
        return 1;
    } else {            /* 否 */
        return 0;
    }
}

char *fstr_lstrip(char *s, char c) {
    char *walk;

    /*
     * 直接抛弃左侧的若干字符c，
     * 可能会造成内存泄露。
     */
    walk = s;
    while (*walk != '\0' && *walk == c) {
        ++walk;
    }

    return walk;
}

char *fstr_rstrip(char *s, char c) {
    char *walk;

    /*
     * 直接抛弃右侧若干字符c，
     * 可能会造成内存泄露。
     */
    walk = s + strlen(s) - 1;
    while (walk >= s && *walk == c) {
        *walk = '\0';
        --walk;
    }

    return walk;
}

char *fstr_strip(char *s, char c) {
    char *walk;
    char *result;

    /*
     * 抛弃两侧的若干字符c，
     * 可能会造成内存泄露。
     */
    walk = s;
    while (*walk != '\0' && *walk == c) {   /* 左侧 */
        ++walk;
    }

    result = walk;
    walk = result + strlen(result) - 1;
    while (walk >= result && *walk == c) {  /* 右侧 */
        *walk = '\0';
        --walk;
    }

    return result;
}

int fstr_count(const char *s, char c) {
    int count;
    char *walk;

    count = 0;
    walk = (char *) s;

    while (*walk != '\0') {
        if (*walk == c) {
            ++count;
        }
        ++walk;
    }

    return count;
}

char *fstr_split(char *s, char c) {
    static char *next = NULL;   /* 保存上次解析到的位置 */
    char *token;
    int i;

    i = 0;
    token = NULL;

    /*
     * 若输入的字符串指针为NULL，
     * 则将指针s重置为上一次的解析位置，
     * 继续解析步骤。
     */
    if (s == NULL) {
        s = next;
    }
    if (s != NULL) {
        /*
         * 找到第一个非字符c的位置，
         * 赋值给token，也即为函数的返回值。
         */
        while (s[i] != '\0') {
            if (s[i] != c) {
                token = s + i++;
                break;
            }
            ++i;
        }
        /*
         * 找到之后的第一个匹配字符c的位置，
         * 将该位置重置为'\0'，并将next指针
         * 指向下一个字符。
         */
        while (s[i] != '\0') {
            if (s[i] == c) {
                s[i++] = '\0';
                next = s + i;
                break;
            }
            ++i;
        }
        /*
         * 若已到结尾，则next指针置空。
         */
        if (s[i] == '\0') {
            next = NULL;
        }
    }

    return token;
}

char *fstr_replace(char *s, const char *old, const char *new) {
    char *t = strdup(s);
    char *pos = strstr(t, old);     /* old子串位置标记 */
    if (!pos) {
        return t;
    }
    *pos = '\0';    /* 发现子串的位置做结尾标记 */
    int old_len = strlen(old);
    /* 新串长度 */
    int len = strlen(s) - old_len + strlen(new) + 1;
    char *res = (char *) calloc(len, sizeof(char));
    strcat(res, t);
    strcat(res, new);
    strcat(res, pos + old_len);
    return res;
}