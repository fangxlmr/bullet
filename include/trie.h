/* 
 * Copyright (C) 2018 by Xiaoliang Fang (fangxlmr@foxmail.com).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef _BULLET_TRIE_H
#define _BULLET_TRIE_H

/**
 * Define a new trie_t type
 */
typedef struct _trie *trie_t;

/**
 * trie_new - Create a new trie
 *
 * @trie[out]: the new trie
 *
 * Return 0 if create new trie successfully, -1
 * if out of memory.
 */
int trie_new(trie_t *trie);

/**
 * trie_free - Destroy a trie
 *
 * @trie[in]: the trie
 */
void trie_free(trie_t *trie);

/**
 * trie_add - Add a new word to trie
 *
 * @trie[in]: the trie
 * @word[in]: input word
 *
 * Return 0 if add word to trie successfully,
 * -1 if out of memory.
 */
int trie_add(trie_t trie, const char *word);

/**
 * trie_contains - Check if trie contains a word
 *
 * @trie[in]: the trie
 * @word[in]: the word
 *
 * Return non-zero if the trie contains the given
 * word, 0 if not.
 */
int trie_contains(trie_t trie, const char *word);

/**
 * trie_startswith - Check if it is a prefix in trie
 *
 * @trie[in]: the trie
 * @word[in]: the prefix word
 *
 * Return non-zero if the word is a prefix in trie,
 * 0 if the given word is not a prefix in trie.
 */
int trie_startswith(trie_t trie, const char *prefix);

#endif /* _BULLET_TRIE_H */
