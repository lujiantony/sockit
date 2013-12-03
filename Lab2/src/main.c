
// Copyright 2007, Jesper Thomschutz <jesperht@yahoo.com>
// Licensed under GPLv2

#include <stdio.h>
#include <usb.h>
#include <stdint.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/time.h>

pthread_t thread;
pthread_mutex_t mut;
int number=0, i;
int sockfd = 0;

/*
void *ethernet_read_thread()
{
    int sockfd = 0, n = 0;
    char recvbuff[256];
    struct sockaddr_in serv_addr;
    const char host[] = "128.59.17.215";

    memset(recvbuff, '0',sizeof(recvbuff));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(42000);

    if(inet_pton(AF_INET, host, &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    }

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    }

/*        while((n = read(sockfd, recvbuff, sizeof(recvbuff)-1)) > 0)
    {
        printf("%s\n",recvbuff);
    }

    printf("Starting listening to the incoming Ethernet packages")
    while ( (n = read(sockfd, recvbuff, sizeof(recvbuff)-1)) > 0)
    {
        recvbuff[n] = 0;
        if(fputs(recvbuff, stdout) == EOF)
        {
            printf("\n Error : Fputs error\n");
        }
    }

    if(n < 0)
    {
        printf("\n Read error \n");
    }

    pthread_exit(NULL);
}
*/

void *ethernet_read_thread()
{

	 ////////Socket initialization for Ethernet communication////////
	    int n = 0;
	    char recvbuff[1024];
	    //unsigned char sendbuff[256];
	    struct sockaddr_in serv_addr;
	    const char host[] = "128.59.18.126";

	    memset(recvbuff, '0', sizeof (recvbuff));
	    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
	        printf("\n Error : Could not create socket \n");
	        pthread_exit(NULL);
	    }

	    memset(&serv_addr, '0', sizeof (serv_addr));

	    serv_addr.sin_family = AF_INET;
	    serv_addr.sin_port = htons(42000);

	    if (inet_pton(AF_INET,host, &serv_addr.sin_addr) <= 0) {
	        printf("\n inet_pton error occured\n");
	        pthread_exit(NULL);
	    }

	    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof (serv_addr)) < 0) {
	        printf("\n Error : Connect Failed \n");
	        pthread_exit(NULL);
	    }

/*
	    while ((n = read(sockfd, recvbuff, sizeof (recvbuff) - 1)) > 0) {
	        recvbuff[n] = 0;
	        if (fputs(recvbuff, stdout) == EOF) {
	            printf("\n Error : Fputs error\n");
	        }
	    }

	    if (n < 0) {
	        printf("\n Read error \n");
	    }
*/

	       while ((n = read(sockfd, recvbuff, sizeof (recvbuff) - 1)) > 0)
	        {
	        recvbuff[n] = 0;
	        if(strlen(recvbuff)!=0){
	        printf("Received: ");
	        printf("%s\n",recvbuff);}
	        }

	        if(n < 0)
	        {
	            printf("\n Read error \n");
	        }

	        pthread_exit(NULL);
	    ////////End of Socket initializaiton////////
}


void thread_create(void)
{
        int temp;
        memset(&thread, 0, sizeof(thread));          //comment1
        /*create Ethernet read thread*/
        if((temp = pthread_create(&thread, NULL, ethernet_read_thread, NULL)) != 0)       //comment2
                printf("Error: Ethernet read thread not created!\n");
        else
                printf("Ethernet read thread created\n");
}

void thread_wait(void)
{
        /*wait for thread to end*/
        if(thread !=0) {                   //comment4
                pthread_join(thread,NULL);
                printf("Ethernet read thread finished\n");
        }
}

static unsigned char keycode[256] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2',
    '3', '4', '5', '6', '7', '8', '9', '0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
};

//The function is used to find the keyboard with specified Vendor ID and Product ID
//It returns the usb_device handle for read the keyboard input

