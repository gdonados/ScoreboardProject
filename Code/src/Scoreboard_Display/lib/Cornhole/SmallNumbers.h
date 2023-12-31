#ifndef SMALLNUMBERS_H
#define SMALLNUMBERS_H

#include <Arduino.h>

const static byte smallNumbers[10][5][5] =
    {
        // 0
        {
            {0, 1, 1, 1, 0},
            {1, 0, 0, 0, 1},
            {1, 0, 0, 0, 1},
            {1, 0, 0, 0, 1},
            {0, 1, 1, 1, 0}},

        // 1
        {
            {0, 0, 1, 0, 0},
            {0, 1, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 1, 1, 1, 1}},

        // 2
        {
            {1, 1, 1, 1, 0},
            {0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0},
            {1, 1, 1, 1, 1}},

        // 3
        {
            {1, 1, 1, 1, 0},
            {0, 0, 0, 0, 1},
            {0, 1, 1, 1, 0},
            {0, 0, 0, 0, 1},
            {1, 1, 1, 1, 0}},

        // 4
        {
            {1, 0, 0, 0, 1},
            {1, 0, 0, 0, 1},
            {1, 1, 1, 1, 1},
            {0, 0, 0, 0, 1},
            {0, 0, 0, 0, 1}},

        // 5
        {
            {1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0},
            {1, 1, 1, 1, 1},
            {0, 0, 0, 0, 1},
            {1, 1, 1, 1, 0}},

        // 6
        {
            {0, 1, 1, 1, 1},
            {1, 0, 0, 0, 0},
            {1, 1, 1, 1, 0},
            {1, 0, 0, 0, 1},
            {0, 1, 1, 1, 0}},

        // 7
        {
            {1, 1, 1, 1, 1},
            {0, 0, 0, 0, 1},
            {0, 0, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 1, 0, 0, 0}},

        // 8
        {
            {0, 1, 1, 1, 0},
            {1, 0, 0, 0, 1},
            {0, 1, 1, 1, 0},
            {1, 0, 0, 0, 1},
            {0, 1, 1, 1, 0}},

        // 9
        {
            {0, 1, 1, 1, 0},
            {1, 0, 0, 0, 1},
            {0, 1, 1, 1, 1},
            {0, 0, 0, 0, 1},
            {0, 0, 0, 0, 1}}};

#endif