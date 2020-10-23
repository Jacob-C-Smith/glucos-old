#include <GlucOS/UI.h>

UIDesktop_t* UICreateDesktop ( )
{
    UIDesktop_t* ret = malloc(sizeof(UIDesktop_t));
    ret->head = (void*) 0;
    return ret;
};
void UIDrawDesktop( UIDesktop_t* desktop )
{
	UIWindow_t* i = desktop->head;

	if (i == 0)
		return;
	
	while (i)
	{
		UIDrawWindow(i);
		i = i->next;
	}
}
void UIDestroyDesktop ( UIDesktop_t* desktop )
{
    UIWindow_t* i = desktop->head;
    while(i)
    {
        UIWindow_t* j = i;
        i = i->next;
        UIDestroyWindow(j);
    }
    free(desktop);
}


UIWindow_t* UICreateWindow( const char* title, u32 x, u32 y, u32 width, u32 height )
{
    UIWindow_t* ret = malloc(sizeof(UIWindow_t));
    
    ret->x         = x;
    ret->y         = y;
    ret->w         = width;
    ret->h         = height;
    ret->title     = title;
    ret->foreColor = 0xFF000000;
    ret->backColor = 0xFFFFFFFF;

    return ret;
}
void UIDrawWindow( UIWindow_t* window )
{
    // Paint the window borders
    {
        VBE_drawLine(window->x            , window->y+5        , window->x            , window->y + window->h, 0x0); // Left window border
        VBE_drawLine(window->x + window->w, window->y+5        , window->x + window->w, window->y + window->h, 0x0); // Right window border
        VBE_drawLine(window->x            , window->y+window->h, window->x+window->w  , window->y + window->h, 0x0); // Bottom window border
    }
    // Paint the inside
    {
        VBE_drawRect(window->x+1, window->y+1, window->h-1,  window->h-1, window->backColor);
    }

    // Paint x o - box
    {
        VBE_drawLine(window->x+window->w-48, window->y   , window->x+window->w-20, window->y,    0x0); // Top 
        VBE_drawLine(window->x+window->w-48, window->y+10, window->x+window->w-20, window->y+10, 0x0); // Bottom
        VBE_drawLine(window->x+window->w-48, window->y   , window->x+window->w-48, window->y+10, 0x0); // Left
        VBE_drawLine(window->x+window->w-20, window->y   , window->x+window->w-20, window->y+10, 0x0); // Right
    }

    size_t aWidth = (window->w - 48 - (strlen(window->title) * 8))/2;                                              // aWidth is half the length of the window minus the length of the XO- box (48px)

    // Paint top window border
    {
        VBE_drawLine(window->x+window->w-20       , window->y+5     , window->x+window->w          , window->y+5 , 0); // Top right window margin
        VBE_drawLine(window->x                    , window->y+5     , window->x+aWidth             , window->y+5 , 0); // Top left window margin
        VBE_drawLine(window->x+window->w-46-aWidth, window->y+5     , window->x+window->w-48       , window->y+5 , 0); // Top center window margin
        VBE_drawLine(window->x+aWidth             , window->y       , window->x+aWidth             , window->y+10, 0); // Window title left detail
        VBE_drawLine(window->x+window->w-46-aWidth, window->y       , window->x+window->w-46-aWidth, window->y+10, 0); // Window title right detail
    }
    
    // Paint the window title
    {
        size_t xm = 0;
        for (size_t i = 0; i < strlen(window->title); i++)
        {
            VBE_putcharat(window->title[i],window->y,window->x+aWidth+xm+3, 0x00000000);
            xm+=8;
        }
        VBE_drawRect(window->x+window->w-47, window->y+1 ,27,9,0xFF0000);
    }
}
void UIDestroyWindow ( UIWindow_t* window )
{
    window->title     = (void*)0;
    window->x         = 0;
    window->y         = 0;
    window->w         = 0;
    window->h         = 0;
    window->foreColor = 0;
    window->backColor = 0;
    window->next      = (void*) 0;
    free(window);
}
void UIAppendWindow( UIDesktop_t* desktop, UIWindow_t* window )
{
	UIWindow_t* i = desktop->head;

	if (i == 0)
	{
		desktop->head = window;
		return;
	}

	while (i->next)
		i = i->next;

	i->next = window;
}

UIButton_t* UICreateButton ( char* ID, char* text, u32 width, u32 height, u32 x, u32 y )
{
    UIButton_t* ret  = malloc(sizeof(UIButton_t));

    ret->ID          = ID;
    
    ret->text        = text;
    ret->width       = width;
    ret->height      = height;
    ret->x           = x;
    ret->y           = y;
    ret->textColor   = 0x00000000;
    ret->backColor   = 0xFFFFFFFF;
    ret->textAlign   = centered;
    ret->borderWidth = 1;
    ret->borderColor = 0x00000000;
    ret->hidden      = false;

    ret->onClick     = (void*)0;
    ret->onHover     = (void*)0;

    return ret;
}
void UIDrawButton ( UIButton_t* button )
{
    VBE_drawHollowRect(button->x-1, button->y-1, button->width+1, button->height+1, button->borderColor);
    VBE_drawRect(button->x, button->y, button->width, button->height, button->backColor);
    size_t xm = 0;
    for (size_t i = 0; i < strlen(button->text); i++)
    {
        VBE_putcharat(button->text[i],button->y,button->x+xm+2, button->textColor);
        xm+=8;
    }
}
void UIDestroyButton ( UIButton_t* button )
{

    button->ID          = (void*)0;

    button->text        = (void*)0;
    button->width       = 0;
    button->height      = 0;
    button->x           = 0;
    button->y           = 0;
    button->textColor   = 0;
    button->backColor   = 0;
    button->textAlign   = 0;
    button->borderWidth = 0;
    button->borderColor = 0;
    button->hidden      = 0;

    button->onClick     = (void*)0;
    button->onHover     = (void*)0;
    free(button);
}

UILabel_t* UICreateLabel ( char* ID, char* text, u32 width, u32 height, u32 x, u32 y )
{
    UILabel_t* ret = malloc(sizeof(UILabel_t));

    ret->ID          = ID;
    
    ret->text        = text;
    ret->width       = width;
    ret->height      = height;
    ret->x           = x;
    ret->y           = y;
    ret->textColor   = 0x00000000;
    ret->textAlign   = centered;
    ret->hidden      = false;

    return ret;
}
void UIDrawLabel ( UILabel_t* label )
{
    size_t xm = 0;
    for (size_t i = 0; i < strlen(label->text); i++)
    {
        VBE_putcharat(label->text[i],label->y,label->x+xm+2, label->textColor);
        xm+=8;
    }
}
void UIDestroyLabel ( UILabel_t* label )
{

    label->ID          = 0;
    
    label->text        = 0;
    label->width       = 0;
    label->height      = 0;
    label->x           = 0;
    label->y           = 0;
    label->textColor   = 0;
    label->textAlign   = 0;
    label->hidden      = 0;

    free(label);
}