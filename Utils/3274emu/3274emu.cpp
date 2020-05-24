/* 
 *  A simple TCP proxy
 *  by Martin Broadhurst (www.martinbroadhurst.com)
 *  Usage: tcpproxy local_host local_port remote_host remote_port
 */
 
#include <stdio.h>
#include <string.h> /* memset() */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <signal.h>
 
#define BACKLOG  10      /* Passed to listen() */
#define BUF_SIZE 4096    /* Buffer for  transfers */

char peer1_5[] = { /* Packet 24 */
0xf5, 0x42, 0x11, 0x40, 0x40, 0x1d, 0x60, 0xc8,
0x85, 0x99, 0x83, 0xa4, 0x93, 0x85, 0xa2, 0x40,
0xe5, 0x85, 0x99, 0xa2, 0x89, 0x96, 0x95, 0x40,
0x40, 0x7a, 0x11, 0x40, 0xd4, 0x1d, 0xe8, 0xf4,
0x4b, 0xf0, 0xf0, 0x11, 0xc1, 0x50, 0x1d, 0x60,
0xc8, 0x96, 0xa2, 0xa3, 0x40, 0x95, 0x81, 0x94,
0x85, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x7a, 0x11, 0xc1, 0xe4, 0x1d, 0xe8,
0xc4, 0xc5, 0xe2, 0xd2, 0xe3, 0xd6, 0xd7, 0x60,
0xf8, 0xc3, 0xc5, 0xd2, 0xd7, 0xe4, 0xe3, 0x11,
0xc2, 0x60, 0x1d, 0x60, 0xc8, 0x96, 0xa2, 0xa3,
0x40, 0xd6, 0xe2, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x7a, 0x11,
0xc2, 0xf4, 0x1d, 0xe8, 0xe6, 0x89, 0x95, 0x84,
0x96, 0xa6, 0xa2, 0x60, 0xf6, 0x4b, 0xf2, 0x4b,
0xf9, 0xf2, 0xf0, 0xf0, 0x40, 0x40, 0xd7, 0x99,
0x96, 0x86, 0x85, 0xa2, 0xa2, 0x89, 0x96, 0x95,
0x81, 0x93, 0x40, 0xf6, 0xf4, 0x60, 0x82, 0x89,
0xa3, 0x11, 0xc3, 0xf0, 0x1d, 0x60, 0xc8, 0x96,
0xa2, 0xa3, 0x40, 0xc1, 0x99, 0x83, 0x88, 0x89,
0xa3, 0x85, 0x83, 0xa3, 0xa4, 0x99, 0x85, 0x40,
0x7a, 0x11, 0xc4, 0xc4, 0x1d, 0xe8, 0xc9, 0x95,
0xa3, 0x85, 0x93, 0x4d, 0xd9, 0x5d, 0x40, 0xa7,
0xf6, 0xf4, 0x11, 0xc5, 0x40, 0x1d, 0x60, 0xd7,
0x99, 0x96, 0x83, 0x85, 0xa2, 0xa2, 0x96, 0x99,
0xa2, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x7a, 0x11, 0xc5, 0xd4, 0x1d, 0xe8, 0xd3,
0xd7, 0x7e, 0xf4, 0x6b, 0x40, 0xc3, 0x96, 0x99,
0x85, 0xa2, 0x7e, 0xf2, 0x6b, 0x40, 0xc3, 0xd7,
0xe4, 0xa2, 0x7e, 0xf1, 0x11, 0xc6, 0x50, 0x1d,
0x60, 0xd3, 0xd7, 0xc1, 0xd9, 0x40, 0xd5, 0x81,
0x94, 0x85, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x7a, 0x11, 0xc6, 0xe4, 0x1d,
0xe8, 0xc8, 0xc5, 0xd9, 0xc3, 0xe4, 0xd3, 0xc5,
0xe2, 0x11, 0xc7, 0x60, 0x1d, 0x60, 0xc4, 0x85,
0xa5, 0x89, 0x83, 0x85, 0x40, 0x95, 0xa4, 0x94,
0x82, 0x85, 0x99, 0x40, 0x40, 0x40, 0x40, 0x40,
0x7a, 0x11, 0xc7, 0xf4, 0x1d, 0xe8, 0xf0, 0x7a,
0xf0, 0xf0, 0xc3, 0xf0, 0x11, 0xc8, 0xf0, 0x1d,
0x60, 0xe2, 0xa4, 0x82, 0x83, 0x88, 0x81, 0x95,
0x95, 0x85, 0x93, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x7a, 0x11, 0xc9, 0xc4, 0x1d,
0xe8, 0xf0, 0xf0, 0xf0, 0xc1, 0x11, 0xc8, 0xf0,
0x1d, 0x60, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x5c, 0x5c, 0x5c,
0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c,
0x5c, 0x40, 0x40, 0x40, 0x5c, 0x5c, 0x5c, 0x5c,
0x40, 0x40, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x6a, 0x6a, 0x11, 0x4a, 0x40, 0x1d, 0x60,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x5c, 0x5c, 0x40, 0x40, 0x40,
0x5c, 0x5c, 0x40, 0x40, 0x40, 0x5c, 0x5c, 0x40,
0x40, 0x40, 0x40, 0x5c, 0x5c, 0x40, 0x40, 0x40,
0x40, 0x5c, 0x5c, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x6a, 0x6a,
0x6a, 0x11, 0x4b, 0x50, 0x1d, 0x60, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x5c, 0x5c, 0x40, 0x40, 0x40, 0x5c, 0x5c,
0x40, 0x40, 0x40, 0x5c, 0x5c, 0x40, 0x40, 0x40,
0x40, 0x5c, 0x5c, 0x40, 0x40, 0x40, 0x5c, 0x5c,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x6a, 0x6a, 0x6a, 0x6a, 0x11,
0x4c, 0x60, 0x1d, 0x60, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x5c, 0x5c, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x5c,
0x5c, 0x40, 0x40, 0x5c, 0x5c, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x6a, 0x6a, 0x40, 0x6a, 0x6a, 0x11, 0x4d, 0xf0,
0x1d, 0x60, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x6a, 0x93, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x6d, 0x6b, 0x6b, 0x6b, 0x60, 0x60,
0x60, 0x6b, 0x6b, 0x6d, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x5c, 0x5c, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x5c, 0x5c, 0x40,
0x5c, 0x5c, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x6a, 0x6a, 0x40,
0x40, 0x6a, 0x6a, 0x11, 0x4f, 0x40, 0x1d, 0x60,
0x40, 0xe9, 0xe9, 0xe9, 0xa9, 0xa9, 0x40, 0x61,
0x6b, 0x7d, 0x4b, 0x60, 0x7d, 0x79, 0x7d, 0x40,
0x40, 0x40, 0x40, 0x60, 0x4b, 0x40, 0x40, 0x5e,
0x60, 0x5e, 0x5e, 0x6b, 0x40, 0x40, 0x40, 0x40,
0x5c, 0x5c, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x5c, 0x5c, 0x5c, 0x5c, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x6a, 0x6a, 0x40, 0x40, 0x40, 0x6a,
0x6a, 0x11, 0x50, 0x50, 0x1d, 0x60, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x6a, 0x6b, 0xf4, 0x60,
0x40, 0x40, 0x5d, 0x40, 0x5d, 0x60, 0x6b, 0x6d,
0x4b, 0x40, 0x6b, 0x4d, 0x40, 0x4d, 0x40, 0x40,
0x7d, 0x7d, 0x60, 0x7d, 0x40, 0x40, 0x5c, 0x5c,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x6a,
0x6a, 0x40, 0x40, 0x40, 0x40, 0x6a, 0x6a, 0x11,
0xd1, 0x60, 0x1d, 0x60, 0x40, 0x40, 0x40, 0x40,
0x40, 0x7d, 0x60, 0x60, 0x60, 0x7d, 0x7d, 0x4d,
0x6d, 0x61, 0x60, 0x60, 0x7d, 0x40, 0x40, 0x79,
0x60, 0x7d, 0x5d, 0x6d, 0x5d, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x5c, 0x5c, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x5c,
0x5c, 0x40, 0x40, 0x5c, 0x5c, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x6a, 0x6a, 0x40, 0x40,
0x40, 0x40, 0x40, 0x6a, 0x6a, 0x40, 0x40, 0x40,
0x40, 0x6a, 0x6a, 0x6a, 0x6a, 0x6a, 0x6a, 0x6a,
0x6a, 0x6a, 0x6a, 0x11, 0xd2, 0xf0, 0x1d, 0x60,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x5c, 0x5c, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x5c, 0x5c, 0x40, 0x40, 0x40,
0x5c, 0x5c, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x6a, 0x6a, 0x6a, 0x6a, 0x6a, 0x6a, 0x6a, 0x6a,
0x6a, 0x6a, 0x6a, 0x40, 0x40, 0xe4, 0x97, 0x84,
0x81, 0xa3, 0x85, 0x40, 0xf0, 0xf8, 0x11, 0xd4,
0x40, 0x1d, 0x60, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0xe3, 0x88, 0x85, 0x40, 0xd4, 0xe5,
0xe2, 0x40, 0xf3, 0x4b, 0xf8, 0x91, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x5c, 0x5c, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x5c, 0x5c,
0x40, 0x40, 0x40, 0x40, 0x5c, 0x5c, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x6a, 0x6a, 0x11, 0xd5, 0x50, 0x1d,
0x60, 0x40, 0x40, 0x40, 0x40, 0x40, 0xe3, 0xa4,
0x99, 0x4d, 0x95, 0x5d, 0x92, 0x85, 0xa8, 0x40,
0xe2, 0xa8, 0xa2, 0xa3, 0x85, 0x94, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x5c, 0x5c, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x5c, 0x5c, 0x40, 0x40,
0x40, 0x40, 0x40, 0x5c, 0x5c, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x6a, 0x6a, 0x11, 0xd6, 0x60, 0x1d, 0x60, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x5c, 0x5c, 0x5c,
0x5c, 0x5c, 0x5c, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x5c, 0x5c, 0x5c, 0x5c, 0x40, 0x40, 0x40,
0x40, 0x40, 0x5c, 0x5c, 0x5c, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x6a, 0x6a, 0x6a, 0x6a,
0x6a, 0x6a, 0x11, 0xd7, 0xf0, 0x1d, 0x60, 0x11,
0xd9, 0x40, 0x1d, 0x60, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0xe3, 0xd2, 0xf3, 0x40, 0x83, 0x99, 0x85, 0x81,
0xa3, 0x85, 0x84, 0x40, 0x82, 0xa8, 0x40, 0xe5,
0x96, 0x93, 0x92, 0x85, 0x99, 0x40, 0xc2, 0x81,
0x95, 0x84, 0x92, 0x85, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0xa5, 0x82, 0x81, 0x95, 0x84,
0x92, 0x85, 0x7c, 0x82, 0xa2, 0x97, 0x60, 0x87,
0x94, 0x82, 0x88, 0x4b, 0x83, 0x96, 0x94, 0x11,
0x5a, 0x50, 0x1d, 0x60, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0xe3, 0xd2, 0xf4, 0x60, 0x40, 0xa4, 0x97, 0x84,
0x81, 0xa3, 0x85, 0x40, 0x82, 0xa8, 0x40, 0xd1,
0xa4, 0x85, 0x99, 0x87, 0x85, 0x95, 0x40, 0xe6,
0x89, 0x95, 0x92, 0x85, 0x93, 0x94, 0x81, 0x95,
0x95, 0x40, 0x40, 0xa6, 0x89, 0x95, 0x92, 0x85,
0x93, 0x94, 0x81, 0x95, 0x95, 0x7c, 0x89, 0x84,
0x4b, 0x85, 0xa3, 0x88, 0xa9, 0x4b, 0x83, 0x88,
0x11, 0x5b, 0x60, 0x1d, 0x60, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0xa2, 0x85, 0x85, 0x40, 0xe3, 0xd2,
0xf4, 0x60, 0x4b, 0xc3, 0xd9, 0xc5, 0xc4, 0xc9,
0xe3, 0xe2, 0x40, 0x86, 0x96, 0x99, 0x40, 0x83,
0x96, 0x94, 0x97, 0x93, 0x85, 0xa3, 0x85, 0x40,
0x83, 0x99, 0x85, 0x84, 0x89, 0xa3, 0xa2, 0xff,
0xef };
char peer1_6[] = { /* Packet 26 */
0xf5, 0xc3, 0x11, 0x40, 0x40, 0xe3, 0x85, 0x99,
0x94, 0x89, 0x95, 0x81, 0x93, 0x11, 0x40, 0xc8,
0x1d, 0xf8, 0x11, 0x40, 0x4a, 0x1d, 0xf8, 0xc3,
0xe4, 0xe4, 0xf0, 0xc3, 0xf0, 0x40, 0x40, 0x11,
0x40, 0xd3, 0x1d, 0xf8, 0x11, 0xc1, 0xc1, 0x1d,
0xf8, 0xc4, 0x81, 0xa3, 0x85, 0x11, 0xc1, 0xc6,
0x1d, 0xf8, 0x11, 0xc1, 0xc7, 0x1d, 0xf8, 0xf0,
0xf2, 0x4b, 0xf0, 0xf1, 0x4b, 0xf2, 0xf0, 0x11,
0xc1, 0x50, 0x1d, 0xf8, 0x11, 0xc2, 0xd1, 0x1d,
0xf8, 0xe3, 0x89, 0x94, 0x85, 0x11, 0xc2, 0xd6,
0x1d, 0xf8, 0x11, 0xc2, 0xd7, 0x1d, 0xf8, 0xf2,
0xf0, 0x7a, 0xf4, 0xf7, 0x7a, 0xf1, 0xf0, 0x11,
0xc2, 0x60, 0x1d, 0xf0, 0x11, 0xc4, 0x4a, 0x1d,
0xf0, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c,
0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x11, 0xc4, 0xd7,
0x1d, 0xf0, 0x11, 0xc4, 0xd9, 0x1d, 0xf0, 0x5c,
0x5c, 0x5c, 0x5c, 0x11, 0xc4, 0x5e, 0x1d, 0xf0,
0x11, 0xc4, 0x5f, 0x1d, 0xf0, 0x5c, 0x5c, 0x5c,
0x5c, 0x5c, 0x11, 0xc4, 0xe5, 0x1d, 0xf0, 0x11,
0xc4, 0x6e, 0x1d, 0xf0, 0x4f, 0x4f, 0x11, 0xc4,
0xf1, 0x1d, 0xf0, 0x11, 0xc5, 0x5a, 0x1d, 0xf0,
0x5c, 0x5c, 0x11, 0xc5, 0x5d, 0x1d, 0xf0, 0x11,
0xc5, 0x5f, 0x1d, 0xf0, 0x5c, 0x5c, 0x11, 0xc5,
0xe2, 0x1d, 0xf0, 0x11, 0xc5, 0xe4, 0x1d, 0xf0,
0x5c, 0x5c, 0x11, 0xc5, 0xe7, 0x1d, 0xf0, 0x11,
0xc5, 0x6a, 0x1d, 0xf0, 0x5c, 0x5c, 0x11, 0xc5,
0x6d, 0x1d, 0xf0, 0x11, 0xc5, 0xf0, 0x1d, 0xf0,
0x5c, 0x5c, 0x11, 0xc5, 0xf3, 0x1d, 0xf0, 0x11,
0xc5, 0x7d, 0x1d, 0xf0, 0x4f, 0x4f, 0x4f, 0x11,
0xc6, 0xc1, 0x1d, 0xf0, 0x11, 0xc6, 0x6a, 0x1d,
0xf0, 0x5c, 0x5c, 0x11, 0xc6, 0x6d, 0x1d, 0xf0,
0x11, 0xc6, 0x6f, 0x1d, 0xf0, 0x5c, 0x5c, 0x11,
0xc6, 0xf2, 0x1d, 0xf0, 0x11, 0xc6, 0xf4, 0x1d,
0xf0, 0x5c, 0x5c, 0x11, 0xc6, 0xf7, 0x1d, 0xf0,
0x11, 0xc6, 0x7a, 0x1d, 0xf0, 0x5c, 0x5c, 0x11,
0xc6, 0x7d, 0x1d, 0xf0, 0x11, 0xc6, 0x7f, 0x1d,
0xf0, 0x5c, 0x5c, 0x11, 0xc7, 0xc2, 0x1d, 0xf0,
0x11, 0xc7, 0x4c, 0x1d, 0xf0, 0x4f, 0x4f, 0x4f,
0x4f, 0x11, 0xc7, 0xd1, 0x1d, 0xf0, 0x11, 0xc7,
0x7f, 0x1d, 0xf0, 0x5c, 0x5c, 0x11, 0xc8, 0xc2,
0x1d, 0xf0, 0x11, 0xc8, 0x4a, 0x1d, 0xf0, 0x5c,
0x5c, 0x11, 0xc8, 0x4d, 0x1d, 0xf0, 0x11, 0xc8,
0x4e, 0x1d, 0xf0, 0x5c, 0x5c, 0x11, 0xc8, 0xd1,
0x1d, 0xf0, 0x11, 0xc8, 0x5b, 0x1d, 0xf0, 0x4f,
0x4f, 0x11, 0xc8, 0x5e, 0x1d, 0xf0, 0x4f, 0x4f,
0x11, 0xc8, 0x61, 0x1d, 0xf0, 0x11, 0xc8, 0xf7,
0x1d, 0xf8, 0x4f, 0x93, 0x11, 0xc8, 0x7a, 0x1d,
0xf8, 0x11, 0xc8, 0x7f, 0x1d, 0xf8, 0x6d, 0x6b,
0x6b, 0x6b, 0x60, 0x60, 0x60, 0x6b, 0x6b, 0x6d,
0x11, 0xc9, 0x4a, 0x1d, 0xf8, 0x11, 0xc9, 0x4f,
0x1d, 0xf0, 0x5c, 0x5c, 0x11, 0xc9, 0xd2, 0x1d,
0xf0, 0x11, 0xc9, 0x5a, 0x1d, 0xf0, 0x5c, 0x5c,
0x40, 0x5c, 0x5c, 0x11, 0xc9, 0x60, 0x1d, 0xf0,
0x11, 0xc9, 0x6a, 0x1d, 0xf0, 0x4f, 0x4f, 0x11,
0xc9, 0x6d, 0x1d, 0xf0, 0x11, 0xc9, 0x6e, 0x1d,
0xf0, 0x4f, 0x4f, 0x11, 0xc9, 0xf1, 0x1d, 0xf0,
0x11, 0x4a, 0x40, 0x1d, 0xf8, 0xe9, 0xe9, 0xe9,
0xa9, 0xa9, 0x40, 0x61, 0x6b, 0x7d, 0x4b, 0x60,
0x7d, 0x79, 0x7d, 0x40, 0x40, 0x40, 0x40, 0x60,
0x4b, 0x40, 0x40, 0x5e, 0x60, 0x5e, 0x5e, 0x6b,
0x11, 0x4a, 0x5c, 0x1d, 0xf8, 0x11, 0x4a, 0x5f,
0x1d, 0xf0, 0x5c, 0x5c, 0x11, 0x4a, 0xe2, 0x1d,
0xf0, 0x11, 0x4a, 0x6a, 0x1d, 0xf0, 0x5c, 0x5c,
0x5c, 0x5c, 0x11, 0x4a, 0x6f, 0x1d, 0xf0, 0x11,
0x4a, 0xf9, 0x1d, 0xf0, 0x4f, 0x4f, 0x11, 0x4a,
0x7c, 0x1d, 0xf0, 0x11, 0x4a, 0x7e, 0x1d, 0xf0,
0x4f, 0x4f, 0x11, 0x4b, 0xc1, 0x1d, 0xf0, 0x11,
0x4b, 0xd5, 0x1d, 0xf8, 0x4f, 0x6b, 0xf4, 0x60,
0x40, 0x40, 0x5d, 0x40, 0x5d, 0x60, 0x6b, 0x6d,
0x4b, 0x40, 0x6b, 0x4d, 0x40, 0x4d, 0x40, 0x40,
0x7d, 0x7d, 0x60, 0x7d, 0x11, 0x4b, 0x6e, 0x1d,
0xf8, 0x11, 0x4b, 0x6f, 0x1d, 0xf0, 0x5c, 0x5c,
0x11, 0x4b, 0xf2, 0x1d, 0xf0, 0x11, 0x4b, 0x7a,
0x1d, 0xf0, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x11,
0x4c, 0x40, 0x1d, 0xf0, 0x11, 0x4c, 0xc8, 0x1d,
0xf0, 0x4f, 0x4f, 0x11, 0x4c, 0x4b, 0x1d, 0xf0,
0x11, 0x4c, 0x4e, 0x1d, 0xf0, 0x4f, 0x4f, 0x11,
0x4c, 0xd1, 0x1d, 0xf0, 0x11, 0x4c, 0xe4, 0x1d,
0xf8, 0x7d, 0x60, 0x60, 0x60, 0x7d, 0x7d, 0x4d,
0x6d, 0x61, 0x60, 0x60, 0x7d, 0x40, 0x40, 0x79,
0x60, 0x7d, 0x5d, 0x6d, 0x5d, 0x11, 0x4c, 0xf9,
0x1d, 0xf8, 0x11, 0x4c, 0x7f, 0x1d, 0xf0, 0x5c,
0x5c, 0x11, 0x4d, 0xc2, 0x1d, 0xf0, 0x11, 0x4d,
0x4a, 0x1d, 0xf0, 0x5c, 0x5c, 0x11, 0x4d, 0x4d,
0x1d, 0xf0, 0x11, 0x4d, 0x4e, 0x1d, 0xf0, 0x5c,
0x5c, 0x11, 0x4d, 0xd1, 0x1d, 0xf0, 0x11, 0x4d,
0xd7, 0x1d, 0xf0, 0x4f, 0x4f, 0x11, 0x4d, 0x5a,
0x1d, 0xf0, 0x11, 0x4d, 0x5e, 0x1d, 0xf0, 0x4f,
0x4f, 0x11, 0x4d, 0x61, 0x1d, 0xf0, 0x11, 0x4d,
0xe4, 0x1d, 0xf0, 0x4f, 0x4f, 0x4f, 0x4f, 0x4f,
0x4f, 0x4f, 0x4f, 0x4f, 0x4f, 0x11, 0x4d, 0x6f,
0x1d, 0xf0, 0x11, 0x4e, 0x4f, 0x1d, 0xf0, 0x5c,
0x5c, 0x11, 0x4e, 0xd2, 0x1d, 0xf0, 0x11, 0x4e,
0x5a, 0x1d, 0xf0, 0x5c, 0x5c, 0x11, 0x4e, 0x5d,
0x1d, 0xf0, 0x11, 0x4e, 0x5f, 0x1d, 0xf0, 0x5c,
0x5c, 0x11, 0x4e, 0xe2, 0x1d, 0xf0, 0x11, 0x4e,
0xe7, 0x1d, 0xf0, 0x4f, 0x4f, 0x4f, 0x4f, 0x4f,
0x4f, 0x4f, 0x4f, 0x4f, 0x4f, 0x4f, 0x11, 0x4e,
0xf3, 0x1d, 0xf0, 0x11, 0x4f, 0xc6, 0x1d, 0xf8,
0xe3, 0x88, 0x85, 0x40, 0xd4, 0xe5, 0xe2, 0x40,
0xf3, 0x4b, 0xf8, 0x91, 0x11, 0x4f, 0xd3, 0x1d,
0xf8, 0x11, 0x4f, 0x5f, 0x1d, 0xf0, 0x5c, 0x5c,
0x11, 0x4f, 0xe2, 0x1d, 0xf0, 0x11, 0x4f, 0x6a,
0x1d, 0xf0, 0x5c, 0x5c, 0x11, 0x4f, 0x6d, 0x1d,
0xf0, 0x11, 0x4f, 0xf0, 0x1d, 0xf0, 0x5c, 0x5c,
0x11, 0x4f, 0xf3, 0x1d, 0xf0, 0x11, 0x4f, 0x7e,
0x1d, 0xf0, 0x4f, 0x4f, 0x11, 0x50, 0xc1, 0x1d,
0xf0, 0x11, 0x50, 0xd4, 0x1d, 0xf8, 0xe3, 0xa4,
0x99, 0x4d, 0x95, 0x5d, 0x92, 0x85, 0xa8, 0x40,
0xe2, 0xa8, 0xa2, 0xa3, 0x85, 0x94, 0x11, 0x50,
0xe5, 0x1d, 0xf8, 0x11, 0x50, 0x6f, 0x1d, 0xf0,
0x5c, 0x5c, 0x11, 0x50, 0xf2, 0x1d, 0xf0, 0x11,
0x50, 0x7a, 0x1d, 0xf0, 0x5c, 0x5c, 0x11, 0x50,
0x7d, 0x1d, 0xf0, 0x11, 0xd1, 0xc1, 0x1d, 0xf0,
0x5c, 0x5c, 0x11, 0xd1, 0xc4, 0x1d, 0xf0, 0x11,
0xd1, 0x4e, 0x1d, 0xf0, 0x4f, 0x4f, 0x11, 0xd1,
0xd1, 0x1d, 0xf0, 0x11, 0xd1, 0x7d, 0x1d, 0xf0,
0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x11, 0xd2,
0xc4, 0x1d, 0xf0, 0x11, 0xd2, 0xc9, 0x1d, 0xf0,
0x5c, 0x5c, 0x5c, 0x5c, 0x11, 0xd2, 0x4e, 0x1d,
0xf0, 0x11, 0xd2, 0xd2, 0x1d, 0xf0, 0x5c, 0x5c,
0x5c, 0x11, 0xd2, 0xd6, 0x1d, 0xf0, 0x11, 0xd2,
0x5c, 0x1d, 0xf0, 0x4f, 0x4f, 0x4f, 0x4f, 0x4f,
0x4f, 0x11, 0xd2, 0xe3, 0x1d, 0xf0, 0x11, 0xd4,
0x4b, 0x1d, 0xf0, 0xe3, 0xd2, 0xf3, 0x40, 0x83,
0x99, 0x85, 0x81, 0xa3, 0x85, 0x84, 0x40, 0x82,
0xa8, 0x40, 0xe5, 0x96, 0x93, 0x92, 0x85, 0x99,
0x40, 0xc2, 0x81, 0x95, 0x84, 0x92, 0x85, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0xa5, 0x82,
0x81, 0x95, 0x84, 0x92, 0x85, 0x7c, 0x82, 0xa2,
0x97, 0x60, 0x87, 0x94, 0x82, 0x88, 0x4b, 0x83,
0x96, 0x94, 0x11, 0xd5, 0xc3, 0x1d, 0xf0, 0x11,
0xd5, 0x5b, 0x1d, 0xf0, 0xe3, 0xd2, 0xf4, 0x60,
0x40, 0xa4, 0x97, 0x84, 0x81, 0xa3, 0x85, 0x40,
0x82, 0xa8, 0x40, 0xd1, 0xa4, 0x85, 0x99, 0x87,
0x85, 0x95, 0x40, 0xe6, 0x89, 0x95, 0x92, 0x85,
0x93, 0x94, 0x81, 0x95, 0x95, 0x40, 0x40, 0xa6,
0x89, 0x95, 0x92, 0x85, 0x93, 0x94, 0x81, 0x95,
0x95, 0x7c, 0x89, 0x84, 0x4b, 0x85, 0xa3, 0x88,
0xa9, 0x4b, 0x83, 0x88, 0x11, 0xd6, 0xd4, 0x1d,
0xf0, 0x11, 0xd6, 0xf4, 0x1d, 0xf0, 0xa2, 0x85,
0x85, 0x40, 0xe3, 0xd2, 0xf4, 0x60, 0x4b, 0xc3,
0xd9, 0xc5, 0xc4, 0xc9, 0xe3, 0xe2, 0x40, 0x86,
0x96, 0x99, 0x40, 0x83, 0x96, 0x94, 0x97, 0x93,
0x85, 0xa3, 0x85, 0x40, 0x83, 0x99, 0x85, 0x84,
0x89, 0xa3, 0xa2, 0x11, 0xd7, 0x5a, 0x1d, 0xf0,
0x11, 0xd9, 0x5d, 0x1d, 0xf0, 0xd4, 0xe5, 0xe2,
0x40, 0xf3, 0x4b, 0xf8, 0x91, 0x40, 0xd3, 0x85,
0xa5, 0x85, 0x93, 0x40, 0xf8, 0xf5, 0xf0, 0xf5,
0x11, 0xd9, 0xf1, 0x1d, 0xf0, 0x11, 0x5b, 0x5f,
0x1d, 0xf8, 0xd3, 0x96, 0x87, 0x96, 0x95, 0x40,
0x7e, 0x7e, 0x7e, 0x6e, 0x11, 0x5b, 0x6a, 0x1d,
0xc8, 0x13, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
0x40, 0x40, 0x11, 0x5d, 0x6b, 0x1d, 0xf8, 0xd9,
0xe4, 0xd5, 0xd5, 0xc9, 0xd5, 0xc7, 0x40, 0x40,
0xe3, 0xd2, 0xf4, 0x60, 0x11, 0x5d, 0xf9, 0x1d,
0xf8, 0x11, 0x5d, 0x7f, 0x1d, 0xf8, 0xff, 0xef };


