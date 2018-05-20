#ifndef BULLET_FSTRING_H
#define BULLET_FSTRING_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

/**
 * @brief 判断是否全部为字母或数字字符
 * @param s 目标字符串
 * @return 返回判断结果布尔值。空字符串返回 false
 */
extern bool fstr_isalnum (const char *s);

/**
 * @brief 判断是否全部为字母字符
 * @param s 目标字符串
 * @return 返回判断结果布尔值。空字符串返回 false
 */
extern bool fstr_isalpha (const char *s);

/**
 * @brief 判断是否全部为数字字符
 * @param s 目标字符串
 * @return 返回判断结果布尔值.空字符串返回 false
 */
extern bool fstr_isdigit (const char *s);

/**
 * @brief 判断字符串中的字母是否全部为小写
 * @param s 目标字符串
 * @return 返回判断结果布尔值。空字符串返回 false
 */
extern bool fstr_islower (const char *s);

/**
 * @brief 判断字符串中的字母是否全部为大写
 * @param s 目标字符串
 * @return 返回判断结果布尔值.空字符串返回 false.
 */
extern bool fstr_isupper (const char *s);

/**
 * @brief 将字符串中的字母全部小写
 * @param s 目标字符串
 * @return 返回新字符串。空字符串返回 null
 */
extern char *fstr_lower (const char *s);

/**
 * @brief 将字符串中的字母全部大写
 * @param s 目标字符串
 * @return 返回新字符串。空字符串返回 null
 */
extern char *fstr_upper (const char *s);

/**
 * @brief 将字符串中的字母大小写互换
 * @param s 目标字符串
 * @return 返回新字符串。空字符串返回 null
 */
extern char *fstr_swapcase (const char *s);

/**
 * @brief 检查字符串是否以特定字符串组合开头
 * @param s 目标字符串
 * @param str 特定字符串
 * @return 返回检测结果的布尔值。
 */
extern bool fstr_startswith (const char *s, const char *str);

/**
 * @brief 检查字符串是否以特定字符串组合结尾
 * @param s 目标字符串
 * @param str 特定字符串
 * @return 返回检测结果的布尔值。
 */
extern bool fstr_endswith (const char *s, const char *str);


/**
 * @brief 去除字符串开头的所有字符c，返回新字符串
 * @param s 目标字符串
 * @param c 目标字符
 * @return 返回新字符串
 */
extern char *fstr_lstrip (const char *s, char c);

/**
 * @brief 去除字符串结尾的所有字符c，返回新字符串
 * @param s 目标字符串
 * @param c 目标字符
 * @return 返回新字符串
 */
extern char *fstr_rstrip (const char *s, char c);


/**
 * @brief 去除字符串开头个结尾的字符 c，返回新字符串
 * @param s 目标字符串
 * @param c  目标字符
 * @return  返回新字符串
 */
extern char *fstr_strip (const char *s, char c);

/**
 * @brief 查找字符 c 在字符串中出现的次数
 * @param s 目标字符串
 * @param c 目标字符
 * @return  返回字符 c 在目标字符串中出现的次数
 */
int fstr_count (const char *s, char c);

/**
 * @brief 查找目标字符在字符串中的索引
 * @param s 目标字符串
 * @param c 目标字符
 *  * @param size 返回数组的大小
 * @return  返回索引值组成的数组。若不包含字符 c 则返回null，且size = 0
 *  * NOTE: 索引从0开始
 */
int *fstr_index (const char *s, char c, int *size);

/**
 * @brief 依照字符c，分隔字符串
 * @param s 目标字符串
 * @param c 目标字符
 * @return 返回新字符串数组
 */
extern char **fstr_split (const char *s, char c, int *size);



#endif /* BULLET_FSTRING_H */
