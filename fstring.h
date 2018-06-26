/**
 * @file    fstring.h
 *
 * @brief   字符串解析库
 *
 * 原生的C语言对字符串处理的支持比较少，
 * fstring库扩展了字符串处理函数，以满足不同需要。
 *
 */

#ifndef BULLET_FSTRING_H
#define BULLET_FSTRING_H


/**
 * fstr_isalnum     判断字符串内所有字符是否均为数字或字母
 *
 * @param s         目标字符串
 * @return          若所有字母均为数字或字母，则返回非0值，
 *                  否则，返回0。
 *                  空指针串或空串也返回0。
 */
extern int fstr_isalnum(const char *s);

/**
 * fstr_isalpha     判断字符串内所有字符是否均为字母
 *
 * @param s         目标字符串
 * @return          若字符串内所有字符均为字母，则返回 非0值，
 *                  否则，返回0。
 *                  空指针串或空串也返回0。
 */
extern int fstr_isalpha(const char *s);

/**
 * fstr_isdigit     判断字符串内所有字符是否均为数字
 *
 * @param s         目标字符串
 * @return          若字符串内所有字符均为数字，则返回非0值，
 *                  否则，返回0。
 *                  空指针串或空串也返回0。
 */
extern int fstr_isdigit(const char *s);

/**
 * fstr_islower     判断字符串中的字母是否全部为小写
 *
 * @param s         目标字符串
 * @return          若字符串中的所有字母均为小写，则返回非0值，
 *                  否则，返回0。
 *                  空指针串或空串也返回0。
 */
extern int fstr_islower(const char *s);

/**
 * fstr_islower     判断字符串中的字母是否全部为大写
 *
 * @param s         目标字符串
 * @return          若字符串中的所有字母均为大写，则返回非0值，
 *                  否则，返回0。
 *                  空指针串或空串也返回0。
 */
extern int fstr_isupper(const char *s);

/**
 * fstr_tolower     将字符串中的字母全部小写
 *
 * @param s         目标字符串
 */
extern void fstr_tolower(char *s);

/**
 * fstr_toupper     将字符串中的字母全部大写
 *
 * @param s 目标字符串
 */
extern void fstr_toupper(char *s);

/**
 * fstr_swapcase    将字符串中的字母大小写互换
 *
 * @param s         目标字符串
 */
extern void fstr_swapcase(char *s);

/**
 * fstr_startswith  检查目标字符串是否以特定字符串模式开头
 *
 * @param s         目标字符串
 * @param str       模式字符串
 * @return          若目标字符串以模式字符串开头，则返回非0值，
 *                  否则，返回0。
 */
extern int fstr_startswith(const char *s, const char *start);

/**
 * fstr_startswith  检查目标字符串是否以特定字符串模式结尾
 *
 * @param s         目标字符串
 * @param str       模式字符串
 * @return          若目标字符串以模式字符串结尾，则返回非0值，
 *                  否则，返回0。
 */
extern int fstr_endswith(const char *s, const char *end);

/**
 * fstr_lstrip      忽略字符串开头的所有字符c
 *
 * @param s         目标字符串
 * @param c         目标字符
 * @note            由于函数直接忽略原始字符串左侧所有包含字符c的
 *                  位置，所有该函数可能会造成内存泄露。
 */
extern char *fstr_lstrip(char *s, char c);

/**
 * fstr_lstrip      忽略字符串结尾的所有字符c
 *
 * @param s         目标字符串
 * @param c         目标字符
 * @note            由于函数直接忽略原始字符串右侧所有包含字符c的
 *                  位置，所有该函数可能会造成内存泄露。
 */
extern char *fstr_rstrip(char *s, char c);

/**
 * fstr_lstrip      忽略字符串开头与结尾的所有字符c
 *
 * @param s         目标字符串
 * @param c         目标字符
 * @note            由于函数直接忽略原始字符串左、右两侧所有包含字符c的
 *                  位置，所有该函数可能会造成内存泄露。
 */
extern char *fstr_strip(char *s, char c);

/**
 * fstr_count       查找字符c在字符串中出现的次数
 *
 * @param s         目标字符串
 * @param c         目标字符
 * @return          返回字符c在目标字符串中出现的次数
 */
extern int fstr_count(const char *s, char c);

/**
 * fstr_split       将字符串按照字符c分解
 * @param s         目标字符串
 * @param c         目标字符
 * @return          当s != NULL时，函数重新分解字符串s，
 *                  当s == NULL时，函数将从上一次分解完毕
 *                  之后的位置继续分解。
 * @note            该函数的作用类似于标准库函数中的strtok函数。
 *                  strtok函数是依照空格分解函数，而该函数是依照
 *                  指定的字符c来分解字符串。
 */
char *fstr_split(char *s, char c);

/**
 * fstr_replace     字符串替换
 *
 * @param s         目标字符串
 * @param old       旧字符串
 * @param new       新字符串
 * @return          将目标字符串中包含有子串old的部分，替换为子串new。
 * @note            子串old与子串new的长度必须相同。
 *                  若子串new过大（过小），则替换时会产生溢出（替换不完全）
 *                  出现。
 * @todo            函数尚且不完全，待加强。
 */
extern char *fstr_replace(char *s, const char *old, const char *new);

#endif /* BULLET_FSTRING_H */