unsigned int transfer(int from, int to)
{
  char buf[BUF_SIZE]
;  unsigned int disconnected = 0;
  size_t bytes_read, bytes_written;
  bytes_read = read(from, buf, BUF_SIZE);
  if (bytes_read == 0) {
    disconnected = 1;
  }
  else {
    bytes_written = write(to, buf, bytes_read);
    if (bytes_written == -1) {
      disconnected = 1;
    }
  }
  return disconnected;
}

int state;
unsigned char code;
bool doTerminalTypeDone;
bool doBinaryDone;
bool doEORDone;
bool willBinaryDone;
bool willEORDone;


void clearTelnetOptions() {
  doTerminalTypeDone =false;
  doBinaryDone =false;
  doEORDone = false;
  willBinaryDone = false;
  willEORDone = false;
} 

bool testTelnetOptionsDone() {
  if (doTerminalTypeDone && doBinaryDone && doEORDone && willBinaryDone && willEORDone) {
    return true;
  }
  return false;
}

#define BINARY 0x00
#define TERMTYPE 0x18
#define EOR 0x19

#define SE 240
#define NOP 241
#define DATA_MARK 242
#define BREAK 243
#define INTERRUPT_PROCESS 244
#define ABORT_OUTPUT 246
#define ARE_YOU_THERE 247
#define ERASE_CHAR 247
#define ERASELINE 248
#define GOAHEAD 249
#define SB   250
#define WILL 251
#define WONT 252
#define DO   253
#define DONT 254
#define IAC 255



