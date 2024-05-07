// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.3
// LVGL version: 8.3.6
// Project name: UI_Design

#ifndef _UI_DESIGN_UI_H
#define _UI_DESIGN_UI_H

#ifdef __cplusplus
extern "C" {
#endif

    #include "lvgl.h"

#include "ui_helpers.h"
#include "components/ui_comp.h"
#include "components/ui_comp_hook.h"
#include "ui_events.h"
// SCREEN: ui_Screen1
void ui_Screen1_screen_init(void);
extern lv_obj_t *ui_Screen1;
void ui_event_Switch1( lv_event_t * e);
extern lv_obj_t *ui_Switch1;
extern lv_obj_t *ui_Label1;
void ui_event_Switch2( lv_event_t * e);
extern lv_obj_t *ui_Switch2;
extern lv_obj_t *ui_Label2;
extern lv_obj_t *ui_Arc1;
void ui_event_Slider1( lv_event_t * e);
extern lv_obj_t *ui_Slider1;
extern lv_obj_t *ui____initial_actions0;

LV_IMG_DECLARE( ui_img_spring2_by_web750eb_png);   // assets/Spring2_by_web750eb.png



void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif