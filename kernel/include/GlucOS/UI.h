#ifndef GLUCOS_UI_H
#define GLUCOS_UI_H

#include <typedef.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <GlucOS/VBE.h>
#include <GlucOS/Color.h>

#define UI_AUTO -1

struct UIWindow_s
{
    const char*        title;
    long int           x;
    long int           y;
    long int           w;
    long int           h;
    u32                foreColor;
    u32                backColor;
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
    char*    ID;

    // Renderer
    char*    text;
    long int width;
    long int height;
    long int x;
    long int y;
    long int textColor;
    long int backColor;
    u8       textAlign;
    long int borderWidth;
    u32      borderColor;
    bool     hidden;

    // Callbacks
    void*    onClick;
    void*    onHover;
};
typedef struct UIButton_s UIButton_t;

struct UITextInput_s
{
    // ID
    char*    ID;

    // Renderer
    char*    placeholder;
    char*    text;
    long int width;
    long int height;
    long int x;
    long int y;
    long int textColor;
    long int backColor;
    bool     hidden;

    // Callbacks
    void*    onChange;
    void*    onInput;
};
typedef struct UITextInput_s UITextInput_t;

struct UILabel_s
{
    // ID
    char*    ID;

    // Renderer
    char*    text;
    long int width;
    long int height;
    long int x;
    long int y; 
    u32      textColor;
    u8       textAlign;
    bool     hidden;

    // Callbacks
    void*    onClick;
};
typedef struct UILabel_s UILabel_t;

struct UIDropdown_s
{
    // ID
    char*    ID;

    // Renderer
    char**   options;
    long int index;
    long int width;
    long int height;
    long int x;
    long int y;
    long int textColor;
    long int borderColor;
    u8       textAlign;
    bool     collapsed;
    bool     hidden;

    // Callbacks
    void*    onChange;
};
typedef struct UIDropdown_s UIDropdown_t;

struct UIRadioButton_s
{
    // ID
    char*    ID;
    char*    groupID;

    // Renderer
    long int x;
    long int y;
    bool     hidden;
    bool     checked;

    // Callbacks
    void*    onChange;
};
typedef struct UIRadioButton_s UIRadioButton_t;

struct UICheckbox_s
{
    // ID
    char*    ID;
    char*    groupID;

    // Renderer
    long int x;
    long int y;
    bool     hidden;
    bool     checked;

    // Callbacks
    void*    onChange;
};
typedef struct UICheckbox_s UICheckbox_t;

struct UIImage_s
{
    // ID
    char* ID;
};
typedef struct UIImage_s UIImage_t;

struct UICanvas_s
{
    // ID
    char* ID;
};
typedef struct UICanvas_s UICanvas_t;

struct UITextArea_s
{
    // ID
    char* ID;
};
typedef struct UITextArea_s UITextArea_t;

struct UIChart_s
{
    // ID
    char* ID;
};
typedef struct UIChart_s UIChart_t;

struct UISlider_s
{
    // ID
    char* ID;
};
typedef struct UISlider_s UISlider_t;

enum textAlign_e {
    left     = 0,
    centered = 1,
    right    = 2,
};

// Window functions
UIWindow_t*    UICreateWindow         ( const char* title, long int x, long int y, long int width, long int height );
void           UIDrawWindow           ( UIWindow_t* window );
void           UIAppendWindow         ( UIDesktop_t* desktop, UIWindow_t* window );
void           UIDestroyWindow        ( UIWindow_t* window );

// Desktop functions
UIDesktop_t*   UICreateDesktop        ( );
void           UIDrawDesktop          ( UIDesktop_t* desktop );
void           UIDestroyDesktop       ( UIDesktop_t* desktop );

// Button functions
UIButton_t*    UICreateButton         ( char* ID, char* text, long int x, long int y, long int width, long int height );
void           UIDrawButton           ( UIButton_t* button );
void           UIDestroyButton        ( UIButton_t* button );

// TextInput functions
UITextInput_t*   UICreateTextInput    ( char* ID, char* placeholder, long int x, long int y, long int width, long int height );
void             UIDrawTextInput      ( UITextInput_t* textInput );
void             UIDestroyTextInput   ( UITextInput_t* textInput );

// Label functions
UILabel_t*       UICreateLabel        ( char* ID, char* text, long int x, long int y);
void             UIDrawLabel          ( UILabel_t* label );
void             UIDestroyLabel       ( UILabel_t* label );

// Dropdown functions
UIDropdown_t*    UICreateDropdown     ( char* ID, char** options, long int x, long int y, long int width, long int height );
void             UIDrawDropdown       ( UIDropdown_t* dropdown );
void             UIDestroyDropdown    ( UIDropdown_t* dropdown );

// RadioButton functions
UIRadioButton_t* UICreateRadioButton  ( char* ID, char* groupID, long int x, long int y );
void             UIDrawRadioButton    ( UIRadioButton_t* radioButton );
void             UIDestroyRadioButton ( UIRadioButton_t* radioButton );

// CheckBox functions
UICheckbox_t*    UICreateCheckbox     ( char* ID, char* groupID, long int x, long int y );
void             UIDrawCheckbox       ( UICheckbox_t* checkbox );
void             UIDestroyCheckbox    ( UICheckbox_t* checkbox );

// Image functions
UIImage_t*       UICreateImage        ( char* ID, long int x, long int y, long int width, long int height );
void             UIDrawImage          ( UIImage_t* image );
void             UIDestroyImage       ( UIImage_t* image );

// Canvas functions
UICanvas_t*      UICreateCanvas       ( char* ID, long int x, long int y, long int width, long int height );
void             UIDrawCanvas         ( UICanvas_t* canvas );
void             UIDestroyCanvas      ( UICanvas_t* canvas );

// TextArea functions
UITextArea_t*    UICreateTextArea     ();
void             UIDrawTextArea       ( UITextArea_t* textArea );
void             UIDestroyTextArea    ( UITextArea_t* textArea );

// Chart functions
UIChart_t*       UICreateChart        ();
void             UIDrawChart          ( UIChart_t* chart );
void             UIDestroyChart       ( UIChart_t* chart );

// Slider functions
UISlider_t*      UICreateSlider       ( char* ID, long int x, long int y, long int width, long int val, long int minVal, long int maxVal, long int step);
void             UIDrawSlider         ( UISlider_t* slider );
void             UIDestroySlider      ( UISlider_t* slider );

#endif