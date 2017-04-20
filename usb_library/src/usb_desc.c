/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"
#include "usb_desc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

//USB设备描述符的定义  /* USB Standard Device Descriptor */
const u8 Joystick_DeviceDescriptor[JOYSTICK_SIZ_DEVICE_DESC] =
{
	0x12,                       /*bLength */
    USB_DEVICE_DESCRIPTOR_TYPE, /*bDescriptorType*/
    0x10,                       /*bcdUSB */
    0x01,
    0xFF,                       /*bDeviceClass*/
    0x00,                       /*bDeviceSubClass*/
    0x00,                       /*bDeviceProtocol*/
    0x40,                       /*bMaxPacketSize40*/
    0x88,                       /*idVendor (0x0483)*/
    0x16,
    0x22,                       /*idProduct = 0x5750*/
    0x00,
    0x00,                       /*bcdDevice rel. 2.00*/
    0x02,
    1,                          /*Index of string descriptor describing manufacturer */
    2,                          /*Index of string descriptor describing product*/
    3,                          /*Index of string descriptor describing the device serial number */
    0x01                        /*bNumConfigurations*/
}

; 
/* Joystick_DeviceDescriptor */

//USB配置描述符集合的定义
const u8 Joystick_ConfigDescriptor[JOYSTICK_SIZ_CONFIG_DESC] =
{
	0x09, /* bLength: Configuation Descriptor size */
    USB_CONFIGURATION_DESCRIPTOR_TYPE, /* bDescriptorType: Configuration */
    JOYSTICK_SIZ_CONFIG_DESC,
    /* wTotalLength: Bytes returned */
    0x00,
    0x01,         /* bNumInterfaces: 1 interface */
    0x01,         /* bConfigurationValue: Configuration value */
    0x00,         /* iConfiguration: Index of string descriptor describing
                                 the configuration*/
    0xe0,         /* bmAttributes: Bus powered */
                  /*Bus powered: 7th bit, Self Powered: 6th bit, Remote wakeup: 5th bit, reserved: 4..0 bits */
    0x32,         /* MaxPower 100 mA: this current is used for detecting Vbus */
 //   0x96,         /* MaxPower 300 mA: this current is used for detecting Vbus */
    /************** Descriptor of Custom HID interface ****************/
    /* 09 */
    0x09,         /* bLength: Interface Descriptor size */
    USB_INTERFACE_DESCRIPTOR_TYPE,/* bDescriptorType: Interface descriptor type */
    0x00,         /* bInterfaceNumber: Number of Interface */
    0x00,         /* bAlternateSetting: Alternate setting */
    0x02,         /* bNumEndpoints */
    0x03,         /* bInterfaceClass: HID */
    0x00,         /* bInterfaceSubClass : 1=BOOT, 0=no boot */
    0x00,         /* nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse */
    0,            /* iInterface: Index of string descriptor */
    /******************** Descriptor of Custom HID HID ********************/
    /* 18 */
    0x09,         /* bLength: HID Descriptor size */
    HID_DESCRIPTOR_TYPE, /* bDescriptorType: HID */
    0x10,         /* bcdHID: HID Class Spec release number */
    0x01,
    0x00,         /* bCountryCode: Hardware target country */
    0x01,         /* bNumDescriptors: Number of HID class descriptors to follow */
    0x22,         /* bDescriptorType */
    JOYSTICK_SIZ_REPORT_DESC,/* wItemLength: Total length of Report descriptor */
    0x00,
    /******************** Descriptor of Custom HID endpoints ******************/
    /* 27 */
    0x07,          /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE, /* bDescriptorType: */

    0x81,          /* bEndpointAddress: Endpoint Address (IN) */               
                   // bit 3...0 : the endpoint number
                   // bit 6...4 : reserved
                    // bit 7     : 0(OUT), 1(IN)
    0x03,          /* bmAttributes: Interrupt endpoint */
    0x40,          /* wMaxPacketSize: 64 Bytes max */
    0x00,
    0x01,          /* bInterval: Polling Interval (2 ms) */
    /* 34 */
    	
    0x07,	/* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,	/* bDescriptorType: */
			/*	Endpoint descriptor type */
    0x01,	/* bEndpointAddress: */
			/*	Endpoint Address (OUT) */
    0x03,	/* bmAttributes: Interrupt endpoint */
    0x40,	/* wMaxPacketSize: 64 Bytes max  */
    0x00,
    0x0A	/* bInterval: Polling Interval (2 ms) */
    /* 41 */
}


; /* MOUSE_ConfigDescriptor */

const u8 Joystick_ReportDescriptor[JOYSTICK_SIZ_REPORT_DESC] =
{
	0x06, 0x00,0xFF,                    // USAGE_PAGE(User define)0x06, 0x00,0xFF
    0x09, 0x01,                    // USAGE(User define)
    0xa1, 0x01,                    // COLLECTION (Application)    
	0x09, 0x01,                    // USAGE_PAGE(1)使用在页面	
	0x15, 0x00,
	
	0x26, 0xff,                    // USAGE_PAGE(2)	使用在页面
    0x00, 0x75,                    //   USAGE_MINIMUM(0)
    0x08, 0x95,                    //   USAGE_MAXIMUM(255)
	
    0x40, 0x81,                    //   LOGICAL_MAXIMUM (255)
	0x02, 0x09,                    //   LOGICAL_MINIMUM (0)
    0x02, 0x15,                    //   INPUT (Data,Var,Abs)
    
    0x00, 0x26,                    // USAGE_PAGE(3)使用在页面
    0xff, 0x00,                    //   USAGE_MINIMUM(0)
    0x75, 0x08,                    //   USAGE_MAXIMUM(255)
	
    0x95, 0x3F,                    //   LOGICAL_MAXIMUM (255)
   // 0x91, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x91, 0x02,                    //   OUTPUT (Data,Var,Abs)
    0xc0                           // END_COLLECTION
}; /* Joystick_ReportDescriptor */


/* USB String Descriptors (optional) */
const u8 Joystick_StringLangID[JOYSTICK_SIZ_STRING_LANGID] =
  {
    JOYSTICK_SIZ_STRING_LANGID,
    USB_STRING_DESCRIPTOR_TYPE,
    0x09,
    0x04
  };
  

const u8 Joystick_StringVendor[JOYSTICK_SIZ_STRING_VENDOR] =
  {
    JOYSTICK_SIZ_STRING_VENDOR, /* Size of Vendor string */
    USB_STRING_DESCRIPTOR_TYPE,  /* bDescriptorType*/
    /* Manufacturer: "STMicroelectronics" */
    'X', 0, 'K', 0, 'Y', 0,'C', 0
  };
  

const u8 Joystick_StringProduct[JOYSTICK_SIZ_STRING_PRODUCT] =
{
	JOYSTICK_SIZ_STRING_PRODUCT,          /* bLength */
	USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
   'I', 0, //I
	'D', 0, //D
	'2', 0,	//2
	' ', 0, 
	'R', 0, 
	'e', 0,  
	'a', 0,  
	'd', 0,  
	'e', 0,  
	'r', 0  
	};

const u8 Joystick_StringSerial[JOYSTICK_SIZ_STRING_SERIAL] =
{
	JOYSTICK_SIZ_STRING_SERIAL,           /* bLength */
   USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
	0x35, 0x00, //5
	0x26, 0x00, //&
	0x31, 0x00, //1
	0x37, 0x00, //7
	0x42, 0x00, //B
	0x45, 0x00, //E
	0x43, 0x00, //C
	0x38, 0x00, //8
	0x32, 0x00, //2
	0x39, 0x00, //9
	0x26, 0x00, //&
	0x30, 0x00, //0
	0x26, 0x00, //&
	0x32, 0x00 //2
  };

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/


