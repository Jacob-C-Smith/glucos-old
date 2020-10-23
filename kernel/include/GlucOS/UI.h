#ifndef GLUCOS_UI_H
#define GLUCOS_UI_H

#include <typedef.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <GlucOS/VBE.h>

struct UIWindow_s
{
    const char* title;
    u32 x;
    u32 y;
    u32 w;
    u32 h;
    u32 foreColor;
    u32 backColor;
    struct UIWindow_s* next;
};
typedef struct UIWindow_s UIWindow_t;

struct UIDesktop_s
{
    UIWindow_t* head;
};
typedef struct UIDesktop_s UIDesktop_t;

struct UIButton_s
{
    // ID
    char* ID;

    // Renderer
    char* text;
    u32   width;
    u32   height;
    u32   x;
    u32   y;
    u32   textColor;
    u32   backColor;
    u8    textAlign;
    u32   borderWidth;
    u32   borderColor;
    bool  hidden;

    // Callbacks
    void* onClick;
    void* onHover;
};
typedef struct UIButton_s UIButton_t;

struct UILabel_s
{
    // ID
    char* ID;

    // Renderer
    char* text;
    u32   width;
    u32   height;
    u32   x;
    u32   y;
    u32   textColor;
    u8    textAlign;
    bool  hidden;
};
typedef struct UILabel_s UILabel_t;

enum textAlign_e {
    left     = 0,
    centered = 1,
    right    = 2,
};

// Desktop functions
UIDesktop_t* UICreateDesktop  ( );
void         UIDrawDesktop    ( UIDesktop_t* desktop );
void         UIDestroyDesktop ( UIDesktop_t* desktop );
// Window functions
UIWindow_t*  UICreateWindow   ( const char* title, u32 x, u32 y, u32 width, u32 height );
void         UIDrawWindow     ( UIWindow_t* window );
void         UIAppendWindow   ( UIDesktop_t* desktop, UIWindow_t* window );
void         UIDestroyWindow  ( UIWindow_t* window );

// Button functions
UIButton_t*  UICreateButton   ( char* ID, char* text, u32 width, u32 height, u32 x, u32 y );
void         UIDrawButton     ( UIButton_t* button );
void         UIDestroyButton  ( UIButton_t* button );

// Label functions
UILabel_t* UICreateLabel      ( char* ID, char* text, u32 width, u32 height, u32 x, u32 y );
void       UIDrawLabel        ( UILabel_t* label );
void       UIDestroyLabel     ( UILabel_t* label );


#endif