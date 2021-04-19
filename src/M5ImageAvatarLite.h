#ifndef _IMAGEAVATARLITE_H_
#define _IMAGEAVATARLITE_H_

#include <SD.h>
#include <SPIFFS.h>
#include <lgfx.h>
#include "ImageAvatarConfig.h"

class ImageAvatarLite
{
    private:
        LGFX *_gfx;
        LGFX_Sprite _head_sp;     // 頭（背景）用スプライト
        LGFX_Sprite _eye_op_sp;   // 開いた右目のスプライト
        LGFX_Sprite _eye_cl_sp;   // 閉じた右目のスプライト
        LGFX_Sprite _mouth_op_sp; // 開いた口のスプライト
        LGFX_Sprite _mouth_cl_sp; // 閉じた口のスプライト
        LGFX_Sprite _mouth_sp;    // 口描画用スプライト
        LGFX_Sprite _eye_l_sp;    // 左目描画用スプライト
        LGFX_Sprite _eye_r_sp;    // 右目描画用スプライト
        LGFX_Sprite _lcd_sp;      // LCDに最終的に描画する直前のスプライト
        move_param_s _mv;

        bool _is_change;
        uint8_t _expression;    // 感情
        uint32_t _draw_time;

        fs::FS *_fs;
        const char* _filename;
        ImageAvatarConfig _config;
        spcommon_s _spcommon;

        lgfx::rgb565_t _tp_color; // 透明色

        void initSprites(bool is_change);
        void deleteSprites();
        void loadConfig(fs::FS& fs, const char* filename);
        void execDraw();

        void drawHead();
        void drawEyes();
        void drawMouth();
        lgfx::rgb565_t convertColorCode(uint32_t code);

    public:
        ImageAvatarLite(void);
        ~ImageAvatarLite(void);

        void createSprite();
        void init(LGFX *gfx, fs::FS& fs, const char* filename, bool is_change, uint8_t expression = 0);
        void drawAll();
        void setMoveParameter(move_param_s mv);
        void setExpression(uint8_t expression);
        void setBreath(float f);
        void setBlink(float ratio);
        void setBlink(float ratio, bool isRight);
        void setAngle(float angle);
        void setMouthOpen(float ratio);
        
        float getMouthOpen();
        move_param_s getMoveParameter();

        void readTest();
        void drawTest();
};

#endif // _IMAGEAVATARLITE_H_