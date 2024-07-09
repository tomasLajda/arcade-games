//
// Created by ja on 7/8/24.
//

#include "breakOutLevel.h"
#include "../../graphics/screen.h"
#include "ball.h"
#include "boundaryEdge.h"
#include "../../utils/fileCommandLoader.h"
#include "../../app/app.h"

BreakOutLevel::BreakOutLevel() {}

void BreakOutLevel::Init(const AARectangle &boundary) {
    CreateDefaultLevel(boundary);
}

void BreakOutLevel::Load(const std::vector<Block> &blocks) {
    mBlocks.clear();
    mBlocks = blocks;
}

void BreakOutLevel::Update(uint32_t deltaTime, Ball &ball) {
    std::vector<Block> collidedBlocks;

    BoundaryEdge edgeToBounceOff;
    Block *blockToBounceOff = nullptr;

    float largestMag = -1.0f;

    for(auto &block : mBlocks) {
        BoundaryEdge edge;

        if(!block.IsDestroyed() && block.HasCollided(ball.GetBoundingRect(), edge)) {
            collidedBlocks.push_back(block);

            float mag = block.GetCollisionOffset(ball.GetBoundingRect()).Mag();

            if(mag > largestMag) {
                edgeToBounceOff = edge;
                blockToBounceOff = &block;
            }
        }
    }

    if(blockToBounceOff != nullptr) {
        blockToBounceOff->Bounce(ball, edgeToBounceOff);
        blockToBounceOff->ReduceHP();
    }

    for(const auto &block : collidedBlocks) {
        BoundaryEdge edge;
        if(block.HasCollided(ball.GetBoundingRect(), edge)) {
            Vec2D p;
            ball.MakeFlushWithEdge(edge, p, true);
        }
    }
}

void BreakOutLevel::Draw(Screen &screen) {
    for(auto &block: mBlocks) {
        if(!block.IsDestroyed()) {
            block.Draw(screen);
        }
    }
}

void BreakOutLevel::CreateDefaultLevel(const AARectangle &boundary) {
    mBlocks.clear();

    const int NUM_BLOCK_ACROSS = ((int)boundary.GetWidth() - (2*(BLOCK_WIDTH))/ BLOCK_WIDTH);
    const int NUM_BLOCK_ROWS = 5;

    float startX = ((int)boundary.GetWidth() - (NUM_BLOCK_ACROSS * (BLOCK_WIDTH+1))) / 2;

    Color colors[NUM_BLOCK_ROWS];
    colors[0] = Color::Red();
    colors[1] = Color::Magenta();
    colors[2] = Color::Yellow();
    colors[3] = Color::Green();
    colors[4] = Color::Cyan();

    for(int r = 0; r < NUM_BLOCK_ROWS; ++r) {
        AARectangle blockRect = AARectangle(Vec2D(startX, BLOCK_HEIGHT * (r+1)), BLOCK_WIDTH, BLOCK_HEIGHT);

        for(int c = 0; c < NUM_BLOCK_ACROSS; ++c) {
            Block b;
            b.Init(blockRect, 1, Color::Black(), colors[r]);
            mBlocks.push_back(b);
            blockRect.MoveBy(Vec2D(BLOCK_WIDTH, 0));
        }
    }
}

bool BreakOutLevel::IsLevelComplete() const {
    for(size_t i = 0; i < mBlocks.size(); ++i) {
        if(!mBlocks[i].IsDestroyed() && mBlocks[i].GetHp() != Block::UNBREAKABLE) {
            return false;
        }
    }

    return true;
}

struct LayoutBlock {
    char symbol = '-';
    int hp = 0;
    Color color = Color::Black();
};

LayoutBlock FindLayoutBlockFromSymbol(const std::vector<LayoutBlock> &blocks, char symbol) {
    for(size_t i = 0; i < blocks.size(); ++i) {
        if(blocks[i].symbol == symbol) {
            return blocks[i];
        }
    }

    return LayoutBlock();
}

std::vector<BreakOutLevel> BreakOutLevel::LoadLevelsFromFile(const std::string &filePath) {
    std::vector<BreakOutLevel> levels;

    std::vector<LayoutBlock> layoutBlocks;

    std::vector<Block> levelBlocks;

    int width = 0;
    int height = 0;

    FileCommandLoader fileLoader;
    Command levelCommand;
    levelCommand.command = "level";
    levelCommand.parseFunc = [&](ParseFuncParams params) {
        if(levels.size() > 0) {
            levels.back().Load(levelBlocks);
        }
        layoutBlocks.clear();
        levelBlocks.clear();
        width = 0;
        height = 0;

        BreakOutLevel level;
        level.Init(AARectangle(Vec2D::Zero, App::Singleton().Width(), App::Singleton().Height()));

        levels.push_back(level);
    };

    fileLoader.AddCommand(levelCommand);
    Command blockCommand;
    blockCommand.command = "block";
    blockCommand.parseFunc = [&](ParseFuncParams params) {
        LayoutBlock lb;

        layoutBlocks.push_back(lb);
    };
    fileLoader.AddCommand(blockCommand);

    Command symbolCommand;
    symbolCommand.command = "symbol";
    symbolCommand.parseFunc = [&](ParseFuncParams params) {
        layoutBlocks.back().symbol = FileCommandLoader::ReadChar(params);
    };

    fileLoader.AddCommand(symbolCommand);

    Command fillColorCommand;
    fillColorCommand.command = "fillcolor";
    fillColorCommand.parseFunc = [&](ParseFuncParams params) {
        layoutBlocks.back().color = FileCommandLoader::ReadColor(params);
    };

    fileLoader.AddCommand(fillColorCommand);

    Command hpCommand;
    hpCommand.command = "hp";
    hpCommand.parseFunc = [&](ParseFuncParams params) {
        layoutBlocks.back().hp = FileCommandLoader::ReadInt(params);
    };

    fileLoader.AddCommand(hpCommand);

    Command widthCommand;
    widthCommand.command = "width";
    widthCommand.parseFunc = [&](ParseFuncParams params) {
        width = FileCommandLoader::ReadInt(params);
    };

    fileLoader.AddCommand(widthCommand);

    Command heightCommand;
    heightCommand.command = "height";
    heightCommand.parseFunc = [&](ParseFuncParams params) {
        height = FileCommandLoader::ReadInt(params);
    };

    fileLoader.AddCommand(heightCommand);

    Command layoutCommand;
    layoutCommand.commandType = COMMAND_MULTI_LINE;
    layoutCommand.command = "layout";
    layoutCommand.parseFunc = [&](ParseFuncParams params) {
        int blockWidth = BLOCK_WIDTH;
        int screenWidth = App::Singleton().Width();

        float startingX = 0;
        AARectangle blockRect(Vec2D(startingX, (params.lineNum+1)*BLOCK_HEIGHT), BLOCK_WIDTH, BLOCK_HEIGHT);

        for(int c = 0; c < params.line.length(); ++c) {
            if(params.line[c] != '-') {
                LayoutBlock layoutBlock = FindLayoutBlockFromSymbol(layoutBlocks, params.line[c]);

                Block b;
                b.Init(blockRect, layoutBlock.hp, Color::Black(), layoutBlock.color);
                levelBlocks.push_back(b);
            }
            blockRect.MoveBy(Vec2D(BLOCK_WIDTH, 0));
        }
    };

    fileLoader.AddCommand(layoutCommand);
    fileLoader.LoadFile(filePath);

    if(levels.size() > 0) {
        levels.back().Load(levelBlocks);
    }

    return  levels;
}