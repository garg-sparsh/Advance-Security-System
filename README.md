# Advance-Security-System
In the RFID system, the reader sends out a radio frequency wave to the tag and the
tag broadcasts back its stored data to the reader. The system has two antennas, one
for the tag and the other on the reader. The data collected from the tag can either be
sent directly to a host computer through standard interfaces or it can be stored in a
portable reader and later updated to the computer for data processing. The
automatic reading and direct use of tag data is called ‘automatic data capture’.
When the tag which is battery free, is to be read, the reader sends out a power pulse
to the antenna lasting for about 50ms.The magnetic field generated is collected by
the antenna in the transponder that is tuned to the same frequency. This received
energy is rectified and stored on a capacitor within the transponder. When the power
pulse has finished, the transponder immediately transmits back its data, using the
energy stored within its capacitor as its power source. The data is picked up by the
receiving antenna and decoded by the reader unit. Once all the data has been
transmitted, the storage capacitor is discharged resetting the transponder to make it
ready for the next read cycle. The period between transmission pulses is called sync
time and lasts between 20ms and 50ms depending on the system set up.
