#include <GlucOS/UI.h>

// Window functions
UIWindow_t* UICreateWindow( const char* title, long int x, long int y, long int width, long int height )
{
    UIWindow_t* ret = malloc(sizeof(UIWindow_t));
    
    ret->x         = x;
    ret->y         = y;
    ret->w         = width;
    ret->h         = height;
    ret->title     = title;
    ret->foreColor = Black;
    ret->backColor = White;

    return ret;
}
void UIDrawWindow( UIWindow_t* window )
{
    // Paint the window borders
    {
        VBE_drawLine(window->x            , window->y+5        , window->x            , window->y + window->h, window->foreColor); // Left window border
        VBE_drawLine(window->x + window->w, window->y+5        , window->x + window->w, window->y + window->h, window->foreColor); // Right window border
        VBE_drawLine(window->x            , window->y+window->h, window->x+window->w  , window->y + window->h, window->foreColor); // Bottom window border
    }
    // Paint the inside
    {
        VBE_drawRect(window->x+1, window->y+1, window->h-1,  window->h-1, window->backColor);
    }

    // Paint x o - box
    {
        VBE_drawLine(window->x+window->w-48, window->y   , window->x+window->w-20, window->y,    window->foreColor); // Top 
        VBE_drawLine(window->x+window->w-48, window->y+10, window->x+window->w-20, window->y+10, window->foreColor); // Bottom
        VBE_drawLine(window->x+window->w-48, window->y   , window->x+window->w-48, window->y+10, window->foreColor); // Left
        VBE_drawLine(window->x+window->w-20, window->y   , window->x+window->w-20, window->y+10, window->foreColor); // Right
    }

    size_t aWidth = (window->w - 48 - (strlen(window->title) * 8))/2;                                              // aWidth is half the length of the window minus the length of the XO- box (48px)

    // Paint top window border
    {
        VBE_drawLine(window->x+window->w-20       , window->y+5     , window->x+window->w          , window->y+5 , window->foreColor); // Top right window margin
        VBE_drawLine(window->x                    , window->y+5     , window->x+aWidth             , window->y+5 , window->foreColor); // Top left window margin
        VBE_drawLine(window->x+window->w-45-aWidth, window->y+5     , window->x+window->w-48       , window->y+5 , window->foreColor); // Top center window margin
        VBE_drawLine(window->x+aWidth             , window->y       , window->x+aWidth             , window->y+10, window->foreColor); // Window title left detail
        VBE_drawLine(window->x+window->w-45-aWidth, window->y       , window->x+window->w-45-aWidth, window->y+10, window->foreColor); // Window title right detail
    }
    
    // Paint the window title
    {
        size_t xm = 0;
        for (size_t i = 0; i < strlen(window->title); i++)
        {
            VBE_putcharat(window->title[i],window->y,window->x+aWidth+xm+3, window->foreColor);
            xm+=8;
        }
        VBE_drawRect(window->x+window->w-47, window->y+1 ,27,9,Red);
    }
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


// Desktop functions
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

// Button functions
UIButton_t* UICreateButton ( char* ID, char* text, long int x, long int y, long int width, long int height)
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

    VBE_writestringat(button->text, button->x+2, button->y+1);
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

// TextInput functions
UITextInput_t* UICreateTextInput ( char* ID, char* placeholder, long int x, long int y, long int width, long int height )
{
    UITextInput_t* ret = malloc(sizeof(UITextInput_t));
    // ID
    ret->ID          = ID;

    // Renderer
    ret->placeholder = placeholder;
    ret->text        = calloc(128,1);
    ret->width       = width;
    ret->height      = height;
    ret->x           = x;
    ret->y           = y;
    ret->textColor   = Black;
    ret->backColor   = White;
    ret->hidden      = false;

    return ret;
}
void UIDrawTextInput ( UITextInput_t* textInput )
{
    VBE_drawHollowRect(textInput->x, textInput->y, textInput->width, textInput->height, Gray);
    VBE_drawHollowRect(textInput->x+1, textInput->y+1, textInput->width-2, textInput->height-2, Gray);
    if(textInput->text[0] == '\0')
    {
        VBE_writestringat(textInput->placeholder, textInput->x+4, textInput->y+4);
    }else
    {
        VBE_writestringat(textInput->text, textInput->x+4, textInput->y+4);
    }
}
void UIDestroyTextInput ( UITextInput_t* textInput )
{
    // ID
    textInput->ID          = 0;
    // Renderer
    textInput->placeholder = 0;
    textInput->text        = 0;
    textInput->width       = 0;
    textInput->height      = 0;
    textInput->x           = 0;
    textInput->y           = 0;
    textInput->textColor   = 0;
    textInput->backColor   = 0;
    textInput->hidden      = 0;
    // Callbacks
    textInput->onChange    = 0;
    textInput->onInput     = 0;
}

// Label functions
UILabel_t* UICreateLabel ( char* ID, char* text, long int x, long int y)
{
    UILabel_t* ret = malloc(sizeof(UILabel_t));

    ret->ID          = ID;
    
    ret->text        = text;
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
// Dropdown functions
UIDropdown_t* UICreateDropdown ( char* ID, char** options, long int x, long int y, long int width, long int height )
{
    UIDropdown_t* ret = malloc(sizeof(UIDropdown_t));

    ret->ID          = ID;
    
    ret->collapsed   = true;
    ret->options     = options;
    ret->index       = -1;
    ret->width       = width;
    ret->height      = height;
    ret->x           = x;
    ret->y           = y;
    ret->textColor   = Black;
    ret->borderColor = Black;
    ret->textAlign   = centered;
    ret->hidden      = false;

    return ret;
}
void UIDrawDropdown ( UIDropdown_t* dropdown )
{
    VBE_drawHollowRect(dropdown->x, dropdown->y, dropdown->width, dropdown->height,dropdown->textColor);    
    size_t xm = 0;
    if(dropdown->index >= 0 )
    {
        for (size_t i = 0; i < strlen(dropdown->options[dropdown->index]); i++)
        {
            VBE_putcharat(dropdown->options[dropdown->index][i],dropdown->y+1,dropdown->x+xm+2, dropdown->textColor);
            xm+=8;
        }
    }
    VBE_drawLine(dropdown->x + dropdown->width - 11, dropdown->y + 2,dropdown->x +  dropdown->width - 11, dropdown->y + dropdown->height - 2, dropdown->borderColor);
    if(dropdown->collapsed == true)
    {
        // Draw the ► symbol
        VBE_drawLine(dropdown->x + dropdown->width - 7, dropdown->y + 2,dropdown->x + dropdown->width - 7, dropdown->y + dropdown->height - 2, dropdown->borderColor);
        VBE_drawLine(dropdown->x + dropdown->width - 6, dropdown->y + 3,dropdown->x + dropdown->width - 6, dropdown->y + dropdown->height - 3, dropdown->borderColor);
        VBE_drawLine(dropdown->x + dropdown->width - 5, dropdown->y + 4,dropdown->x + dropdown->width - 5, dropdown->y + dropdown->height - 4, dropdown->borderColor);
        VBE_drawLine(dropdown->x + dropdown->width - 4, dropdown->y + 5,dropdown->x + dropdown->width - 4, dropdown->y + dropdown->height - 5, dropdown->borderColor);
    }else
    {
        // Draw the holow ▼ symbol
        VBE_drawLine(dropdown->x + dropdown->width - 9, dropdown->y + 5,dropdown->x + dropdown->width - 2, dropdown->y + 5, dropdown->borderColor);
        VBE_drawLine(dropdown->x + dropdown->width - 9, dropdown->y + 5,dropdown->x + dropdown->width - 6, dropdown->y + 8, dropdown->borderColor);
        VBE_drawLine(dropdown->x + dropdown->width - 2, dropdown->y + 5,dropdown->x + dropdown->width - 5, dropdown->y + 8, dropdown->borderColor);

        // Draw the shadow to the left of the dropdown
        VBE_drawLine(dropdown->x + dropdown->width + 1, dropdown->y + 1, dropdown->x + dropdown->width + 1, dropdown->y + dropdown->height, Gray);

        u32 optcount = 0;
        while (dropdown->options[optcount++]);
        optcount--;

        for(u32 i = 0; i < optcount; i++)
        {
            VBE_writestringat(dropdown->options[i], dropdown->x+4, dropdown->y+(12*(i+1))+1);
            VBE_drawLine(dropdown->x+1, dropdown->y+dropdown->height+1, dropdown->x+1, dropdown->y+dropdown->height+(12*(i+1)), Gray);
            VBE_drawLine(dropdown->x+1, dropdown->y+dropdown->height+(12*(i+1)), dropdown->x+dropdown->width+1, dropdown->y+dropdown->height+(12*(i+1)), Gray);  
            VBE_drawLine(dropdown->x+dropdown->width+1, dropdown->y+dropdown->height+(12*(i+1)), dropdown->x+dropdown->width+1, dropdown->y+(12*(i+1)), Gray);  
        }
    }    
}
void UIDestroyDropdown ( UIDropdown_t* dropdown )
{
    dropdown->ID          = 0;
    
    // TODO: Deallocate double pointer.
    dropdown->options     = 0;
    dropdown->index       = 0;
    dropdown->width       = 0;
    dropdown->height      = 0;
    dropdown->x           = 0;
    dropdown->y           = 0;
    dropdown->textColor   = 0;
    dropdown->textAlign   = 0;
    dropdown->hidden      = 0;

    free(dropdown);
}

// RadioButton functions
UIRadioButton_t* UICreateRadioButton  ( char* ID, char* groupID, long int x, long int y );
void             UIDrawRadioButton    ( UIRadioButton_t* radioButton );
void             UIDestroyRadioButton ( UIRadioButton_t* radioButton );

// CheckBox functions
UICheckbox_t* UICreateCheckbox ( char* ID, char* groupID, long int x, long int y )
{
    UICheckbox_t* ret = malloc(sizeof(UICheckbox_t));
    ret->ID       = ID;
    ret->groupID  = groupID;
    ret->x        = x;
    ret->y        = y;
    ret->hidden   = false;
    ret->checked  = false;

    return ret;
}
void UIDrawCheckbox ( UICheckbox_t* checkbox )
{
    VBE_drawHollowRect(checkbox->x, checkbox->y,11,11,Black);
    if(checkbox->checked)
    {
        VBE_putcharat(128, checkbox->y+1, checkbox->x+2, Black);
    }
}
void UIDestroyCheckbox ( UICheckbox_t* checkbox )
{

}

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
