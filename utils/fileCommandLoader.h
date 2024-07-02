//
// Created by ja on 7/2/24.
//

#ifndef ARCADE_GAMES_FILECOMMANDLOADER_H
#define ARCADE_GAMES_FILECOMMANDLOADER_H

#include <functional>
#include <vector>
#include <string>
#include <cstdint>

class Color;
class Vec2D;

enum CommandType{
    COMMAND_ONE_LINE = 0,
    COMMAND_MULTI_LINE
};

struct ParseFuncParams {
    std::string line;
    size_t dilimitPos;
    int lineNum;
};

using ParseFunc = std::function<void(const ParseFuncParams &params)>;

struct Command {
    CommandType commandType = COMMAND_ONE_LINE;
    std::string command = "";
    ParseFunc parseFunc = nullptr;
};


class FileCommandLoader {
public:
    void AddCommand(const Command &command);
    bool LoadFile(const std::string &filePath);

    static Color ReadColor(const ParseFuncParams &params);
    static Vec2D ReadSize(const ParseFuncParams &params);
    static int ReadInt(const ParseFuncParams &params);
    static std::string ReadString(const ParseFuncParams &params);
    static char ReadChar(const ParseFuncParams &params);

private:
    std::vector<Command> mCommands;
};


#endif//ARCADE_GAMES_FILECOMMANDLOADER_H
