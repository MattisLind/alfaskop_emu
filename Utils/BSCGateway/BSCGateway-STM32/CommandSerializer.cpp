#include <stdio.h>


#include "CommandSerializer.h"

/*CommandSerializer::CommandSerializer (class Serial &serial, void (* processMessage) (MSG *)) {
  Serial=serial;
  processMessageCb = processMessage;
  }*/

unsigned char CommandSerializer::AsciiHexToChar (char ch) {
  return (ch > '9')?ch-'A'-10:ch-'0';
}

void CommandSerializer::processCharacter (char ch) {
  MSG msg;
  printf ("commandState=%d ch=%c\n", commandState, ch);
  if (commandState == 0) {
    bufferPtr=0;  
    command = ch;    
    switch (ch) {
    case 'G':
    case 'L':
    case 'M':
    case 'W':
    case 'R':
    case 'Q':
    case 'N':
    case 'S':
    case 'X':
    case 'T':
    case 'P':
    case 'E': // Error !
      commandState=1; 
      break;
    case 'H':
    case 'I':
      command = ch;
      rtsVal = -1;
      ctsVal = -1;
      dtrVal = -1;
      commandState=2;
      break;
    default:
      break;
    }
  }
  else if (commandState == 1) {
    if (ch == '\n') { // NL
      switch (command) {
      case 'G':
	msg.type = HAND_REQ;
	break;
      }
      processMessageCb (&msg);	    
      commandState = 0;
    } else if ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F' )) {
      // First hex digit	
      // Valid hex digit
      commandState=1; // Go back and look for another hexdigit
      hexdigit = AsciiHexToChar(ch) << 4;   
      commandState = 4;
      messageBuffer[bufferPtr++] = hexdigit;
    } else {
      commandState = 5; // Error clean up
      Serial.println('E');	  
    }
  }
  else if (commandState == 2) {
    // Parse handshake lines code R, C, D
    switch (ch) {
    case 'R':
    case 'C':
    case 'D':
      commandState = 3;
      handshakeLine = ch;
      break;
    case '\n':
      commandState = 0; // execute handshake command
      if (command == 'H') {
	msg.type = SET_HAND;
      } else {
	msg.type = REP_HAND;
      }
      msg.data.handshakeData.dtr = dtrVal;
      msg.data.handshakeData.rts = rtsVal;
      msg.data.handshakeData.cts = ctsVal;
      processMessageCb (&msg);      
      break;
    default:
      // wait for next NL and start over
      Serial.println('E');
      commandState = 5;
      break;      
    }
  }
  else if (commandState == 3) {
    // Parse handshake line value, 0 or 1.
    switch (ch) {
    case '0':
    case '1':
      commandState = 2;
      switch (handshakeLine) {
      case 'R':
	rtsVal = ch-'0';
	break;
      case 'C':
	ctsVal = ch-'0';
	break;
      case 'D':
	dtrVal = ch-'0';
	break;
      }
      break;
    case '\n':
      commandState = 0;
      Serial.println('E');
      break;
    }
  }
  else if (commandState == 4) {
    if (ch == '\n') {
      // This is an error only first of a hex digits received
      Serial.println('E');
      commandState = 0;
    } else if ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F' )) {
      // Valid hex digit
      // Second hexdigit
      commandState=1; // Go back and look for another hexdigit
      hexdigit |= AsciiHexToChar (ch) & 0x0f;
      
    } else {
      commandState = 5; // Error clean up
      Serial.println('E');
    }
  } else if (commandState == 5) {
    if (ch == '\n') { // We have an error. Wait until next NL and start parsing again.
      commandState = 0;
    } 
  }
}


void CommandSerializer::doRequestHandshakeLineState() {
  Serial.println("G");
}

void CommandSerializer::handleHandshakeLines (int rtsVal, int ctsVal, int dtrVal) {
  if (rtsVal>=0) {
    Serial.print('R');
    Serial.print(rtsVal+'0');
  }
  if (ctsVal>=0) {
    Serial.print('C');
    Serial.print(ctsVal+'0');
  }
  if (dtrVal>=0) {
    Serial.print('D');
    Serial.print(dtrVal+'0');
  }
  Serial.println();  
}

// if val is negative then not sent.
void CommandSerializer::doSetResetHandshakeLines(int rtsVal, int ctsVal, int dtrVal) {
  Serial.print('H');
  handleHandshakeLines(rtsVal, ctsVal, dtrVal);
}

void CommandSerializer::doHandshakeLinesChanged(int rtsVal, int ctsVal, int dtrVal) {
  Serial.print('I');
  handleHandshakeLines(rtsVal, ctsVal, dtrVal);
}

void CommandSerializer::doEOT() {
  Serial.println("Q");
}
void CommandSerializer::doENQ(unsigned char CU, unsigned char DV) {
  Serial.print("P");
  Serial.print(CU, HEX);
  Serial.print(DV,HEX);
  Serial.println();
}
void CommandSerializer::doStatus() {}
void CommandSerializer::doTestRequestMessage() {}
void CommandSerializer::doTextMessage() {}
void CommandSerializer::doACK0() {
  Serial.println('L');
}
void CommandSerializer::doACK1() {
  Serial.println('M');
}
void CommandSerializer::doWACK() {
  Serial.println('W');
}
void CommandSerializer::doRVI() {
  Serial.println('R');
}
void CommandSerializer::doNAK() {
  Serial.println('N');
}
