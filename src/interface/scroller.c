#define VGA_WIDTH 80
#define VGA_HEIGHT 25

unsigned int scroll_position = 0;

void scroll_up(void)
{
    if (scroll_position > 0)
    {
        scroll_position--;
        for(int row = 0; row < VGA_HEIGHT; row++)
        {
            for(int col = 0; col < VGA_WIDTH; col++)
            {
                
            }
        }
    }
}

void scroll_down(void)
{
    if (scroll_position > 0)
    {
        scroll_position++;
        for(int row = 0; row < VGA_HEIGHT; row++)
        {
            for(int col = 0; col < VGA_WIDTH; col++)
            {
                
            }
        }
    }
}