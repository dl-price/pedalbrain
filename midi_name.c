
#ifdef ARDUINO

#include <usb_names.h>

#define MIDI_NAME   {'P','B','r','a','i','n'}
#define MIDI_NAME_LEN  6

// Do not change this part.  This exact format is required by USB.

struct usb_string_descriptor_struct usb_string_product_name = {
    2 + MIDI_NAME_LEN * 2,
    3,
    MIDI_NAME
};
#endif
