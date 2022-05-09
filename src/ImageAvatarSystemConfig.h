#ifndef _IMAGEAVATAR_SYSTEM_CONFIG_H_
#define _IMAGEAVATAR_SYSTEM_CONFIG_H_

#include <ArduinoJson.h> // https://github.com/bblanchon/ArduinoJson
#include <M5Unified.h>

#define MAX_AVATAR_NUM 8  // 最大8個のAvatar

class ImageAvatarSystemConfig {
    protected:
        uint8_t _volume;                                       // Initial volume
        uint8_t _lcd_brightness;                               // brightness of lcd
        uint8_t _avatar_count;                                 // avatar count
        String _avatar_jsonfiles[MAX_AVATAR_NUM];              // json filename
        String _bluetooth_device_name;                         // bluetooth_device_name
        String _servo_jsonfile;                                // servo json filename
        bool _servo_random_mode;                               // servo random mode flag
        void setSystemConfig(DynamicJsonDocument doc);
    public:
        ImageAvatarSystemConfig();
        ~ImageAvatarSystemConfig();
        void loadConfig(fs::FS& fs, const char *json_filename);

        void printAllParameters();
        uint8_t getVolume() { return _volume; }
        uint8_t getLcdBrightness() { return _lcd_brightness; };
        uint8_t getAvatarMaxCount() { return _avatar_count; }
        String getBluetoothDeviceName() { return _bluetooth_device_name; }
        String getAvatarJsonFilename(uint8_t avatar_no) { return _avatar_jsonfiles[avatar_no]; }
        String getServoJsonFilename() { return _servo_jsonfile; }
        bool getServoRandomMode() { return _servo_random_mode; }
};


#endif // _IMAGEAVATAR_SERVO_CONFIG_
