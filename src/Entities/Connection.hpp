#pragma once

struct Connection
{
    float k;            // spring coefficient
    float c;            // damping coefficient
    float length;
    unsigned int start; // connections
    unsigned int end;
};