void process3270Data(unsigned char ch) {
  if (testTelnetOptionsDone()) {
    // process TN3270 data!
  } else {
    // We are not ready for procssing TN3270 data yet. No point in forwarding data
    printf("Not yet negotaited options done\n");
  }
  
}

unsigned int sendTelnetSubnegotationParams (int socket, const unsigned char * paramString, int length) {
  size_t bytes_written;
  unsigned int disconnected = 0;
  unsigned char sb[] = {0xFF, 0xFA};
  unsigned char sbEnd[] = {0xFF, 0xF0};
  bytes_written = write(socket, sb, 2);
  bytes_written = write(socket, paramString, length);
  bytes_written = write(socket, sbEnd, 2);
  if (bytes_written == -1) {
    disconnected = 1;
  }  
  return disconnected;
}


#define STATE_NORMAL 0
#define STATE_IAC_RECEIVED 1
#define STATE_PROCESS_OPTION 2
#define STATE_SUBPARAM_TYPE 3
#define STATE_SUBPARAM_OPCODE 4

unsigned char subParamsBuf [BUF_SIZE];
int subParamPtr = 0; 

void storeSubParam (unsigned char ch) {
  printf ("storing %c at ptr=%d\n", ch, subParamPtr);
  subParamsBuf[subParamPtr++] = ch;
}

