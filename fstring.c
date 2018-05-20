#include "fstring.h"

/**
 * @brief 判断是否全部为字母或数字字符
 * @param s 目标字符串
 * @return 返回判断结果布尔值。空字符串返回 false
 */
bool fstr_isalnum (const char *s) {
    int len = strlen(s);
    if (len == 0) {
        return false;
    }
    printf("len = %d\n", strlen(s));
    for (int i = 0; i < len; ++i) {
        if (!isalnum(s[i])) {
            return false;
        }
    }
    return true;
}


/**
 * @brief 判断是否全部为字母字符
 * @param s 目标字符串
 * @return 返回判断结果布尔值.空字符串返回 false
 */
bool fstr_isalpha (const char *s) {
    int len = strlen(s);
    if (len == 0) {
        return false;
    }
    for (int i = 0; i < len; ++i) {
        if (!isalpha(s[i])) {
            return false;
        }
    }
    return true;
}


/**
 * @brief 判断是否全部为数字字符
 * @param s 目标字符串
 * @return 返回判断结果布尔值.空字符串返回 false
 */
bool fstr_isdigit (const char *s) {
    int len = strlen(s);
    if (len == 0) {
        return false;
    }
    for (int i = 0; i < len; ++i) {
        if (!isdigit(s[i])) {
            return false;
        }
    }
    return true;
}


/**
 * @brief 判断字符串中的字母是否全部为小写
 * @param s 目标字符串
 * @return 返回判断结果布尔值,空字符串返回 false
 */
bool fstr_islower (const char *s) {
    int len = strlen(s);
    if (len == 0) {
        return false;
    }
    for (int i = 0; i < len; ++i) {
        if (isalpha(s[i]) && isupper(s[i])) {
            return false;
        }
    }
    return true;
}


/**
 * @brief 判断字符串中的字母是否全部为大写
 * @param s 目标字符串
 * @return 返回判断结果布尔值,空字符串返回 false
 */
bool fstr_isupper (const char *s) {
    int len = strlen(s);
    if (len == 0) {
        return false;
    }
    for (int i = 0; i < len; ++i) {
        if (isalpha(s[i]) && islower(s[i])) {
            return false;
        }
    }
    return true;
}


/**
 * @brief 将字符串中的字母全部小写
 * @param s 目标字符串
 * @return 返回新字符串。空字符串返回 null
 */
char *fstr_lower (const char *s) {
    int len = strlen(s);
    if (len == 0) {
        return NULL;
    }
    char *t = strdup(s);
    for (int i = 0; i < len; ++i) {
        if (isalpha(t[i]) && isupper(t[i])) {
            t[i] += 
        }
    }
}


/**
 * @brief 将字符串中的字母全部大写
 * @param s 目标字符串
 * @return 返回新字符串。空字符串返回 null
 */
char *fstr_upper (const char *s);


/**
 * @brief 将字符串中的字母大小写互换
 * @param s 目标字符串
 * @return 返回新字符串。空字符串返回 null
 */
char *fstr_swapcase (const char *s);


/**
 * @brief 检查字符串是否以特定字符串组合开头
 * @param s 目标字符串
 * @param str 特定字符串
 * @return 返回检测结果的布尔值。
 */
//bool fstr_startswith (const char *s, const char *start) {
//    int len = strlen(str);
//    if (len > strlen(s)) {
//        return false;
//    }
//    for (int i = 0; i < len && ; ++i) {
//        if (str[i] != s[i]) {
//            return false;
//        }
//    }
//    return true;
//}


/**
 * @brief 检查字符串是否以特定字符串组合结尾
 * @param s 目标字符串
 * @param str 特定字符串
 * @return 返回检测结果的布尔值。
 */
//TODO 判断函数strrev是否复制源字符串
//bool fstr_endswith (const char *s, const char *end) {
//    char *s_rev = strrev(s);
//    char *str_rev = strrev(start);
//
//    return true;
//}


