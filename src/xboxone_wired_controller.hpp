#pragma once

#include <libusb.h>
#include <string>

#include "usb_controller.hpp"

class XboxOneWiredController: public USBController
{
private:
  int endpoint;
  int interface;
  bool sent_auth;
  bool guide_button;

private:
  bool parse_button_status(uint8_t* data, int len, XboxGenericMsg* omsg);
  bool parse_ledbutton_status(uint8_t* data, int len, XboxGenericMsg* omsg);
  bool parse_init_status(uint8_t* data, int len, XboxGenericMsg* omsg);
  bool parse_auth_status(uint8_t* data, int len, XboxGenericMsg* omsg);

  XboxOneWiredController(const XboxOneWiredController& other);
  XboxOneWiredController& operator= (const XboxOneWiredController&);

public:
  XboxOneWiredController(libusb_device* usb, int controller_id, bool try_detach);
  virtual ~XboxOneWiredController();

  bool parse(uint8_t* data, int len, XboxGenericMsg* msg_out);
  void set_rumble_real(uint8_t left, uint8_t right);
  void set_led_real(uint8_t status);
};

