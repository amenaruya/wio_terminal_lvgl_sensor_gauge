#ifndef __LIGHT_GAUGE_APP_HPP__
#define __LIGHT_GAUGE_APP_HPP__

#include "LvglArduinoAbstractLayer.hpp"

class App final: public LAAL<App> {
private:
    /* 画面設定 */
    void                __mFDisplaySetup();

    /* デバイス設定 */
    void                __mFDeviceSetup();
    /* reading light sensor */
    static uint32_t     __mFu32GetLightSensorValue();

    /* gauge */
    static lv_obj_t*    __mpObjectGaugeLight;
    /* gauge配置 */
    void                __mFGaugeSetup();

    /* task object */
    lv_task_t*          __mpTaskUpdateGauge;
    /* task function */
    static void         __mFUpdateGauge(lv_task_t* pTask);
    /* set task */
    void                __mFSetTask();

    /* 画面構成 */
    void                __mFContentsSetup();

    /* constructor */
    App();
    /* destructor */
    ~App();

public:
    /* 初期化 */
    static App*         mFpLaalInitialize(TFT_eSPI* pTft);
};

#endif // __LIGHT_GAUGE_APP_HPP__
