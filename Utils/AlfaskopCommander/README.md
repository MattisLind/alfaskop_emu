# Alfaskop Commander

This is a small quick and dirty tool that is used to send a poll message to the Alfaskop terminal over the SS3 bus. It uses a TWIB board
that was perviously reversengineered connected to a small STM32F103 based blue pill board.

![Board and STM32](https://i.imgur.com/aPNMMkrl.jpg?1)

Connecting the realterm client to the serial port give a simple command line interface where operations liker Reset and send a poll can be performed. 
Since the bus will listen to its own transmission it will see the loopback of the poll message sent.

![Realterm view](https://raw.githubusercontent.com/MattisLind/alfaskop_emu/master/Utils/AlfaskopCommander/AlfaskopCommander.png)

The resulting waveform. There are significant amount of leading transistion which is to make the receiver synchronize to the signal sent.

![Scope output](https://i.imgur.com/hYTeKTEl.jpg?1)
