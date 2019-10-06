# Alfaskop Commander

This is a small quick and dirty tool that is used to send a poll message to the Alfaskop terminal over the SS3 bus. It uses a TWIB board
that was perviously reversengineered connected to a small STM32F103 based blue pill board.

![Board and STM32](https://i.imgur.com/aPNMMkrl.jpg?1)

Connecting the realterm client to the serial port give a simple command line interface where operations like Reset and send a poll can be performed. 
Since the bus will listen to its own transmission it will see the loopback of the poll message sent.

![Realterm view](https://raw.githubusercontent.com/MattisLind/alfaskop_emu/master/Utils/AlfaskopCommander/AlfaskopCommander.png)

The resulting waveform. There are significant amount of leading transitions which are to make the receiver synchronize to the signal sent.

![Scope output](https://i.imgur.com/hYTeKTEl.jpg?1)

This mockup was tested against the real world Alfaskop 4110 and it did infact respond to the Poll as it should. The not so exciting video clip below show what happens when the terminal receive a poll. After the LOAD text on the status line a P is added to signify that the poll has been received and that the terminal sent a IPL request in response.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=8MVXaOKJ0f0
" target="_blank"><img src="http://img.youtube.com/vi/8MVXaOKJ0f0/0.jpg" 
alt="IMAGE ALT TEXT HERE" width="480" height="360" border="10" /></a>

And the resulting output in the terminal window:

![Successful poll](https://i.imgur.com/oOjNPl7l.jpg)

The poll command sent is 00 00 FE E9 (the two extra bytes are the CRC as received) and the poll response from the terminal is th FE FF 00 A0 FF + 2 CRC bytes.