void endOfSubParam () {
  subParamsBuf[subParamPtr++] = 0;
}

unsigned int  processBSCDataFromHercules(int server, int client) {
  unsigned int disconnected = 0;
  return disconnected;
}


bool subState;

unsigned int processDataFromTerminal (int client) {
  unsigned char buf[BUF_SIZE];
  const unsigned char terminalTypeRequest [] = {0x18, 0x01};
  int i;
  unsigned int disconnected = 0;
  size_t bytes_read, bytes_written;
  bytes_read = read(client, buf,BUF_SIZE);
  if (bytes_read == 0) {
    disconnected = 1;
  } else {
    for (i=0; i<bytes_read; i++) {
      printf ("read %02x : %c from terminal\n", buf[i] & 0xff, buf[i] & 0xff);
      switch (state) {
      case STATE_NORMAL:
	if (buf[i] == IAC) {
	  printf ("IAC received\n");
	  state = STATE_IAC_RECEIVED;
	} else {
	  // Normal character - do normal processing according to 3270 Data stream
	  if (subState) {
	    storeSubParam(buf[i]);
	  } else {
	    process3270Data (buf[i]);
	  }
	}
	break;
      case STATE_IAC_RECEIVED:

	switch (buf[i]) {
	case IAC:
	  // We got another IAC which means that normal processing of a 255 byte should take place
	  state = STATE_NORMAL;
	  if (subState) {
	    storeSubParam(255);
	  } else {
	    process3270Data(255);
	  }
	  break;
	case DONT:
	case DO:
	case WONT:
	case WILL:
	  state = STATE_PROCESS_OPTION;
	  code = buf[i];
	  printf ("received DONT, DO, WONT or WILL: %02x\n", code);
	  break;
	case SB:
	  printf ("Received SB\n");
	  state = STATE_SUBPARAM_TYPE;
	  break;
	case SE:
	  printf("Received SE\n");
	  state = STATE_NORMAL;
	  endOfSubParam();
	  doTerminalTypeDone = true;
	  printf ("Terminal param received: %s\n", subParamsBuf);
	  write(client, peer1_5, sizeof (peer1_5));
	  write(client, peer1_6, sizeof (peer1_6));
	  subState = false;
	  break;
	}
	break;
      case STATE_SUBPARAM_TYPE:
	printf ("Received SUVPARAM TYPE = %02x\n", buf[i]);
	state = STATE_SUBPARAM_OPCODE;
	break;
      case STATE_SUBPARAM_OPCODE:
	printf ("Received SUBPARAM OPCODE = %02x\n", buf[i]);
	state = STATE_NORMAL;
	subState = true;
	break;
      case STATE_PROCESS_OPTION:
	state = STATE_NORMAL;
	switch (buf[i]) {
	case TERMTYPE:
	  printf ("Received TERMTYPE\n");
	  if (code == WILL) {
	    sendTelnetSubnegotationParams(client, terminalTypeRequest, 2);
	    
	  }
	  break;
	case EOR:
	  printf ("Received EOR\n");
	  if (code == WILL) {
	    willEORDone = true;
	  } else if (code == DO) {
	    doEORDone = true;
	  }
	  break;
	case BINARY: 
	  printf ("Recieved BINARY\n");
	  if (code == WILL) {
	    willBinaryDone = true;
	  } else if (code == DO) {
	    doBinaryDone = true;
	  }
	  break;
	}
	break;	  
      }
    }
  }
  return disconnected;
}

