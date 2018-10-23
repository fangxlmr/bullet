/* 
 * error.h - Report error message
 *
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

#ifndef BULLET_ERROR_H
#define BULLET_ERROR_H

/*
 * Print a message with `fprintf (stderr, format, ...)`;
 * if ERRNUM is nozero, follow it with ": " and stderr(ERRNUM).
 * If STATUS is nozero, terminate the program with `exit(STATUS)`.
 */
extern void error(int status, int errnum, const char *format, ...);

#endif /* BULLET_ERROR_H */
