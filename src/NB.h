/*
  This file is part of the MKR NB library.
  Copyright (c) 2018 Arduino SA. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _NB_H_INCLUDED
#define _NB_H_INCLUDED

#include <Arduino.h>

enum NB_NetworkStatus_t { ERROR, IDLE, CONNECTING, NB_READY, GPRS_READY, TRANSPARENT_CONNECTED, NB_OFF};

class NB {

public:
  /** Constructor
      @param debug    Determines debug mode
    */
  NB(bool debug = false);

  /** Start the NB IoT modem, attaching to the NB IoT or LTE Cat M1 network
      @param pin         SIM PIN number (4 digits in a string, example: "1234"). If
                         NULL the SIM has no configured PIN.
      @param apn         (optional) APN to use
      @param restart     Restart the modem. Default is TRUE. The modem receives
                         a signal through the Ctrl/D7 pin. If it is shut down, it will
                         start-up. If it is running, it will restart. Takes up to 10
                         seconds
      @param synchronous If TRUE the call only returns after the Start is complete
                         or fails. If FALSE the call will return immediately. You have
                         to call repeatedly ready() until you get a result. Default is TRUE.
      @return If synchronous, NB_NetworkStatus_t. If asynchronous, returns 0.
    */
  NB_NetworkStatus_t begin(const char* pin = 0, bool restart = true, bool synchronous = true);
  NB_NetworkStatus_t begin(const char* pin, const char* apn, bool restart = true, bool synchronous = true);
  NB_NetworkStatus_t begin(const char* pin, const char* apn, const char* username, const char* password, bool restart = true, bool synchronous = true);

  /** Check network access status
      @return 1 if Alive, 0 if down
   */
  int isAccessAlive();

  /** Shutdown the modem (power off really)
      @return true if successful
    */
  bool shutdown();

  /** Secure shutdown the modem (power off really)
      @return always true
    */
  bool secureShutdown();

  /** Hard reset the modem
   */ 
  void hardReset();

  /** Get last command status
      @return returns 0 if last command is still executing, 1 success, >1 error
    */
  int ready();

  void setTimeout(unsigned long timeout);

  /** Get number of hard resets
   */
  int getResetCount();

  unsigned long getTime();
  unsigned long getLocalTime();
  bool setTime(unsigned long const epoch, int const timezone = 0);

  NB_NetworkStatus_t status();

private:
  NB_NetworkStatus_t _state;
  int _readyState;
  const char* _pin;
  const char* _apn;
  const char* _username;
  const char* _password;
  String _response;
  unsigned long _timeout;
  int _resetCount = 0;
};

#endif
