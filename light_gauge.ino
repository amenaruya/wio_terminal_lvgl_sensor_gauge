#include <TFT_eSPI.h>
#include <lvgl.h>

#include "LightGaugeApp.hpp"

/* TFT LCD */
static TFT_eSPI TFT;

/* App */
App* pApp;

void setup() {
    pApp = App::mFpLaalInitialize(&TFT);
    pApp -> mFSetup();
}

void loop() {
    pApp -> mFOperateGraphic();
}