unsigned int sendTelnetDo(int socket, unsigned char option) {
  unsigned int disconnected = 0;
  unsigned char buf[] = {0xFF, 0xFD, 0x00};
  size_t bytes_written;
  buf[2] = option;
  // Write Telnet negotation to client
  bytes_written = write(socket, buf, 3); 
  if (bytes_written == -1) {
    disconnected = 1;
  }  
  return disconnected;
}

unsigned int sendTelnetWill(int socket, unsigned char option) {
  unsigned int disconnected = 0;
  char buf[] = {0xFF, 0xFB, 0x00};
  size_t bytes_written;
  buf[2] = option;
  // Write Telnet negotation to client
  bytes_written = write(socket, buf, 3); 
  if (bytes_written == -1) {
    disconnected = 1;
  }  
  return disconnected;
}

unsigned int sendTelnetDont(int socket, unsigned char option) {
  unsigned int disconnected = 0;
  char buf[] = {0xFF, 0xFE, 0x00};
  size_t bytes_written;
  buf[2] = option;
  // Write Telnet negotation to client
  bytes_written = write(socket, buf, 3); 
  if (bytes_written == -1) {
    disconnected = 1;
  }  
  return disconnected;
}

unsigned int sendTelnetWont(int socket, unsigned char option) {
  unsigned int disconnected = 0;
  char buf[] = {0xFF, 0xFC, 0x00};
  size_t bytes_written;
  buf[2] = option;
  // Write Telnet negotation to client
  bytes_written = write(socket, buf, 3); 
  if (bytes_written == -1) {
    disconnected = 1;
  }  
  return disconnected;
}


