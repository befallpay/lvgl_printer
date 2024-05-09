Thermal printer function packaged based on LVGL open-source library.

1. The LVGL project uses the official "lv_port_win_codeblocks master", and the LVGL open-source library uses version 9.0.

2. Code file description

PrEmu: Simulating Print Paper Output with Bitmap Files

PrInput: The dependency of the printer. Users only need to adapt the functions to run the printer function.

PrWraper: A secondary packaging based on PrInput for ease of use.

PrLvgl: A printer basic functional interface based on lvgl encapsulation, such as image printing and text printing.

MonoPix: monochromatic data processing. Convenient printer to achieve rich functions.

PrTest: An example of using printer functionality.
