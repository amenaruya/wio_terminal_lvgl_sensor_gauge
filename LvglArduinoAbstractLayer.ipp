template<class T>
T* LAAL<T>::__smpLaalSingleton = nullptr;
template<class T>
TFT_eSPI* LAAL<T>::__mpTft = nullptr;

template<class T>
void LAAL<T>::__mFNew() {
    /* lvglの初期化 */
    lv_init();

    /* TFTの初期設定 */
    (this -> __mpTft) -> begin();
    (this -> __mpTft) -> setRotation(3);
}

template<class T>
void LAAL<T>::mFSetup() {
    /* 画面設定 */
    (this -> __mFDisplaySetup)();
    /* 入力設定 */
    (this -> __mFDeviceSetup)();
    /* 画面作成 */
    (this -> __mFContentsSetup)();
}

template<class T>
void LAAL<T>::__mFDisplayFlush(
    lv_disp_drv_t*      pDisplayDriver,
    const lv_area_t*    pArea,
    lv_color_t*         pColor
) {
    const uint32_t w = pArea -> x2 - pArea -> x1 + 1;
    const uint32_t h = pArea -> y2 - pArea -> y1 + 1;

    LAAL<T>::__mpTft -> startWrite();
    LAAL<T>::__mpTft -> setAddrWindow(pArea -> x1, pArea -> y1, w, h);
    LAAL<T>::__mpTft -> pushColors(&pColor -> full, w * h, true);
    LAAL<T>::__mpTft -> endWrite();

    lv_disp_flush_ready(pDisplayDriver);
}

template<class T>
void LAAL<T>::mFOperateGraphic() {
    while (1) {
        /* operate tasks */
        this -> __mu32TickPeriod = lv_task_handler();
        /* delay */
        delay(this -> __mu32TickPeriod);
        /* tell lvgl system elapsed time */
        lv_tick_inc(this -> __mu32TickPeriod);
    }
}

template<class T>
void LAAL<T>::__mFDisplaySetup() {
    /* 画面表示用bufferそのものの初期化 */
    lv_disp_buf_init(
        &(this -> __smDisplayBuffer),
        this -> __smColorBufferMain,
        this -> __smColorBufferSub,
        LV_HOR_RES_MAX * 10
    );

    /* 画面制御設定 */
    lv_disp_drv_init(&(this -> __mDisplayDriver));
    (this -> __mDisplayDriver).ver_res = LV_VER_RES_MAX;
    (this -> __mDisplayDriver).flush_cb = this -> __mFDisplayFlush;
    (this -> __mDisplayDriver).buffer = &(this -> __smDisplayBuffer);
    this -> __mpDisplay = lv_disp_drv_register(&(this -> __mDisplayDriver));
}

template<class T>
bool LAAL<T>::__mFbReadEncoder(
    lv_indev_drv_t*     pInputDeviceDriver,
    lv_indev_data_t*    pInputDevicesData
) {
    (void) pInputDeviceDriver;
    (void) pInputDevicesData;
    return false;
}

template<class T>
void LAAL<T>::__mFDeviceSetup() {
    /* 入力の設定 */
    lv_indev_drv_init(&(this -> __mInputDeviceDriverEncoder));
    (this -> __mInputDeviceDriverEncoder).type = LV_INDEV_TYPE_ENCODER;
    (this -> __mInputDeviceDriverEncoder).read_cb = this -> __mFbReadEncoder;
    this -> __mpInputDeviceEncoder = lv_indev_drv_register(&(this -> __mInputDeviceDriverEncoder));
}
