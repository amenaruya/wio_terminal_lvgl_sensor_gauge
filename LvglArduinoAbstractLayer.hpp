#ifndef __LVGL_ARDUINO_ABSTRACT_LAYER_HPP__
#define __LVGL_ARDUINO_ABSTRACT_LAYER_HPP__

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <lvgl.h>

template<class T>
class LAAL {
private:
    /* delete copy constructor */
    LAAL(const LAAL&) = delete;
    /* delete copy operator */
    LAAL& operator=(const LAAL&) = delete;

protected:
    /* singleton */
    static T*           __smpLaalSingleton;

    /* TFT LCD */
    static TFT_eSPI*    __mpTft;

    /* tick (1～10) */
    uint32_t            __mu32TickPeriod;

    /* ディスプレイ */

    /* display buffer */
    lv_disp_buf_t       __smDisplayBuffer;
    /* main color buffer */
    lv_color_t          __smColorBufferMain[LV_HOR_RES_MAX * 10];
    /* sub color buffer */
    lv_color_t          __smColorBufferSub[LV_HOR_RES_MAX * 10];
    /* display driver */
    lv_disp_drv_t       __mDisplayDriver;
    /* display */
    lv_disp_t*          __mpDisplay;
    /* 画面初期化 */
    static void         __mFDisplayFlush(
        lv_disp_drv_t*      pDisplayDriver,
        const lv_area_t*    pArea,
        lv_color_t*         pColor
    );
    /* 画面設定 */
    virtual void        __mFDisplaySetup();

    /* 入力デバイス(encode) */

    /* input device driver */
    lv_indev_drv_t      __mInputDeviceDriverEncoder;
    /* input device */
    lv_indev_t*         __mpInputDeviceEncoder;
    /* Reading encoder callback */
    static bool         __mFbReadEncoder(
        lv_indev_drv_t*     pInputDeviceDriver,
        lv_indev_data_t*    pInputDevicesData
    );
    /* デバイス設定 */
    virtual void        __mFDeviceSetup();

    /* 画面要素 */

    /* widget */
    /*
    example:
    lv_obj_t*           __mpObject;
    void                __mFObjectEventhandler(
        lv_obj_t*           pObject,
        lv_event_t          event
    ) = 0;
    */

    /* group */
    /*
    example:
    lv_group_t*         __mpGroup;
    void                __mFGroupSetup();
    */

    /* 画面構成 */
    virtual void        __mFContentsSetup() = 0;

    /* constructor */
    void                __mFNew();
    LAAL() = default;
    /* destructor */
    virtual ~LAAL() = default;

public:
    /* 設定 */
    void                mFSetup();
    /* 画面実行 */
    void                mFOperateGraphic();
};

#include "LvglArduinoAbstractLayer.ipp"

#endif // __LVGL_ARDUINO_ABSTRACT_LAYER_HPP__