void handle(int client, const char *remote_host, const char *remote_port)
{
  struct addrinfo hints, *res;
  int server = -1;
  unsigned int disconnected = 0;
  fd_set set;
  unsigned int max_sock;


  /* Get the address info */
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  if (getaddrinfo(remote_host, remote_port, &hints, &res) != 0) {
    perror("getaddrinfo");
    close(client);
    return;
  }
 
  /* Create the socket */
  server = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (server == -1) {
    perror("socket");
    close(client);
    return;
  }
 
  /* Connect to the host */
  /*
  if (connect(server, res->ai_addr, res->ai_addrlen) == -1) {
    perror("connect");
    close(client);
    return;
  }
  */

  if (client > server) {
    max_sock = client;
  }
  else {
    max_sock = server;
  }
  clearTelnetOptions();
  sendTelnetWill(client, 0x00);
  sendTelnetDo(client, 0x00);
  sendTelnetWill(client, 0x19);
  sendTelnetDo(client, 0x19);
  sendTelnetDo(client, 0x18);

  /* Main transfer loop */
  while (!disconnected) {
    FD_ZERO(&set);
    FD_SET(client, &set);
    FD_SET(server, &set);
    if (select(max_sock + 1, &set, NULL, NULL, NULL) == -1) {
      perror("select");
      break;
    }
    if (FD_ISSET(client, &set)) {
      // Here is where we take care of input from the TN3270 terminal client.
      disconnected = processDataFromTerminal(client);
    }
    if (FD_ISSET(server, &set)) {
      disconnected = processBSCDataFromHercules(server, client);
    }
  }
  close(server);
  close(client);
}
 
