
// Copyright 2007, Jesper Thomschutz <jesperht@yahoo.com>
// Licensed under GPLv2

#include <stdio.h>
#include <usb.h>
#include <stdint.h>
#include <errno.h>
 static unsigned char keycode[256] = {
   ' ',' ',' ',' ','a','b','c','d','e','f','g','h','i','j','k','l',
   'm','n','o','p','q','r','s','t','u','v','w','x','y','z','1','2',
   '3','4','5','6','7','8','9','0',' ',' ',' ',' ',' ',' ',' ',' ',
   ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
   ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
   ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
   ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
   ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
   ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
   ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
   ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
   ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
   ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
   ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
   ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
   ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
 };

static struct usb_device *findKeyboard(uint16_t vendor, uint16_t product)
{
  struct usb_bus *bus;
  struct usb_device *dev;
  struct usb_bus *busses;

  usb_init();
  usb_find_busses();
  usb_find_devices();
  busses = usb_get_busses();

  for (bus = busses; bus; bus = bus->next)
    for (dev = bus->devices; dev; dev = dev->next)
      if ((dev->descriptor.idVendor == vendor) && (dev->descriptor.idProduct == product))
        return dev;

  return NULL;
}

 void
 print_input(unsigned char *buf, uint16_t size)
 {
         int i;

         if (size < 3) return;
         if (buf[2] == 0x01) return;

         printf("INPUT: ");
         for (i=2; i<size; i++) {
                 if (buf[i])
                         printf("\"%c\"(0x%02x) ", keycode[buf[i]], buf[i]);
         }

         printf("%s%s\n",
                (buf[0] & 0x01) ? "[ctrl]":"",
                (buf[0] & 0x02) ? "[shift]":""
               );
 }

int
 usb_keyboard_test(struct usb_device *dev)
 {
         usb_dev_handle *handle;
         struct usb_config_descriptor *config = &dev->config[0];
         struct usb_interface *interface = &config->interface[0];
         struct usb_interface_descriptor *altsetting = &interface->altsetting[0];
         struct usb_endpoint_descriptor *endpoint = &altsetting->endpoint[0];
         uint8_t ep = endpoint->bEndpointAddress;
	 unsigned char buf1[256];
         unsigned char buf[256];
         ssize_t read_size;
         int ignore = 1;
	 int i = 0;
         handle = usb_open(dev);
         usb_get_string_simple(handle, dev->descriptor.iProduct,
                               (char *)buf, sizeof(buf));

         printf("USB-DEV: 0x%04x/0x%04x \"%s\"\n",
                dev->descriptor.idVendor, dev->descriptor.idProduct, buf);

         if (usb_set_configuration(handle, config->bConfigurationValue) < 0) {
                 if (usb_detach_kernel_driver_np(handle,altsetting->bInterfaceNumber) < 0) {
                         printf("usb_set_configuration() error.\n");
                         usb_close(handle);
                         return -1;
                 }
         }

         usb_claim_interface(handle, altsetting->bInterfaceNumber);

         while (1) {
                 read_size = usb_interrupt_read(handle, ep, (char *)buf,
                                                endpoint->wMaxPacketSize, 0);
                 if (read_size < 0) {
                         if (read_size == -ETIMEDOUT)
                                 printf("read timeout.\n");
                         else
                                 printf("read error: %d\n", read_size);
                 }

                 if (!ignore || buf[2])
                         print_input(buf, endpoint->wMaxPacketSize);

                 if (buf[2] != 0)
                         ignore = 0;
                 else
                         ignore = 1;

                 if (buf[2] == 0x29)
                         break;
         }

         usb_resetep(handle, ep);
         usb_release_interface(handle, altsetting->bInterfaceNumber);

         usb_close(handle);
         return 0;
}

int main (int argc,char **argv)
{
  printf("Trying to locate the Luxeed LED keyboard...\n");

  // Call the findKeyboard function and store the returned results.
  // The function takes the vendor id and product id of the desired keyboard as arguments
  // so that it knows what to look for
 // struct usb_device *dev;
  struct usb_device *dev;
  dev = findKeyboard(0x413C,0x2106);
  int r,x;
  char string[8];
  //usb_dev_handle *fdev;
  //fdev = usb_open(dev);
//If the keyboard wasn't found the function will have returned NULL
  if (dev == NULL) {
    fprintf(stderr, "Not found!\n");
    return 1;
  }
 
  //If it gets this far, it means it found the keyboard
  printf("Found it! Now make me blink already!\n");
  usb_keyboard_test(dev);
/*
  while(1)
{
  r=usb_interrupt_read(fdev,0x81,string,8,0);
  for (x=0;x<8 && r>0;x++)
    printf("%d," ,string[x]);
  printf("\n");
}
*/
  return 0;
}
