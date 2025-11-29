//
// Created by Franc on 29/11/2025.
//

#pragma once


class CommandLine
{
    bool runCommand();
    bool parseCommand();

    public:
    CommandLine() = default;
    ~CommandLine() = default;

    bool read();
};