int main(int argc, char **argv)
{
  int sock;
  struct addrinfo hints, *res;
  int reuseaddr = 1; /* True */
  const char *local_host, *local_port, *remote_host, *remote_port;
  
  /* Get the local and remote hosts and ports from the command line */
  if (argc < 5) {
    fprintf(stderr, "Usage: tcpproxy local_host local_port remote_host remote_port\n");
    return 1;
  }
  local_host = argv[1];
  local_port = argv[2];
  remote_host = argv[3];
  remote_port = argv[4];
 
  /* Get the address info */
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  if (getaddrinfo(local_host, local_port, &hints, &res) != 0) {
    perror("getaddrinfo");
    return 1;
  }
 
  /* Create the socket */
  sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (sock == -1) {
    perror("socket");
    freeaddrinfo(res);
    return 1;
  }
 
  /* Enable the socket to reuse the address */
  if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(int)) == -1) {
    perror("setsockopt");
    freeaddrinfo(res);
    return 1;
  }
 
  /* Bind to the address */
  if (bind(sock, res->ai_addr, res->ai_addrlen) == -1) {
    perror("bind");
    freeaddrinfo(res);
    return 1;
  }
 
  /* Listen */
  if (listen(sock, BACKLOG) == -1) {
    perror("listen");
    freeaddrinfo(res);
    return 1;
  }
 
  freeaddrinfo(res);
 
  /* Ignore broken pipe signal */
  signal(SIGPIPE, SIG_IGN);
  
  /* Main loop */
  while (1) {
    socklen_t size = sizeof(struct sockaddr_in);
    struct sockaddr_in their_addr;
    int newsock = accept(sock, (struct sockaddr*)&their_addr, &size);
 
    if (newsock == -1) {
      perror("accept");
    }
    else {
      printf("Got a connection from %s on port %d\n",
	     inet_ntoa(their_addr.sin_addr), htons(their_addr.sin_port));
      handle(newsock, remote_host, remote_port);
    }
  }
 
  close(sock);
 
  return 0;
}