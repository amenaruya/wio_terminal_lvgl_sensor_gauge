#include "LightGaugeApp.hpp"

/* 針の数 */
constexpr uint16_t      __NEEDLE_COUNT__ = 1;
/* 針の色 */
constexpr lv_color_t    __NEEDLE_COLOR__[__NEEDLE_COUNT__] = {LV_COLOR_SILVER};

/* create gauge */
lv_obj_t*               App::__mpObjectGaugeLight = nullptr;
/*
C:\Users\⋯\AppData\Local\arduino\sketches\DC395E2A554803459821E977C51E7A61\sketch\LightGaugeApp.cpp.o: In function `App::__mFUpdateGauge(_lv_task_t*)':
C:\⋯\light_gauge/LightGaugeApp.cpp:64: undefined reference to `App::__mpObjectGaugeLight'
C:\Users\⋯\AppData\Local\arduino\sketches\DC395E2A554803459821E977C51E7A61\sketch\LightGaugeApp.cpp.o: In function `lv_gauge_set_range':
c:\⋯\libraries\Seeed_Arduino_LvGL\src/src/lv_widgets/lv_gauge.h:105: undefined reference to `App::__mpObjectGaugeLight'
collect2.exe: error: ld returned 1 exit status
*/

App* App::mFpLaalInitialize(TFT_eSPI* pTft) {
    /* 未定ならば初期化 */
    if (LAAL<App>::__smpLaalSingleton == nullptr) {
        /* static member variableの初期化 */
        LAAL<App>::__mpTft = pTft;
        /* 子クラスの初期化 */
        LAAL<App>::__smpLaalSingleton = new App();
    }
    /* 既初期化の場合でも既存インスタンスへのポインターが返却される */
    return LAAL<App>::__smpLaalSingleton;
}

App::App() {
    LAAL<App>::__mFNew();
}
App::~App() {}

void App::__mFDisplaySetup() {
    LAAL<App>::__mFDisplaySetup();
}

void App::__mFDeviceSetup() {
    /* 入力の設定 */
    /*
    lv_indev_drv_init(&(LAAL<App>::__mInputDeviceDriverEncoder));
    (LAAL<App>::__mInputDeviceDriverEncoder).type = LV_INDEV_TYPE_ENCODER;
    (LAAL<App>::__mInputDeviceDriverEncoder).read_cb = App::__mFbReadEncoder;
    LAAL<App>::__mpInputDeviceEncoder = lv_indev_drv_register(&(LAAL<App>::__mInputDeviceDriverEncoder));
    */

    /* enable light sensor */
    pinMode(WIO_LIGHT, INPUT);
}

uint32_t App::__mFu32GetLightSensorValue() {
    return analogRead(WIO_LIGHT);
}

void App::__mFGaugeSetup() {
    /* create gauge */
    this -> __mpObjectGaugeLight = lv_gauge_create(lv_scr_act(), NULL);
    /* set needle count 1 */
    lv_gauge_set_needle_count(this -> __mpObjectGaugeLight, __NEEDLE_COUNT__, __NEEDLE_COLOR__);
    /* set gauge size */
    lv_obj_set_size(this -> __mpObjectGaugeLight, 200, 200);
    /* set align center */
    lv_obj_align(this -> __mpObjectGaugeLight, NULL, LV_ALIGN_CENTER, 0, 0);
    /* set gauge range */
    lv_gauge_set_range(this -> __mpObjectGaugeLight, 0, 1100);
}

void App::__mFUpdateGauge(lv_task_t* pTask) {
    (void) pTask;
    lv_gauge_set_value(App::__mpObjectGaugeLight, 0, (App::__mFu32GetLightSensorValue)());
}

void App::__mFSetTask() {
    this -> __mpTaskUpdateGauge = lv_task_create(App::__mFUpdateGauge, 50, LV_TASK_PRIO_HIGHEST, NULL);
}

void App::__mFContentsSetup() {
    (this -> __mFGaugeSetup)();
    (this -> __mFSetTask)();
}