static struct usb_device *findKeyboard(uint16_t vendor, uint16_t product) {
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
print_input(unsigned char *buf, uint16_t size) {
    int i;

    if (size < 3) return;
    if (buf[2] == 0x01) return;

    printf("INPUT: ");
    for (i = 0; i < size; i++) {
        if (buf[i])
            printf("\"%c\"(0x%02x) ", keycode[buf[i]], buf[i]);
    }

    printf("%s%s\n",
            (buf[0] & 0x01) ? "[ctrl]" : "",
            (buf[0] & 0x02) ? "[shift]" : ""
            );
}

int usb_keyboard_init(struct usb_device *dev) {

}

int usb_keyboard_test(struct usb_device *dev) {
    usb_dev_handle *handle;
    struct usb_config_descriptor *config = &dev->config[0];
    struct usb_interface *interface = &config->interface[0];
    struct usb_interface_descriptor *altsetting = &interface->altsetting[0];
    struct usb_endpoint_descriptor *endpoint = &altsetting->endpoint[0];
    uint8_t ep = endpoint->bEndpointAddress;
    unsigned char buf1[3];
    unsigned char buf[256];
    ssize_t read_size;
    int ignore = 1;
    int i = 0;
    handle = usb_open(dev);
    usb_get_string_simple(handle, dev->descriptor.iProduct,
            (char *) buf, sizeof (buf));

    printf("USB-DEV: 0x%04x/0x%04x \"%s\"\n",
            dev->descriptor.idVendor, dev->descriptor.idProduct, buf);

    if (usb_set_configuration(handle, config->bConfigurationValue) < 0) {
        if (usb_detach_kernel_driver_np(handle, altsetting->bInterfaceNumber) < 0) {
            printf("usb_set_configuration() error.\n");
            usb_close(handle);
            return -1;
        }
    }

    usb_claim_interface(handle, altsetting->bInterfaceNumber);

    while (1) {
        read_size = usb_interrupt_read(handle, ep, (char *) buf, endpoint->wMaxPacketSize, 100);
        //read_size = usb_interrupt_read(handle, ep, (char *)buf1,8, 1000);
        if (read_size < 0) {
            if (read_size == -ETIMEDOUT)
                printf("read timeout.\n");
            else
                printf("read error: %d\n", read_size);
        }

        if (buf[2] == 0x29)
            break;

        if (!buf[3])
            print_input(buf, endpoint->wMaxPacketSize);
        /*
         if (!ignore || buf1[2])
                 print_input(buf1, endpoint->wMaxPacketSize);

         if (buf1[2] != 0)
                 ignore = 0;
         else
                 ignore = 1;
         */


    }

    usb_resetep(handle, ep);
    usb_release_interface(handle, altsetting->bInterfaceNumber);

    usb_close(handle);
    return 0;
}

int main(int argc, char **argv) {

    pthread_mutex_init(&mut,NULL);

    printf("This is the main function\n");
    thread_create();



    // Call the findKeyboard function and store the returned results.
    // The function takes the vendor id and product id of the desired keyboard as arguments
    // so that it knows what to look for
    struct usb_device *dev;
    printf("Trying to locate the keyboard...\n");
    dev = findKeyboard(0x413C, 0x2003);

    //If the keyboard wasn't found the function will have returned NULL
    if (dev == NULL) {
        fprintf(stderr, "Not found!\n");
        return 1;
    }

    //If it gets this far, it means it found the keyboard
    printf("Found it!\n");

    ////////Initiate the USB keyboard////////
    usb_dev_handle *handle;
    struct usb_config_descriptor *config = &dev->config[0];
    struct usb_interface *interface = &config->interface[0];
    struct usb_interface_descriptor *altsetting = &interface->altsetting[0];
    struct usb_endpoint_descriptor *endpoint = &altsetting->endpoint[0];
    uint8_t ep = endpoint->bEndpointAddress;
    unsigned char buf[256];
    unsigned char sendbuff[256];
    int msg_len = 0;
    ssize_t read_size;
    int ignore = 1;
    int i = 0;
    memset(sendbuff,'\0',sizeof(sendbuff));
    handle = usb_open(dev);
    usb_get_string_simple(handle, dev->descriptor.iProduct,
            (char *) buf, sizeof (buf));

    printf("USB-DEV: 0x%04x/0x%04x \"%s\"\n",
            dev->descriptor.idVendor, dev->descriptor.idProduct, buf);

    if (usb_set_configuration(handle, config->bConfigurationValue) < 0) {
        if (usb_detach_kernel_driver_np(handle, altsetting->bInterfaceNumber) < 0) {
            printf("usb_set_configuration() error.\n");
            usb_close(handle);
            return -1;
        }
    }

    usb_claim_interface(handle, altsetting->bInterfaceNumber);
    ////////End of USB keyboard initiation////////






    //Start reading input from keyboard
    while (1) {

        /*The USB keyboard package is as follow:
         * Each package contains 8 bytes
         * BYTE0 BYTE1 BYTE2 BYTE3 BYTE4 BYTE5 BYTE6 BYTE7
         * BYTE0--
         * 		|--bit0: Left Control, if pressed, bit0 = 1
         * 		|--bit1: Left Shift,   if pressed, bit1 = 1
         * 		|--bit2: Left Alt,     if pressed, bit2 = 1
         * 		|--bit3: Left GUI,     if pressed, bit3 = 1
         * 		|--bit4: RightControl, if pressed, bit4 = 1
         * 		|--bit5: Right Shift,  if pressed, bit5 = 1
         * 		|--bit6: Right Alt,    if pressed, bit6 = 1
         * 		|--bit7: Right GUI,    if pressed, bit7 = 1
         * BYTE1-- Reserved
         * BYTE2-BYTE7 --Normal key inputs
         * Example:
         * If the keyboard send a package as follow:
         * 0x02 0x00 0x04 0x05 0x00 0x00 0x00 0x00
         * This means that Left Shift + "a" + "b" are pressed simultaneously!
         */
/*
        n = read(sockfd, recvbuff, sizeof (recvbuff) - 1);

        recvbuff[n] = 0;
        if(strlen(recvbuff)!=0)
        printf("The received: %s",recvbuff);

        n = read(sockfd, recvbuff, sizeof (recvbuff) - 1);
        recvbuff[n] = 0;
        if (fputs(recvbuff, stdout) == EOF) {
            printf("\n Error : Fputs error\n");
        }
        if (n < 0) {
            printf("\n Read error \n");}
*/

        //Clear the buf for usb package receiving
        buf[0] = '\0';
        //read the usb package
        read_size = usb_interrupt_read(handle, ep, (char *) buf, endpoint->wMaxPacketSize, 300);

        //Check if the usb_interrupt_read returns correctly
        if (read_size < 0) {
            if (read_size != -ETIMEDOUT)
                printf("read error: %d\n", read_size);
        }

            /*
            if (read_size < 0) {
                if (read_size == -ETIMEDOUT)
                    printf("read timeout.\n");
                else
                    printf("read error: %d\n", read_size);
            }
             */
        else {

            /*The follwoing is the case where only one key is pressed at the same time
             *Remember that the USB keyboard package can contain multiple keys. The usage of the package completely depends on what you need
             *In this case, we only need single key as our input, so we check if buf[3]==0.
             *Also remember that release a key will also trigger the usb_interrupt_read.
             */

            if (buf[2] == 0x29)
                break;

            //When buf[0] == 0, it means no functional keys are pressed, such as alt, shift and ctrl
            //Finish the else statement to make use of the functional keys
            if (buf[0] == 0) {
                if (!buf[3]) {
                    //Handle normal input with
                    if (buf[2] >= 0x04 && buf[2] < 0x28) {
                        //Append each input to the sendbuf.
                        sendbuff[msg_len++] = keycode[buf[2]];
                        printf("The current input is %c\n", keycode[buf[2]]);
                        printf("The sendbuff is now %s\n\n", sendbuff);
                    } else {
                        //Handle special input
                        switch (buf[2]) {
                                //Space
                            case 0x2C: sendbuff[msg_len++] = ' ';
                                break;

                                //Enter
                            case 0x28:

                            {
                            	sendbuff[msg_len] = '\0';
                                write(sockfd, sendbuff, strlen(sendbuff));
                                memset(sendbuff,'\0',sizeof(sendbuff));
                                msg_len = 0;
                            }
                                break;

                                //Backspace
                            case 0x2A:
                            {
                                sendbuff[--msg_len] = 0;
                                printf("The sendbuff is now %s\n\n", sendbuff);
                            }
                                break;

                            default: break;

                                //Add more cases here like backspace, enter etc
                        }
                        //printf("The sendbuff is now %s\n\n",sendbuff);
                    }
                } else {
                    //Insert your code for the case when multiple keys are being pressed simultaneously
                }
            } else {
                //Insert your code here to handle functional keys
            }

            //printf("The sendbuff is now %s\n\n",sendbuff);

            /*if (!buf[3])
                print_input(buf, endpoint->wMaxPacketSize);

             if (!ignore || buf[2])
                     print_input(buf1, endpoint->wMaxPacketSize);

             if (buf1[2] != 0)
                     ignore = 0;
             else
                     ignore = 1;
             */

        }
    }
    //usb_keyboard_test(dev);
    /*
      while(1)
    {
      r=usb_interrupt_read(fdev,0x81,string,8,0);
      for (x=0;x<8 && r>0;x++)
        printf("%d," ,string[x]);
      printf("\n");
    }
     */

    //Release the USB device
    usb_resetep(handle, ep);
    usb_release_interface(handle, altsetting->bInterfaceNumber);
    usb_close(handle);
    printf("Waiting for other threads to end\n");
    thread_wait();
    return 0;
}

