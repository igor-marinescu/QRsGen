# QRsGen
QR-code simple Generator
![Alt QRsGen](/resources/screenschot1.png)

## What is QRsGen
QRsGen is a simple tool for generating QR-codes.
It is made in Qt and uses fukuchi/libqrencode.

## Installing
The tool doesn't need to be installed.
Execute QRsGen.exe from bin folder to start it.
QRsGen doesn't modify any files/registry on local machine.
QRsGen doesn't send/receive anything to/from network.

## Command line arguments
It is possible to customize QRsGen by invoking it with additional arguments:

		QRsGen.exe [-e <level>] [-c <mode>] [-s <on>] [-h] [text]

Arguments:

     -e <level> | --error <level>

         Error Correction Level. Valid values for <level>: 0 .. 3,
             0   Lowest (default)
             3   Highest

     -c <mode> | --encoding <mode>

         Encoding Mode. Valid values for <mode>: 0 .. 3
             0   Numeric mode
             1   Alphabet-numeric mode
             2   8-bit data mode (default)
             3   Kanji mode

     -s <on> | --sensitive <on>

         Case Sensitive On/Off. Valid values:
             0   Case non-sensitive
             1   Case sensitive (default)

     -h | --help Displays this help

     text Text to be displayed as QR Code

Example:

     QRsGen.exe -e 1 -c 2 -s 1 "Hello World"

     Generates QR-Code from "Hello World", Error Correction Level=Medium
     Encoding Mode=8-bit data, case sensitive.


## Authors

Igor Marinescu - Qt UI

## License

See the [LICENSE.md](LICENSE.md) file for details.

## Acknowledgments

fukuchi - libqrencode (https://github.com/fukuchi/libqrencode)