/**
 * @brief 去除字符串开头的所有字符c，返回新字符串
 * @param s 目标字符串
 * @param c 目标字符
 * @return 返回新字符串
 */
char *fstr_lstrip (const char *s, char c) {
    int s_len = strlen(s);
    char *start, *end;
    start = (char *)s;
    end = (char *) (s + s_len - 1);
    while (*start == c && end >= start) {
        ++start;
    }
    size_t t_len = end - start + 1;
    char *t = (char *) calloc((t_len + 1), sizeof(char));
    strncpy(t, start, t_len);
    return t;
}


/**
 * @brief 去除字符串结尾的所有字符c，返回新字符串
 * @param s 目标字符串
 * @param c 目标字符
 * @return 返回新字符串
 */
char *fstr_rstrip (const char *s, char c) {
    int s_len = strlen(s);
    char *start, *end;
    start = (char *)s;
    end = (char *) (s + s_len - 1);
    while (*end == c && start <= end) {
        --end;
    }
    size_t t_len = end - start + 1;
    char *t = (char *) calloc((t_len + 1), sizeof(char));
    strncpy(t, start, t_len);
    return t;

}


/**
 * @brief 去除字符串开头个结尾的字符 c，返回新字符串
 * @param s 目标字符串
 * @param c  目标字符
 * @return  返回新字符串
 */
char *fstr_strip (const char *s, char c) {
    int s_len = strlen(s);
    char *start, *end;
    start = (char *)s;
    end = (char *) (s + s_len - 1);
    while (*start == c && start <= end) {
        ++start;
    }
    while (*end == c && start <= end) {
        --end;
    }
    size_t t_len = end - start + 1;
    char *t = (char *) calloc((t_len + 1), sizeof(char));
    strncpy(t, start, t_len);
    return t;
}


/**
 * @brief 查找字符 c 在字符串中出现的次数
 * @param s 目标字符串
 * @param c 目标字符
 * @return  返回字符 c 在目标字符串中出现的次数
 */
int fstr_count (const char *s, char c) {
    int count = 0;
    for (int i = 0; i < strlen(s); ++i) {
        if (*(s + i) == c) {
            ++count;
        }
    }
    return count;
}

/**
 * @brief 查找目标字符在字符串中的索引
 * @param s 目标字符串
 * @param c 目标字符
 * @param size 返回数组的大小
 * @return  返回索引值组成的数组。若不包含字符 c 则返回null，且size = 0
 * NOTE: 索引从0开始
 */
int *fstr_index (const char *s, char c, int *size) {
    *size = fstr_count(s, c);
    int *res;
    if (*size == 0) {
        return NULL;
    } else {
        res = (int *) malloc(*size * sizeof(int));
        for (int i = 0, k = 0; i < strlen(s); ++i) {
            if (s[i] == c) {
                res[k++] = i;
            }
        }
    }
    return res;
}

/**
 * @brief 依照字符c，分隔字符串
 * @param s 目标字符串
 * @param c 目标字符
 * @return 返回新字符串数组，不包含字符 c，则size = 0, 返回 null。
 */
char **fstr_split (const char *s, char c, int *size) {
    char *t = fstr_strip(s, c);
    printf("t = %s", t);
    int count = 0;    /* 字符 c 出现位置的计数 */
    /* 找到对应字符的索引数组 */
    int *index = fstr_index(t, c, &count);

    char **res = NULL;
    if (count != 0) {
        /* 在每个出现的位置，将字符 c 置换为结束符 */
        for (int i = 0; i < count; ++i) {
            *(t + index[i]) = '\0';
        }

        /* 保存每个字符串的起始指针 */
        *size = count + 1;  /* count 个位置，将字符串分成 count + 1 段*/
        res = (char **) malloc(*size * sizeof(char *));
        res[0] = t;
        for (int i = 0; i < count; ++i) {
            res[i + 1] = t + index[i] + 1;
        }
    }
    return res;
}






